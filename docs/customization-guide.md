# Sofle Keyboard Customization Guide

This guide will help you customize your Sofle keyboard firmware to better suit your needs and preferences.

## Table of Contents
- [Getting Started](#getting-started)
- [Basic Key Remapping](#basic-key-remapping)
- [Adding New Layers](#adding-new-layers)
- [Combos](#combos)
- [Tap-Dance](#tap-dance)
- [RGB Controls](#rgb-controls)
- [Encoder Customization](#encoder-customization)
- [Advanced Features](#advanced-features)

---

## Getting Started

### Prerequisites
1. Basic understanding of the ZMK keymap format
2. Text editor (VS Code recommended)
3. ZMK development environment (see `build-instructions.md`)

### File Structure
The main customization happens in:
- `config/sofle.keymap` - Main keymap configuration
- `config/sofle.conf` - Hardware configuration

---

## Basic Key Remapping

### Single Key Changes

To change a single key, locate it in the `bindings` array and replace it with your desired key code.

**Example**: Change Escape to Caps Lock
```c
// Original
&kp ESC

// Changed to
&kp CAPS
```

### Common Key Codes
```c
// Letters
&kp A, &kp B, &kp C, ... &kp Z

// Numbers
&kp N1, &kp N2, ... &kp N0

// Modifiers
&kp LSHFT, &kp RSHFT    // Left/Right Shift
&kp LCTRL, &kp RCTRL    // Left/Right Control
&kp LALT, &kp RALT      // Left/Right Alt
&kp LGUI, &kp RGUI      // Left/Right GUI (Windows/Cmd)

// Function Keys
&kp F1, &kp F2, ... &kp F12

// Special Keys
&kp SPACE, &kp ENTER, &kp TAB
&kp BSPC, &kp DEL
&kp UP, &kp DOWN, &kp LEFT, &kp RIGHT
&kp HOME, &kp END, &kp PG_UP, &kp PG_DN

// Layer Access
&mo 1      // Momentary layer 1 (hold)
&tog 1     // Toggle layer 1 (press)
&to 1      // Switch to layer 1 (permanent)
```

### Full Keycode Reference
For a complete list of ZMK key codes, visit: [ZMK Key Codes Documentation](https://zmk.dev/docs/codes)

---

## Adding New Layers

### Creating Layer 3

1. **Add the layer definition** after the existing layers:

```c
// Add this after the raise_layer block
layer_3 {
    label = "Gaming";
    bindings = <
        &kp ESC    &kp N1    &kp N2    &kp N3    &kp N4    &kp N5                          &kp N6    &kp N7    &kp N8    &kp N9    &kp N0    &none
        &kp TAB    &kp Q     &kp W     &kp E     &kp R     &kp T                           &kp Y     &kp U     &kp I     &kp O     &kp P     &kp BSPC
        &kp LSHFT  &kp A     &kp S     &kp D     &kp F     &kp G                           &kp H     &kp J     &kp K     &kp L     &kp SEMI  &kp SQT
        &kp LCTRL  &kp Z     &kp X     &kp C     &kp V     &kp B     &kp SPACE    &none    &kp N     &kp M     &kp COMMA &kp DOT   &kp FSLH  &kp RSHFT
                                       &kp LALT  &kp LGUI  &kp SPACE &mo 1        &kp ENTER &mo 2    &kp RCTRL &kp RALT  &kp RGUI
    >;
    
    sensor-bindings = <&inc_dec_kp C_VOL_UP C_VOL_DN &inc_dec_kp PG_UP PG_DN>;
};
```

2. **Add access to the new layer**:
   - Add a key to access layer 3 in one of your existing layers
   - Example: `&to 3` for permanent switch or `&tog 3` for toggle

---

## Combos

Combos allow multiple keys to trigger a single action when pressed simultaneously.

### Basic Combo Setup

1. **Add combo definitions** before the keymap block:

```c
/ {
    combos {
        compatible = "zmk,combos";
        
        // Escape combo (Q + W)
        combo_esc {
            timeout-ms = <50>;
            key-positions = <13 14>;  // Q and W positions
            bindings = <&kp ESC>;
        };
        
        // Tab combo (A + S)
        combo_tab {
            timeout-ms = <50>;
            key-positions = <25 26>;  // A and S positions
            bindings = <&kp TAB>;
        };
        
        // Gaming layer toggle (Z + X)
        combo_gaming {
            timeout-ms = <50>;
            key-positions = <37 38>;  // Z and X positions
            bindings = <&tog 3>;
        };
    };
    
    keymap {
        // ... existing keymap
    };
};
```

### Key Position Reference

To find key positions, count from 0 starting at top-left:

```
Left Half:                    Right Half:
0   1   2   3   4   5         6   7   8   9  10  11
12 13  14  15  16  17        18  19  20  21  22  23
24 25  26  27  28  29        30  31  32  33  34  35
36 37  38  39  40  41  42    43  44  45  46  47  48  49
            50  51  52  53    54  55  56  57  58
```

---

## Tap-Dance

Tap-dance allows a single key to perform different actions based on the number of taps.

### Basic Tap-Dance Setup

1. **Define tap-dance behaviors**:

```c
/ {
    behaviors {
        // Shift on hold, Caps Lock on double-tap
        td_shift_caps: tap_dance_shift_caps {
            compatible = "zmk,behavior-tap-dance";
            label = "TAP_DANCE_SHIFT_CAPS";
            #binding-cells = <0>;
            tapping-term-ms = <200>;
            bindings = <&kp LSHFT>, <&kp CAPS>;
        };
        
        // Layer 1 on single tap, Layer 3 on double tap
        td_layers: tap_dance_layers {
            compatible = "zmk,behavior-tap-dance";
            label = "TAP_DANCE_LAYERS";
            #binding-cells = <0>;
            tapping-term-ms = <200>;
            bindings = <&mo 1>, <&tog 3>;
        };
    };
    
    keymap {
        // ... use &td_shift_caps or &td_layers in your bindings
    };
};
```

2. **Use in keymap**:
   Replace `&kp LSHFT` with `&td_shift_caps` in your bindings.

---

## RGB Controls

### Adding RGB Controls to Raise Layer

Replace some unused keys in the raise layer with RGB controls:

```c
// In raise_layer bindings, replace some &trans with:
&rgb_ug RGB_TOG   // RGB toggle on/off
&rgb_ug RGB_HUI   // Hue increase
&rgb_ug RGB_HUD   // Hue decrease
&rgb_ug RGB_SAI   // Saturation increase
&rgb_ug RGB_SAD   // Saturation decrease
&rgb_ug RGB_BRI   // Brightness increase
&rgb_ug RGB_BRD   // Brightness decrease
&rgb_ug RGB_EFF   // Effect increase (next animation)
&rgb_ug RGB_EFR   // Effect decrease (previous animation)
```

### RGB Configuration

In `config/sofle.conf`, uncomment and modify:

```conf
# RGB Configuration
CONFIG_ZMK_RGB_UNDERGLOW=y
CONFIG_WS2812_STRIP=y
CONFIG_ZMK_RGB_UNDERGLOW_EXT_POWER=y
CONFIG_ZMK_RGB_UNDERGLOW_AUTO_OFF_IDLE=y
```

---

## Encoder Customization

### Changing Encoder Functions

In each layer's `sensor-bindings`:

```c
// Volume control (default)
sensor-bindings = <&inc_dec_kp C_VOL_UP C_VOL_DN &inc_dec_kp PG_UP PG_DN>;

// Brightness control
sensor-bindings = <&inc_dec_kp C_BRI_UP C_BRI_DN &inc_dec_kp PG_UP PG_DN>;

// Zoom control
sensor-bindings = <&inc_dec_kp C_AC_ZOOM_IN C_AC_ZOOM_OUT &inc_dec_kp PG_UP PG_DN>;

// Horizontal scroll
sensor-bindings = <&inc_dec_kp C_VOL_UP C_VOL_DN &inc_dec_kp RIGHT LEFT>;
```

### Layer-Specific Encoder Functions

Each layer can have different encoder functions:

```c
default_layer {
    // ... bindings
    sensor-bindings = <&inc_dec_kp C_VOL_UP C_VOL_DN &inc_dec_kp PG_UP PG_DN>;
};

lower_layer {
    // ... bindings
    sensor-bindings = <&inc_dec_kp C_BRI_UP C_BRI_DN &inc_dec_kp HOME END>;
};

raise_layer {
    // ... bindings
    sensor-bindings = <&inc_dec_kp C_AC_ZOOM_IN C_AC_ZOOM_OUT &inc_dec_kp TAB LS(TAB)>;
};
```

---

## Advanced Features

### Hold-Tap (Mod-Tap)

Keys that act as modifiers when held, regular keys when tapped:

```c
/ {
    behaviors {
        // Space on tap, Shift on hold
        space_shift: space_shift {
            compatible = "zmk,behavior-hold-tap";
            label = "SPACE_SHIFT";
            #binding-cells = <2>;
            flavor = "tap-preferred";
            tapping-term-ms = <200>;
            bindings = <&kp>, <&kp>;
        };
    };
    
    keymap {
        default_layer {
            bindings = <
                // ... other keys
                &space_shift LSHFT SPACE  // Use instead of &kp SPACE
                // ... other keys
            >;
        };
    };
};
```

### Sticky Keys

Keys that remain pressed until another key is pressed:

```c
&sk LSHFT    // Sticky shift
&sk LCTRL    // Sticky control
&sk LALT     // Sticky alt
```

### One Shot Layers

Layers that activate for just one keypress:

```c
&sl 1        // One-shot layer 1
&sl 2        // One-shot layer 2
```

---

## Testing and Debugging

### Local Testing
1. Build firmware locally (see `build-instructions.md`)
2. Flash to keyboard
3. Test all modified keys
4. Check for any compilation errors

### Common Issues
- **Key not working**: Check key code spelling and syntax
- **Layer not accessible**: Ensure layer access keys are properly defined
- **Combos not triggering**: Verify key positions and timing
- **RGB not working**: Check configuration file settings

### Validation Tools
- Use ZMK's online keymap editor for syntax checking
- Enable logging for debugging complex behaviors

---

## Example Customizations

### Gaming Setup
```c
// Dedicated gaming layer with WASD, number row, and common gaming keys
gaming_layer {
    label = "Gaming";
    bindings = <
        &kp ESC    &kp N1    &kp N2    &kp N3    &kp N4    &kp N5                    &none     &none     &none     &none     &none     &to 0
        &kp TAB    &kp Q     &kp W     &kp E     &kp R     &kp T                     &none     &none     &none     &none     &none     &none
        &kp LSHFT  &kp A     &kp S     &kp D     &kp F     &kp G                     &none     &none     &none     &none     &none     &none
        &kp LCTRL  &kp Z     &kp X     &kp C     &kp V     &kp B     &none    &none  &none     &none     &none     &none     &none     &none
                                       &kp LALT  &kp LGUI  &kp SPACE &none    &none  &none     &none     &none     &none
    >;
};
```

### Programmer Setup
```c
// Enhanced symbol layer for programming
prog_layer {
    label = "Programming";
    bindings = <
        &kp GRAVE  &kp F1    &kp F2    &kp F3    &kp F4    &kp F5                    &kp F6    &kp F7    &kp F8    &kp F9    &kp F10   &kp F11
        &kp TILDE  &kp EXCL  &kp AT    &kp HASH  &kp DLLR  &kp PRCNT                 &kp CARET &kp AMPS  &kp ASTRK &kp LPAR  &kp RPAR  &kp F12
        &trans     &kp UNDER &kp MINUS &kp PLUS  &kp EQUAL &kp PIPE                  &kp BSLH  &kp LBRC  &kp RBRC  &kp LBKT  &kp RBKT  &kp DQT
        &trans     &trans    &trans    &kp LT    &kp GT    &kp QMARK &trans   &trans &trans    &trans    &kp SEMI  &kp COLON &trans    &trans
                                       &trans    &trans    &trans    &trans   &trans &trans    &trans    &trans    &trans
    >;
};
```

Save your changes and build/flash the firmware to test your customizations!
