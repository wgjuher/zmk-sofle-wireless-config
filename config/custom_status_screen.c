/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/display/cfb.h>

#include <zmk/display.h>
#include <zmk/display/status_screen.h>
#include <zmk/event_manager.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/events/keypress_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/wpm.h>
#include <zmk/keymap.h>
#include <zmk/battery.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// Bongo cat animation states
enum bongo_state {
    BONGO_IDLE,
    BONGO_TAP,
    BONGO_PREP,
    BONGO_FURIOUS
};

// Animation timing
#define ANIM_FRAME_DURATION 500
#define IDLE_FRAME_DURATION 2000
#define TAP_FRAME_DURATION 350
#define PREP_FRAME_DURATION 200
#define FURIOUS_FRAME_DURATION 80

// WPM thresholds
#define IDLE_WPM_THRESHOLD 0
#define TAP_WPM_THRESHOLD 10
#define PREP_WPM_THRESHOLD 30
#define FURIOUS_WPM_THRESHOLD 50

// Simple bongo cat ASCII art for 128x32 display
static const char* bongo_idle_frames[] = {
    " /\\_/\\  ",
    "( o.o ) ",
    " > ^ <  ",
    "        "
};

static const char* bongo_tap_frames[] = {
    " /\\_/\\  ",
    "( ^.^ ) ",
    " \\ ˇ /  ",
    "   !    "
};

static const char* bongo_prep_frames[] = {
    " /\\_/\\  ",
    "( -.- ) ",
    " > - <  ",
    "  ~~~   "
};

static const char* bongo_furious_frames[] = {
    " /\\_/\\  ",
    "( @.@ ) ",
    " \\ ! /  ",
    "  !!!   "
};

// Global state
static enum bongo_state current_bongo_state = BONGO_IDLE;
static uint8_t current_wpm = 0;
static uint8_t current_layer = 0;
static uint8_t battery_level = 100;
static bool typing_activity = false;
static int64_t last_activity_time = 0;
static int64_t last_frame_time = 0;
static uint8_t animation_frame = 0;

static enum bongo_state get_bongo_state(uint8_t wpm) {
    if (wpm >= FURIOUS_WPM_THRESHOLD) {
        return BONGO_FURIOUS;
    } else if (wpm >= PREP_WPM_THRESHOLD) {
        return BONGO_PREP;
    } else if (wpm >= TAP_WPM_THRESHOLD) {
        return BONGO_TAP;
    }
    return BONGO_IDLE;
}

static void draw_bongo_cat(const struct device *dev, int x, int y) {
    const char** frames;
    
    switch (current_bongo_state) {
        case BONGO_FURIOUS:
            frames = bongo_furious_frames;
            break;
        case BONGO_PREP:
            frames = bongo_prep_frames;
            break;
        case BONGO_TAP:
            frames = bongo_tap_frames;
            break;
        default:
            frames = bongo_idle_frames;
            break;
    }
    
    // Draw the 4-line cat
    for (int i = 0; i < 4; i++) {
        cfb_draw_text(dev, frames[i], x, y + (i * 8));
    }
}

static void draw_wpm_info(const struct device *dev, int x, int y) {
    char wpm_text[16];
    snprintf(wpm_text, sizeof(wpm_text), "WPM: %d", current_wpm);
    cfb_draw_text(dev, wpm_text, x, y);
    
    // Add state indicator
    const char* state_text = "";
    switch (current_bongo_state) {
        case BONGO_FURIOUS: state_text = "FURIOUS!"; break;
        case BONGO_PREP: state_text = "Ready..."; break;
        case BONGO_TAP: state_text = "Tapping"; break;
        default: state_text = "Idle"; break;
    }
    cfb_draw_text(dev, state_text, x, y + 8);
}

static void draw_status_info(const struct device *dev, int x, int y) {
    // Layer info
    char layer_text[16];
    snprintf(layer_text, sizeof(layer_text), "L:%d", current_layer);
    cfb_draw_text(dev, layer_text, x, y);
    
    // Battery info
    char battery_text[16];
    snprintf(battery_text, sizeof(battery_text), "B:%d%%", battery_level);
    cfb_draw_text(dev, battery_text, x + 30, y);
}

void zmk_display_status_screen_update_cb(const struct device *dev) {
    if (dev == NULL) {
        return;
    }

    // Clear display
    cfb_framebuffer_clear(dev, false);
    
    // Update animation frame based on timing
    int64_t now = k_uptime_get();
    uint32_t frame_duration = IDLE_FRAME_DURATION;
    
    switch (current_bongo_state) {
        case BONGO_FURIOUS:
            frame_duration = FURIOUS_FRAME_DURATION;
            break;
        case BONGO_PREP:
            frame_duration = PREP_FRAME_DURATION;
            break;
        case BONGO_TAP:
            frame_duration = TAP_FRAME_DURATION;
            break;
        default:
            frame_duration = IDLE_FRAME_DURATION;
            break;
    }
    
    if (now - last_frame_time >= frame_duration) {
        animation_frame = (animation_frame + 1) % 2;
        last_frame_time = now;
    }
    
    // Layout for 128x32 display:
    // [Bongo Cat]  [WPM Info]
    // [Status Info]
    
    // Draw bongo cat (left side)
    draw_bongo_cat(dev, 0, 0);
    
    // Draw WPM info (right side)
    draw_wpm_info(dev, 70, 0);
    
    // Draw status info (bottom)
    draw_status_info(dev, 0, 24);
    
    cfb_framebuffer_finalize(dev);
}

static int custom_status_screen_event_listener(const zmk_event_t *eh) {
    // Handle WPM changes
    if (as_zmk_wpm_state_changed(eh)) {
        current_wpm = zmk_wpm_get_state();
        enum bongo_state new_state = get_bongo_state(current_wpm);
        if (new_state != current_bongo_state) {
            current_bongo_state = new_state;
            animation_frame = 0;
            last_frame_time = k_uptime_get();
        }
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    // Handle key presses for activity
    if (as_zmk_keypress_state_changed(eh)) {
        typing_activity = true;
        last_activity_time = k_uptime_get();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    // Handle layer changes
    if (as_zmk_layer_state_changed(eh)) {
        current_layer = zmk_keymap_highest_layer_active();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    // Handle battery changes
    if (as_zmk_battery_state_changed(eh)) {
        battery_level = zmk_battery_state_of_charge();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    return ZMK_EV_EVENT_BUBBLE;
}

static int custom_status_screen_init(const struct device *dev) {
    LOG_INF("Initializing custom status screen with bongo cat");
    
    current_wpm = 0;
    current_layer = 0;
    battery_level = zmk_battery_state_of_charge();
    current_bongo_state = BONGO_IDLE;
    
    return 0;
}

ZMK_LISTENER(custom_status_screen, custom_status_screen_event_listener);
ZMK_SUBSCRIPTION(custom_status_screen, zmk_wpm_state_changed);
ZMK_SUBSCRIPTION(custom_status_screen, zmk_keypress_state_changed);
ZMK_SUBSCRIPTION(custom_status_screen, zmk_layer_state_changed);
ZMK_SUBSCRIPTION(custom_status_screen, zmk_battery_state_changed);

SYS_INIT(custom_status_screen_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
