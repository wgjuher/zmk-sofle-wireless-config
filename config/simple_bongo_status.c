/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/display/cfb.h>

#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/wpm.h>
#include <zmk/keymap.h>
#include <zmk/battery.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static uint8_t current_wpm = 0;
static uint8_t current_layer = 0;
static uint8_t battery_level = 100;

// Simple bongo cat that changes based on WPM
static const char* get_cat_face(uint8_t wpm) {
    if (wpm >= 50) {
        return "(@.@)";  // Furious
    } else if (wpm >= 30) {
        return "(-.o)";  // Ready - winking
    } else if (wpm >= 10) {
        return "(^.^)";  // Tapping - happy
    } else {
        return "(o.o)";  // Idle
    }
}

void zmk_display_status_screen_update_cb(const struct device *dev) {
    if (dev == NULL) {
        return;
    }

    // Clear the display
    cfb_framebuffer_clear(dev, false);

    // Draw simple bongo cat in top-left
    cfb_draw_text(dev, " /\\_/\\ ", 0, 0);
    cfb_draw_text(dev, get_cat_face(current_wpm), 0, 8);
    cfb_draw_text(dev, " >.<  ", 0, 16);

    // Draw WPM info next to cat
    char wpm_text[16];
    snprintf(wpm_text, sizeof(wpm_text), "WPM:%d", current_wpm);
    cfb_draw_text(dev, wpm_text, 50, 0);

    // Draw layer info on second line
    char layer_text[16];
    snprintf(layer_text, sizeof(layer_text), "L:%d", current_layer);
    cfb_draw_text(dev, layer_text, 50, 8);

    // Draw battery info on third line
    char bat_text[16];
    snprintf(bat_text, sizeof(bat_text), "B:%d%%", battery_level);
    cfb_draw_text(dev, bat_text, 50, 16);

    cfb_framebuffer_finalize(dev);
}

static int status_screen_listener(const zmk_event_t *eh) {
    if (as_zmk_wpm_state_changed(eh)) {
        current_wpm = zmk_wpm_get_state();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    if (as_zmk_layer_state_changed(eh)) {
        current_layer = zmk_keymap_highest_layer_active();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    if (as_zmk_battery_state_changed(eh)) {
        battery_level = zmk_battery_state_of_charge();
        return ZMK_EV_EVENT_BUBBLE;
    }
    
    return ZMK_EV_EVENT_BUBBLE;
}

static int bongo_status_init(const struct device *dev) {
    current_wpm = zmk_wpm_get_state();
    current_layer = zmk_keymap_highest_layer_active();
    battery_level = zmk_battery_state_of_charge();
    return 0;
}

ZMK_LISTENER(bongo_status_screen, status_screen_listener);
ZMK_SUBSCRIPTION(bongo_status_screen, zmk_wpm_state_changed);
ZMK_SUBSCRIPTION(bongo_status_screen, zmk_layer_state_changed);
ZMK_SUBSCRIPTION(bongo_status_screen, zmk_battery_state_changed);

SYS_INIT(bongo_status_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
