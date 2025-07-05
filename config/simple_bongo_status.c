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
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/keymap.h>
#include <zmk/battery.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static uint8_t current_layer = 0;
static uint8_t battery_level = 100;
static uint8_t animation_frame = 0;

// Timer-based bongo cat expressions
static const char* cat_expressions[] = {
    "(o.o)",  // Idle - calm
    "(^.^)",  // Happy - content 
    "(-.o)",  // Winking - playful
    "(@.@)",  // Alert - focused
    "(>.<)",  // Sleepy - tired
    "(*.*)"   // Sparkly - excited
};

static const char* cat_bodies[] = {
    " >.< ",  // Default
    " >^< ",  // Happy
    " >~< ",  // Focused
    " >!< ",  // Alert
    " >_< "   // Sleepy
};

#define EXPRESSION_COUNT 6
#define ANIMATION_INTERVAL_MS 3000  // Change expression every 3 seconds

void zmk_display_status_screen_update_cb(const struct device *dev) {
    if (dev == NULL) {
        return;
    }

    // Clear the display
    cfb_framebuffer_clear(dev, false);

    // Get current expression based on animation frame
    const char* expression = cat_expressions[animation_frame % EXPRESSION_COUNT];
    const char* body = cat_bodies[(animation_frame / 2) % 5];

    // Draw bongo cat in top-left
    cfb_draw_text(dev, " /\\_/\\ ", 0, 0);
    cfb_draw_text(dev, expression, 0, 8);
    cfb_draw_text(dev, body, 0, 16);

    // Draw layer info on right side
    char layer_text[16];
    snprintf(layer_text, sizeof(layer_text), "Layer:%d", current_layer);
    cfb_draw_text(dev, layer_text, 50, 0);

    // Draw battery info on second line
    char bat_text[16];
    snprintf(bat_text, sizeof(bat_text), "Bat:%d%%", battery_level);
    cfb_draw_text(dev, bat_text, 50, 8);

    // Draw status message on third line based on layer
    const char* status_msg;
    switch(current_layer) {
        case 0: status_msg = "QWERTY"; break;
        case 1: status_msg = "LOWER"; break;
        case 2: status_msg = "RAISE"; break;
        default: status_msg = "LAYER"; break;
    }
    cfb_draw_text(dev, status_msg, 50, 16);

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
    
    return ZMK_EV_EVENT_BUBBLE;
}

// Timer callback to update animation
void animation_timer_handler(struct k_timer *timer_id) {
    animation_frame = (animation_frame + 1) % (EXPRESSION_COUNT * 2);
}

K_TIMER_DEFINE(animation_timer, animation_timer_handler, NULL);

static int bongo_status_init(void) {
    // Initialize state
    current_layer = zmk_keymap_highest_layer_active();
    battery_level = zmk_battery_state_of_charge();
    animation_frame = 0;
    
    // Start animation timer
    k_timer_start(&animation_timer, K_MSEC(ANIMATION_INTERVAL_MS), K_MSEC(ANIMATION_INTERVAL_MS));
    
    return 0;
}

ZMK_LISTENER(bongo_status_screen, status_screen_listener);
ZMK_SUBSCRIPTION(bongo_status_screen, zmk_layer_state_changed);
ZMK_SUBSCRIPTION(bongo_status_screen, zmk_battery_state_changed);

SYS_INIT(bongo_status_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
