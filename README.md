# Sofle Keyboard ZMK Firmware

A complete ZMK firmware configuration for the Sofle split keyboard with Nice!Nano wireless controllers.

[![Build](https://github.com/YOUR_USERNAME/zmk-sofle-firmware/actions/workflows/build.yml/badge.svg)](https://github.com/YOUR_USERNAME/zmk-sofle-firmware/actions/workflows/build.yml)

## 🎯 Quick Start

1. **Fork this repository** to your GitHub account
2. **Make changes** to the keymap in `config/sofle.keymap`
3. **Commit and push** your changes
4. **Download firmware** from the Actions tab
5. **Flash firmware** to your Nice!Nano controllers

## 📋 Hardware Requirements

- **Keyboard**: Sofle split keyboard PCBs
- **Controllers**: 2x Nice!Nano v2 (nRF52840)
- **Features**: 
  - 58 keys total (29 per half)
  - 2x rotary encoders
  - RGB underglow support (35 LEDs)
  - Wireless connectivity via Bluetooth 5.0

## 🗂️ Repository Structure

```
zmk-sofle-firmware/
├── config/
│   ├── sofle.keymap          # Main keymap configuration
│   ├── sofle.conf            # Hardware configuration  
│   └── west.yml              # ZMK dependency manifest
├── docs/
│   ├── keymap-reference.md   # Visual keymap documentation
│   ├── customization-guide.md # How to customize your keymap
│   └── build-instructions.md # Building and flashing guide
├── .github/
│   └── workflows/
│       └── build.yml         # Automated firmware builds
└── README.md                 # This file
```

## 🔧 Current Layout

### Layer 0: Default (QWERTY)
Standard QWERTY layout with modifiers and layer access keys.

### Layer 1: Lower (Symbols & Functions) 
Function keys F1-F12, numbers, and programming symbols.

### Layer 2: Raise (Navigation & System)
Bluetooth controls, arrow keys, and system functions.

## 📖 Documentation

- **[Keymap Reference](docs/keymap-reference.md)** - Visual layout and key functions
- **[Customization Guide](docs/customization-guide.md)** - How to modify your keymap
- **[Build Instructions](docs/build-instructions.md)** - Building and flashing firmware

## 🚀 Getting Firmware

### GitHub Actions (Recommended)
1. Fork this repository
2. Make changes to your keymap
3. Push changes to trigger builds
4. Download artifacts from Actions tab

### Local Building
See [Build Instructions](docs/build-instructions.md) for setting up a local development environment.

## 🔄 Flashing Firmware

1. **Enter bootloader**: Double-tap reset button on Nice!Nano
2. **Copy firmware**: Drag `.uf2` file to NICENANO drive
3. **Repeat**: Flash both left and right halves
4. **Pair**: Controllers will automatically connect

## ⌨️ Key Features

- **3-layer layout** optimized for programming and productivity
- **Bluetooth connectivity** with 5 device profiles
- **RGB underglow** with customizable effects
- **Rotary encoders** for volume and page navigation
- **Low power consumption** with sleep modes
- **Wireless split** with automatic half synchronization

## 🎨 Customization

This firmware supports extensive customization:

- **Key remapping** - Change any key function
- **Layer modification** - Add new layers or modify existing ones
- **Combos** - Multiple keys triggering single actions
- **Tap-dance** - Multiple functions per key based on tap count
- **RGB controls** - Custom lighting patterns and colors
- **Encoder functions** - Custom rotary encoder behaviors

See the [Customization Guide](docs/customization-guide.md) for detailed instructions.

## 🔋 Battery Life

Typical battery life with 110mAh batteries:
- **Typing only**: 1-2 months
- **With RGB**: 1-2 weeks  
- **Heavy RGB use**: 3-7 days

Power saving features:
- Automatic sleep after 15 minutes idle
- Deep sleep after 12 hours idle
- RGB auto-off when idle (configurable)

## 🔗 Bluetooth Profiles

The firmware supports 5 Bluetooth profiles:
- **BT1**: Primary computer/workstation
- **BT2**: Secondary computer/laptop  
- **BT3**: Mobile device/tablet
- **BT4**: Additional device
- **BT5**: Additional device

Switch profiles using `RAISE` + `BT1-BT5` keys.

## 🛠️ Troubleshooting

### Common Issues

**Halves not connecting**:
1. Clear Bluetooth bonds: `RAISE` + `BTCLR`
2. Reset both controllers
3. Wait 30 seconds for reconnection

**Keys not working**:
- Check keymap syntax in config files
- Verify firmware flashed successfully
- Test with simple keymap

**RGB not working**:
- Check `sofle.conf` RGB settings
- Verify power connections
- Check LED strip configuration

### Getting Help

- **[ZMK Documentation](https://zmk.dev/docs)**
- **[ZMK Discord](https://zmk.dev/community/discord/invite)**
- **[Issues](https://github.com/YOUR_USERNAME/zmk-sofle-firmware/issues)** - Report bugs or request features

## 📜 License

This project is licensed under the MIT License - see the ZMK project for details.

## 🙏 Acknowledgments

- **[ZMK Firmware](https://github.com/zmkfirmware/zmk)** - The wireless keyboard firmware
- **[Sofle Keyboard](https://github.com/josefadamcik/SofleKeyboard)** - Original keyboard design
- **[nice!nano](https://nicekeyboards.com/nice-nano/)** - Wireless controller boards
- **Original vendor config** - Based on [klee813's configuration](https://github.com/klee813/zmk-config-sofle)

---

## 📝 Quick Configuration Changes

Here are some common modifications you might want to make:

### Change a Key
Edit `config/sofle.keymap` and replace the key code:
```c
&kp ESC    // Original
&kp CAPS   // Changed to Caps Lock
```

### Add RGB Controls
Uncomment RGB settings in `config/sofle.conf`:
```conf
CONFIG_ZMK_RGB_UNDERGLOW=y
CONFIG_WS2812_STRIP=y
```

### Switch Encoder Functions
Modify `sensor-bindings` in each layer:
```c
// Volume control (default)
sensor-bindings = <&inc_dec_kp C_VOL_UP C_VOL_DN &inc_dec_kp PG_UP PG_DN>;

// Brightness control  
sensor-bindings = <&inc_dec_kp C_BRI_UP C_BRI_DN &inc_dec_kp PG_UP PG_DN>;
```

Happy typing! 🎹✨
