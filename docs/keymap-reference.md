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

The keymap consists of 4 layers:
- **Layer 0**: Default (Dvorak base layer)
- **Layer 1**: Lower (Numbers, symbols, function keys)
- **Layer 2**: Raise (Navigation, Bluetooth, system controls)
- **Layer 3**: Adjust (Advanced RGB controls, system settings)

---

## Layer 0: Default (Dvorak)

**Activation**: Default layer (always active)

┌─────┬─────┬─────┬─────┬─────┬─────┐                    ┌─────┬─────┬─────┬─────┬─────┬─────┐
│  `  │  1  │  2  │  3  │  4  │  5  │                    │  6  │  7  │  8  │  9  │  0  │  -  │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│ ESC │  '  │  ,  │  .  │  P  │  Y  │                    │  F  │  G  │  C  │  R  │  L  │BKSPC│
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  A  │  O  │  E  │  U  │  I  │                    │  D  │  H  │  T  │  N  │  S  │  /  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐        ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│SHIFT│  ;  │  Q  │  J  │  K  │  X  │MUTE │        │     │  B  │  M  │  W  │  V  │  Z  │SHIFT│
└─────┴─────┴─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┴─────┴─────┴─────┘
                  │ GUI │ ALT │CTRL │LOWER│        │RAISE│RCTRL│RALT │RGUI │
                  │     │     │     │     │        │     │     │     │     │
                  └─────┴─────┴─────┼─────┤        ├─────┼─────┴─────┴─────┘
                                    │SPACE│        │ RET │
                                    └─────┘        └─────┘

### Key Functions
- **Dvorak Layout**: Optimized for typing efficiency with vowels on the left home row
- **Escape**: Top left for quick access
- **Tab**: Standard position for window/field navigation
- **Shift**: Both sides for comfortable typing
- **Modifiers**: GUI (Windows/Cmd), Alt, Ctrl on both sides
- **Layer Access**: 
  - `LOWER` (hold): Access Layer 1 (symbols/functions)
  - `RAISE` (hold): Access Layer 2 (navigation/system)
  - `LOWER + RAISE` (hold both): Access Layer 3 (adjust/advanced)
- **Encoders**:
  - Left: Volume Up/Down
  - Right: Page Up/Down

---

## Layer 1: Lower (Symbols & Functions)

**Activation**: Hold `LOWER` key (bottom left thumb key)

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

┌─────┬─────┬─────┬─────┬─────┬─────┐                    ┌─────┬─────┬─────┬─────┬─────┬─────┐
│BTCLR│ BT1 │ BT2 │ BT3 │ BT4 │ BT5 │                    │RGB↕ │RGB+ │RGB- │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ INS │PSCR │MENU │     │     │                    │PGUP │     │  ↑  │     │  0  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ ALT │CTRL │SHIFT│     │CAPS │                    │PGDN │  ←  │  ↓  │  →  │ DEL │BKSPC│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐        ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │UNDO │ CUT │COPY │PASTE│     │     │        │     │     │     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┴─────┴─────┴─────┘
                  │     │     │     │     │        │▓▓▓▓▓│     │     │     │
                  │     │     │     │     │        │▓▓▓▓▓│     │     │     │
                  └─────┴─────┴─────┼─────┤        ├─────┼─────┴─────┴─────┘
                                    │     │        │     │
                                    └─────┘        └─────┘

### Key Functions
- **Bluetooth Controls** (Top Row Left):
  - `BTCLR`: Clear all Bluetooth pairings
  - `BT1-BT5`: Switch to Bluetooth device 1-5
- **RGB Basic Controls** (Top Row Right):
  - `RGB↕`: Toggle RGB brightness (custom macro)
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

## Layer 3: Adjust (Advanced RGB & System)

**Activation**: Hold `LOWER + RAISE` keys simultaneously (conditional layer)

┌─────┬─────┬─────┬─────┬─────┬─────┐                    ┌─────┬─────┬─────┬─────┬─────┬─────┐
│BTCLR│ BT1 │ BT2 │ BT3 │ BT4 │ BT5 │                    │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│EXTPW│RGB_H│RGB_H│RGB_S│RGB_S│RGB_E│                    │     │     │     │     │     │     │
│ TOG │ DWN │ UP  │ DWN │ UP  │ FF  │                    │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤                    ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │RGB_B│RGB_B│     │     │     │                    │     │     │     │     │     │     │
│     │ DWN │ UP  │     │     │     │                    │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┐        ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │RGB_T│        │     │     │     │     │     │     │     │
│     │     │     │     │     │     │ OG  │        │     │     │     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┼─────┤        ├─────┼─────┼─────┼─────┴─────┴─────┴─────┘
                  │▓▓▓▓▓│▓▓▓▓▓│▓▓▓▓▓│▓▓▓▓▓│        │▓▓▓▓▓│▓▓▓▓▓│▓▓▓▓▓│▓▓▓▓▓│
                  │▓▓▓▓▓│▓▓▓▓▓│▓▓▓▓▓│▓▓▓▓▓│        │▓▓▓▓▓│▓▓▓▓▓│▓▓▓▓▓│▓▓▓▓▓│
                  └─────┴─────┴─────┼─────┤        ├─────┼─────┴─────┴─────┘
                                    │▓▓▓▓▓│        │▓▓▓▓▓│
                                    └─────┘        └─────┘

### Key Functions
- **Bluetooth Controls** (Top Row):
  - `BTCLR`: Clear all Bluetooth pairings
  - `BT1-BT5`: Switch to Bluetooth device 1-5
- **Advanced RGB Controls**:
  - `EXTPW TOG`: Toggle external power for RGB
  - `RGB_H DWN/UP`: Decrease/Increase RGB hue (color)
  - `RGB_S DWN/UP`: Decrease/Increase RGB saturation (intensity)
  - `RGB_EFF`: Cycle through RGB effects/patterns
  - `RGB_B DWN/UP`: Decrease/Increase RGB brightness
  - `RGB_TOG`: Toggle RGB underglow on/off
- **Layer Activation**: Both `LOWER` and `RAISE` keys are highlighted (▓▓▓▓▓) as this layer requires both to be held

### Usage Examples
- **Change RGB Color**: Hold `LOWER + RAISE`, then use `RGB_H UP/DWN` for hue and `RGB_S UP/DWN` for saturation
- **Switch Bluetooth Device**: Hold `LOWER + RAISE`, then press `BT1-BT5` to switch profiles
- **Reset Bluetooth**: Hold `LOWER + RAISE`, then press `BTCLR` to clear all pairings

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

The Sofle keyboard uses the standard nice!nano display system for reliable operation and maximum compatibility.

### OLED Display Configuration

The display is configured in `sofle.conf`:

```
CONFIG_ZMK_DISPLAY=y
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_BUILT_IN=y
```

This enables:
- OLED display support
- Built-in ZMK display system (reliable and stable)
- Standard status information display

### Display Layout

The 128x32 OLED displays show standard ZMK information:
- **Current Layer**: Active layer indicator
- **Battery Status**: Battery level percentage
- **Bluetooth Status**: Connection state and active profile
- **Caps Lock Status**: Caps lock indicator when active
- **System Status**: Various system state indicators

**Benefits of Built-in Display System:**
- **Reliability**: Stable operation without custom code complications
- **Compatibility**: Works with all ZMK features and updates
- **Low Maintenance**: No custom display code to maintain
- **Battery Efficient**: Optimized power consumption

---

## Bluetooth Pairing

1. **Clear existing pairings**: Hold `LOWER + RAISE` + `BTCLR` (or just `RAISE` + `BTCLR`)
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

RGB underglow is enabled by default with 35 WS2812 LEDs. Controls are available on both the raise and adjust layers:

### Basic RGB Controls (Raise Layer)
- **Toggle Brightness**: `RAISE` + `RGB↕` - Custom brightness toggle macro
- **Brightness**: `RAISE` + `RGB+` / `RGB-` - Adjust brightness levels

### Advanced RGB Controls (Adjust Layer)
- **Full Control**: `LOWER + RAISE` + various RGB keys for complete customization
- **Hue Control**: Adjust color with `RGB_H UP/DWN`
- **Saturation Control**: Adjust color intensity with `RGB_S UP/DWN`
- **Effect Patterns**: Cycle through effects with `RGB_EFF`
- **Power Management**: Toggle external power with `EXTPW TOG`

**Usage:**
1. **Basic**: Hold `RAISE` key and press RGB controls for quick adjustments
2. **Advanced**: Hold `LOWER + RAISE` together for full RGB customization
3. **Power Saving**: Use `EXTPW TOG` in adjust layer to manage power consumption

**Note:** RGB underglow may impact battery life on wireless usage.

---

## Dvorak Layout Benefits

The Dvorak keyboard layout offers several advantages over QWERTY:

### Typing Efficiency
- **Vowels on Left Home Row**: A, O, E, U, I are easily accessible
- **Common Consonants on Right Home Row**: D, H, T, N, S for frequent combinations
- **Reduced Finger Movement**: More efficient finger travel patterns
- **Better Hand Alternation**: Improved rhythm and reduced strain

### Key Positions
- **Frequent Letters**: Most common letters are on the home row
- **Punctuation**: Comma and period are easily accessible
- **Numbers**: Standard number row layout maintained for familiarity

---

## Customization Notes

- **Layer modifications**: Each layer is clearly separated in the keymap file
- **Key remapping**: Individual keys can be easily modified
- **Additional layers**: New layers can be added (Layer 4, 5, etc.)
- **Combos**: Key combinations can be added for special functions
- **Tap-dance**: Single key can perform multiple functions based on tap count
- **Conditional Layers**: The adjust layer demonstrates automatic layer activation

For customization instructions, see `customization-guide.md`.
