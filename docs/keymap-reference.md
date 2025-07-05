# Sofle Keyboard Keymap Reference

This document provides a comprehensive reference for the Sofle keyboard keymap configuration. The Sofle is a 58-key split keyboard with rotary encoders and RGB underglow support.

## Hardware Overview

- **MCU**: Nice!Nano (nRF52840)
- **Layout**: 58 keys split across two halves
- **Encoders**: 2x rotary encoders (one per half)
- **RGB**: WS2812 RGB underglow (35 LEDs)
- **Wireless**: Bluetooth Low Energy
- **Battery**: Support for LiPo batteries

## Layer Overview

The keymap consists of 3 layers:
- **Layer 0**: Default (QWERTY base layer)
- **Layer 1**: Lower (Numbers, symbols, function keys)
- **Layer 2**: Raise (Navigation, Bluetooth, system controls)

---

## Layer 0: Default (QWERTY)

**Activation**: Default layer (always active)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                    ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  `  │  1  │  2  │  3  │  4  │  5  │                    │  6  │  7  │  8  │  9  │  0  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│ ESC │  Q  │  W  │  E  │  R  │  T  │                    │  Y  │  U  │  I  │  O  │  P  │BKSPC│
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  A  │  S  │  D  │  F  │  G  │                    │  H  │  J  │  K  │  L  │  ;  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐        ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│SHIFT│  Z  │  X  │  C  │  V  │  B  │MUTE │        │     │  N  │  M  │  ,  │  .  │  /  │SHIFT│
└─────┴─────┴─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┴─────┴─────┴─────┘
                  │ GUI │ ALT │CTRL │LOWER│        │SPACE│RAISE│CTRL │ ALT │
                  │     │     │     │     │        │     │     │     │ GUI │
                  └─────┴─────┴─────┼─────┤        ├─────┼─────┴─────┴─────┘
                                    │ENTER│        │     │
                                    └─────┘        └─────┘
```

### Key Functions
- **Standard QWERTY**: All letters and numbers in standard positions
- **Escape**: Top left for quick access
- **Tab**: Standard position for window/field navigation
- **Shift**: Both sides for comfortable typing
- **Modifiers**: GUI (Windows/Cmd), Alt, Ctrl on both sides
- **Layer Access**: 
  - `LOWER` (hold): Access Layer 1 (symbols/functions)
  - `RAISE` (hold): Access Layer 2 (navigation/system)
- **Encoders**:
  - Left: Volume Up/Down
  - Right: Page Up/Down

---

## Layer 1: Lower (Symbols & Functions)

**Activation**: Hold `LOWER` key (bottom left thumb key)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                    ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │ F1  │ F2  │ F3  │ F4  │ F5  │                    │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│  `  │  1  │  2  │  3  │  4  │  5  │                    │  6  │  7  │  8  │  9  │  0  │ F12 │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  !  │  @  │  #  │  $  │  %  │                    │  ^  │  &  │  *  │  (  │  )  │  |  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐        ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │  =  │  -  │  +  │  {  │  }  │     │        │     │  [  │  ]  │  ;  │  :  │  \  │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┴─────┴─────┴─────┘
                  │     │     │     │▓▓▓▓▓│        │     │     │     │     │
                  │     │     │     │▓▓▓▓▓│        │     │     │     │     │
                  └─────┴─────┴─────┼─────┤        ├─────┼─────┴─────┴─────┘
                                    │     │        │     │
                                    └─────┘        └─────┘
```

### Key Functions
- **Function Keys**: F1-F12 across top row
- **Numbers**: 1-0 for easy number entry
- **Symbols**: Common programming symbols
  - `!@#$%` on left side
  - `^&*()` on right side
  - `{}[]` for brackets
  - `=+-` for math operations
  - `|:\` for special characters
- **Layer Lock**: The `LOWER` key is highlighted (▓▓▓▓▓) as it's the activation key

---

## Layer 2: Raise (Navigation & System)

**Activation**: Hold `RAISE` key (bottom right thumb key)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐                    ┌─────┬─────┬─────┬─────┬─────┬─────┐
│BTCLR│ BT1 │ BT2 │ BT3 │ BT4 │ BT5 │                    │RGBTOG│RGB+ │RGB- │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ INS │PSCR │MENU │     │     │                    │PGUP │     │  ↑  │     │  0  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ALT │CTRL │SHIFT│     │CAPS │                    │PGDN │  ←  │  ↓  │  →  │ DEL │BKSPC│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐        ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │UNDO │ CUT │COPY │PASTE│     │     │        │     │     │     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┴─────┴─────┴─────┘
                  │     │     │     │     │        │     │▓▓▓▓▓│     │     │
                  │     │     │     │     │        │     │▓▓▓▓▓│     │     │
                  └─────┴─────┴─────┼─────┤        ├─────┼─────┴─────┴─────┘
                                    │     │        │     │
                                    └─────┘        └─────┘
```

