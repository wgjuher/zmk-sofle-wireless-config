/*
 * Copyright (c) 2024 The ZMK Contributors
 * Epic Vertical OLED Display for Sofle - Enhanced Edition
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/display/cfb.h>

#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/keymap.h>
#include <zmk/battery.h>
#include <zmk/ble.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static uint8_t current_layer = 0;
static uint8_t battery_level = 100;
static uint8_t animation_frame = 0;
static uint8_t bt_profile = 0;
static bool bt_connected = false;
static uint32_t uptime_minutes = 0;

// Epic bongo cat expressions with mood variations
static const char* cat_expressions[] = {
    "(o.o)",  // 0: Idle - calm and peaceful
    "(^.^)",  // 1: Happy - content and satisfied
    "(-.o)",  // 2: Winking - playful and cheeky  
    "(@.@)",  // 3: Alert - focused and attentive
    "(>.<)",  // 4: Sleepy - tired but cute
    "(*.*)",  // 5: Sparkly - excited and energetic
    "(O_O)",  // 6: Shocked - surprised reaction
    "(~.~)",  // 7: Zen - meditative and peaceful
    "(=.=)",  // 8: Satisfied - accomplished feeling
    "(-.-)"   // 9: Sleepy eyes - very drowsy
};

static const char* cat_activities[] = {
    " >.< ",  // Default sitting
    " >^< ",  // Happy bounce
    " >~< ",  // Focused typing
    " >!< ",  // Alert stance
    " >_< ",  // Sleepy slouch
    " >*< ",  // Excited wiggle
    " >o< ",  // Surprised jump
    " >-< "   // Zen meditation
};

// Layer-specific cat moods
static const uint8_t layer_moods[] = {
    1,  // Layer 0: Happy
    3,  // Layer 1: Alert  
    5,  // Layer 2: Excited
    7   // Layer 3+: Zen
};

#define EXPRESSION_COUNT 10
#define ACTIVITY_COUNT 8
#define ANIMATION_INTERVAL_MS 2500  // Change every 2.5 seconds

// Battery level indicator with visual bars
static void draw_battery_bar(const struct device *dev, uint8_t level, int x, int y) {
    char bat_text[20];
    char bar[9] = "........";  // 8-char bar
    
    // Fill the bar based on battery level
    uint8_t filled = (level * 8) / 100;
    for (int i = 0; i < filled && i < 8; i++) {
        bar[i] = '#';
    }
    bar[8] = '\0';
    
    snprintf(bat_text, sizeof(bat_text), "BAT[%s]%d%%", bar, level);
    cfb_draw_text(dev, bat_text, x, y);
}

// Draw connection status with visual indicators
static void draw_connection_status(const struct device *dev, int x, int y) {
    char conn_text[16];
    if (bt_connected) {
        snprintf(conn_text, sizeof(conn_text), "BT:%d >>>", bt_profile);
    } else {
        snprintf(conn_text, sizeof(conn_text), "BT:%d ...", bt_profile);
    }
    cfb_draw_text(dev, conn_text, x, y);
}

// Draw uptime in a nice format
static void draw_uptime(const struct device *dev, int x, int y) {
    char time_text[16];
    uint32_t hours = uptime_minutes / 60;
    uint32_t mins = uptime_minutes % 60;
    
    if (hours > 0) {
        snprintf(time_text, sizeof(time_text), "UP:%02dh%02dm", hours, mins);
    } else {
        snprintf(time_text, sizeof(time_text), "UP:%02dm", mins);
    }
    cfb_draw_text(dev, time_text, x, y);
}

// Draw enhanced layer info with borders
static void draw_layer_status(const struct device *dev, int x, int y) {
    char layer_text[20];
    const char* layer_names[] = {"QWERTY", "LOWER", "RAISE", "EXTRA"};
    const char* layer_name = current_layer < 4 ? layer_names[current_layer] : "CUSTOM";
    
    snprintf(layer_text, sizeof(layer_text), "[%s]", layer_name);
    cfb_draw_text(dev, layer_text, x, y);
    
    // Add layer number below
    char num_text[16];
    snprintf(num_text, sizeof(num_text), "L:%d", current_layer);
    cfb_draw_text(dev, num_text, x, y + 8);
}

void zmk_display_status_screen_update_cb(const struct device *dev) {
    if (dev == NULL) {
        return;
    }

    // Clear the display
    cfb_framebuffer_clear(dev, false);

    // VERTICAL LAYOUT - Optimized for 128x32 vertical orientation
    
    // === TOP SECTION: Bongo Cat (Lines 0-16) ===
    uint8_t mood_index = layer_moods[current_layer < 4 ? current_layer : 0];
    uint8_t expression_index = (mood_index + animation_frame) % EXPRESSION_COUNT;
    uint8_t activity_index = (animation_frame / 2) % ACTIVITY_COUNT;
    
    // Draw cat ears
    cfb_draw_text(dev, " /\\_/\\", 0, 0);
    
    // Draw cat face with current expression
    cfb_draw_text(dev, cat_expressions[expression_index], 0, 8);
    
    // Draw cat body with current activity
    cfb_draw_text(dev, cat_activities[activity_index], 0, 16);

    // === MIDDLE SECTION: Status Info (Lines 0-24, Right Side) ===
    
    // Connection status (top right)
    draw_connection_status(dev, 48, 0);
    
    // Battery with visual bar (middle right)
    draw_battery_bar(dev, battery_level, 48, 8);
    
    // Uptime (lower middle right)
    draw_uptime(dev, 48, 16);

    // === BOTTOM SECTION: Layer Status (Lines 24-32) ===
    
    // Layer info with enhanced styling
    draw_layer_status(dev, 0, 24);
    
    // Add some flair based on layer
    if (current_layer == 1) {
        cfb_draw_text(dev, "NUM/SYM", 48, 24);
    } else if (current_layer == 2) {
        cfb_draw_text(dev, "NAV/RGB", 48, 24);
    } else {
        cfb_draw_text(dev, "TYPING", 48, 24);
    }

    cfb_framebuffer_finalize(dev);
}

static int status_screen_listener(const zmk_event_t *eh) {
    if (as_zmk_layer_state_changed(eh)) {
        current_layer = zmk_keymap_highest_layer_active();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    if (as_zmk_battery_state_changed(eh)) {
        battery_level = zmk_battery_state_of_charge();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    if (as_zmk_ble_active_profile_changed(eh)) {
        bt_profile = zmk_ble_active_profile_index();
        bt_connected = zmk_ble_active_profile_is_connected();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    return ZMK_EV_EVENT_BUBBLE;
}

// Animation timer - updates expressions and activities
void animation_timer_handler(struct k_timer *timer_id) {
    animation_frame = (animation_frame + 1) % (EXPRESSION_COUNT * 2);
}

// Uptime timer - tracks how long the keyboard has been running
void uptime_timer_handler(struct k_timer *timer_id) {
    uptime_minutes++;
}

K_TIMER_DEFINE(animation_timer, animation_timer_handler, NULL);
K_TIMER_DEFINE(uptime_timer, uptime_timer_handler, NULL);

static int bongo_status_init(void) {
    // Initialize state
    current_layer = zmk_keymap_highest_layer_active();
    battery_level = zmk_battery_state_of_charge();
    bt_profile = zmk_ble_active_profile_index();
    bt_connected = zmk_ble_active_profile_is_connected();
    animation_frame = 0;
    uptime_minutes = 0;
    
    // Start timers
    k_timer_start(&animation_timer, K_MSEC(ANIMATION_INTERVAL_MS), K_MSEC(ANIMATION_INTERVAL_MS));
    k_timer_start(&uptime_timer, K_MINUTES(1), K_MINUTES(1));
    
    return 0;
}

ZMK_LISTENER(bongo_status_screen, status_screen_listener);
ZMK_SUBSCRIPTION(bongo_status_screen, zmk_layer_state_changed);
ZMK_SUBSCRIPTION(bongo_status_screen, zmk_battery_state_changed);
ZMK_SUBSCRIPTION(bongo_status_screen, zmk_ble_active_profile_changed);

SYS_INIT(bongo_status_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