### Key Functions
- **Bluetooth Controls** (Top Row Left):
  - `BTCLR`: Clear all Bluetooth pairings
  - `BT1-BT5`: Switch to Bluetooth device 1-5
- **RGB Underglow Controls** (Top Row Right):
  - `RGBTOG`: Toggle RGB underglow on/off
  - `RGB+`: Increase brightness
  - `RGB-`: Decrease brightness
- **System Functions**:
  - `INS`: Insert key
  - `PSCR`: Print Screen
  - `MENU`: Context menu key
  - `CAPS`: Caps Lock toggle
- **Navigation**:
  - Arrow keys: `↑↓←→` in standard inverted-T layout
  - `PGUP`/`PGDN`: Page navigation
- **Editing**:
  - `UNDO`/`CUT`/`COPY`/`PASTE`: Common editing shortcuts
  - `DEL`/`BKSPC`: Delete functions
- **Modifiers**: 
  - Individual `ALT`/`CTRL`/`SHIFT` for one-handed shortcuts
- **Layer Lock**: The `RAISE` key is highlighted (▓▓▓▓▓) as it's the activation key

---

## Encoder Functions

### Left Encoder (Master Side)
- **Default Layer**: Volume Up/Down
- **All Layers**: Volume Up/Down (consistent across layers)

### Right Encoder (Slave Side)
- **Default Layer**: Page Up/Down
- **All Layers**: Page Up/Down (consistent across layers)

---

## Display Features

The Sofle keyboard supports OLED displays with an animated bongo cat that responds to your typing speed! The display shows:

- **Animated Bongo Cat**: ASCII art cat that changes based on your WPM
  - **Idle** (0 WPM): Calm sitting cat
  - **Tapping** (10+ WPM): Cat starts moving
  - **Ready** (30+ WPM): Cat prepares for intense typing
  - **Furious** (50+ WPM): Cat goes crazy with rapid animation!
- **WPM Tracking**: Real-time words per minute display
- **Layer Information**: Current active layer indicator  
- **Battery Status**: Battery level percentage
- **Typing State**: Current activity level indicator

### OLED Display Configuration

The bongo cat display is configured in `sofle.conf`:

```
CONFIG_ZMK_DISPLAY=y
CONFIG_ZMK_WPM=y
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=y
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=n
```

This enables:
- OLED display support
- WPM (Words Per Minute) tracking for the bongo cat animation
- Custom status screen with bongo cat instead of the built-in display

### Display Layout

The 128x32 OLED displays show:
```
┌──────────────────────────────────────┐
│ /\_/\     WPM: 42                    │
│( ^.^ )    Tapping                    │
│ \ ˇ /                                │
│   !                                  │
│ L:0  B:85%                           │
└──────────────────────────────────────┘
```

**Left Side**: Animated bongo cat (changes based on typing speed)  
**Right Side**: WPM counter and current state  
**Bottom**: Layer number and battery percentage

---

## Bluetooth Pairing

1. **Clear existing pairings**: Hold `RAISE` + `BTCLR`
2. **Pair new device**: Hold `RAISE` + `BT1` (or BT2-BT5 for additional devices)
3. **Switch devices**: Hold `RAISE` + `BT1-BT5` to switch between paired devices

### Bluetooth Profiles
- **Profile 1** (`BT1`): Primary computer/device
- **Profile 2** (`BT2`): Secondary computer/device
- **Profile 3** (`BT3`): Mobile device/tablet
- **Profile 4** (`BT4`): Additional device
- **Profile 5** (`BT5`): Additional device

---

## RGB Underglow

RGB underglow is enabled by default with 35 WS2812 LEDs. The following controls are available on the raise layer:

**Available Controls:**
- **Toggle**: `RAISE` + `RGBTOG` - Turn underglow on/off
- **Brightness**: `RAISE` + `RGB+` / `RGB-` - Adjust brightness levels
- **Additional controls** can be added:
  - Color cycling with `RGB_HUI` / `RGB_HUD`
  - Effect patterns with `RGB_EFF`
  - Saturation adjustment with `RGB_SAI` / `RGB_SAD`

**Usage:**
1. Hold `RAISE` key
2. Press `RGBTOG` to toggle underglow on/off
3. Press `RGB+` or `RGB-` to adjust brightness
4. Release `RAISE` to return to normal typing

**Note:** RGB underglow may impact battery life on wireless usage.

---

## Customization Notes

- **Layer modifications**: Each layer is clearly separated in the keymap file
- **Key remapping**: Individual keys can be easily modified
- **Additional layers**: New layers can be added (Layer 3, 4, etc.)
- **Combos**: Key combinations can be added for special functions
- **Tap-dance**: Single key can perform multiple functions based on tap count

For customization instructions, see `customization-guide.md`.
