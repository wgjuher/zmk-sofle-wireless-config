# Sofle ZMK Firmware

This repository contains a complete ZMK firmware setup for the Sofle split keyboard with Nice!Nano controllers, featuring a **Dvorak layout** with advanced 4-layer system and custom RGB controls.

## ⌨️ Features

- **Dvorak Layout**: Hardware-level Dvorak layout for ergonomic typing
- **4-Layer Keymap**: Dvorak base, symbols/functions, navigation/system, and conditional adjust layers
- **Custom RGB Controls**: RGB brightness toggle macro with shift-morph behavior
- **Conditional Adjust Layer**: Automatic activation when Lower + Raise are held together
- **OLED Status Displays**: Working OLED displays showing layer, battery, and connection status
- **Stable Configuration**: Tested and verified to build successfully
- **RGB Underglow**: 35 WS2812 LEDs with customizable effects
- **Rotary Encoder Support**: Volume and page navigation
- **Bluetooth LE**: Connect up to 5 devices
- **Battery Monitoring**: Real-time battery level display
- **Safe & Stable**: Uses proper ZMK display integration

## 🚀 Quick Start

1. **Fork this repository** to your GitHub account
2. **Enable GitHub Actions** in your fork
3. **Wait for the build** to complete (about 5-10 minutes)
4. **Download the firmware** from the Actions tab
5. **Flash the firmware** to your Nice!Nano controllers

## 📁 Repository Structure

```
├── config/
│   ├── sofle.keymap          # Main keymap configuration (Dvorak)
│   ├── sofle.conf            # Hardware configuration
│   ├── west.yml              # ZMK dependencies
│   └── CMakeLists.txt        # Build configuration
├── docs/
│   └── keymap-reference.md   # Complete keymap documentation
├── Scripts/
│   └── dev-helper.sh         # Development helper script
├── Firmware/                 # Pre-built firmware files
│   ├── Current_Firmware/     # Latest builds
│   └── Backup_Firmware/      # Backup versions
├── ADJUST_LAYER_GUIDE.md     # Conditional adjust layer documentation
├── DEVELOPMENT.md            # Local development setup guide
├── build.yaml               # GitHub Actions build matrix
└── README.md                # This file
```

## 🎹 Layer System

This firmware features a sophisticated **4-layer system**:

1. **Layer 0 (Dvorak)**: Main typing layer with Dvorak layout
2. **Layer 1 (Lower)**: Numbers, symbols, and function keys  
3. **Layer 2 (Raise)**: Navigation, bluetooth, and RGB controls
4. **Layer 3 (Adjust)**: Advanced RGB and system settings (auto-activated by Lower + Raise)

### Accessing Layers
- **Lower Layer**: Hold the left thumb Lower key
- **Raise Layer**: Hold the right thumb Raise key  
- **Adjust Layer**: Hold **both** Lower + Raise keys simultaneously (conditional activation)

For detailed layer documentation, see [ADJUST_LAYER_GUIDE.md](ADJUST_LAYER_GUIDE.md).

## 🔧 Customization

### Changing the Keymap
Edit `config/sofle.keymap` to modify key assignments. The current keymap uses **Dvorak layout** for ergonomic typing. See [keymap-reference.md](docs/keymap-reference.md) for detailed layer documentation.

### Custom RGB Brightness Toggle
This firmware includes a custom **RGB brightness macro** with shift-morph behavior:
- **Normal press**: `RAISE + RGB↕` - Dims RGB to minimum brightness
- **Shift + press**: `SHIFT + RAISE + RGB↕` - Restores RGB to bright level

This macro provides quick brightness control for battery conservation.

### RGB Underglow
Enable additional RGB effects by adding to `config/sofle.conf`:
```
CONFIG_ZMK_RGB_UNDERGLOW_HUE_STEP=10
CONFIG_ZMK_RGB_UNDERGLOW_SAT_STEP=10
CONFIG_ZMK_RGB_UNDERGLOW_BRT_STEP=10
CONFIG_ZMK_RGB_UNDERGLOW_EFF_START=0
```

### Display Customization
The OLED displays show standard ZMK status information including:
- Current layer indicator (Dvorak/Lower/Raise/Adjust)
- Battery percentage
- Connection status
- Caps lock and other modifier states

## 🔋 Power Management

For optimal battery life:
- RGB underglow can be toggled with `RAISE + RGBTOG`
- Display automatically dims after inactivity
- Bluetooth deep sleep mode is enabled

## 📖 Documentation

- **[Keymap Reference](docs/keymap-reference.md)**: Complete layer documentation
- **[Adjust Layer Guide](ADJUST_LAYER_GUIDE.md)**: Conditional adjust layer usage and controls
- **[Development Guide](DEVELOPMENT.md)**: Local development setup for Arch Linux
- **[ZMK Documentation](https://zmk.dev/)**: Official ZMK firmware docs
- **[Sofle Build Guide](https://josefadamcik.github.io/SofleKeyboard/)**: Original hardware build guide

## 🛠️ Building Locally

To build firmware locally:

1. Install [Zephyr build environment](https://zmk.dev/docs/development/setup)
2. Clone this repository
3. Run the build:
   ```bash
   west build -d build/left -b nice_nano_v2 -- -DSHIELD=sofle_left
   west build -d build/right -b nice_nano_v2 -- -DSHIELD=sofle_right
   ```

## 🐛 Troubleshooting

**Display not working?**
- Ensure OLED displays are properly connected to I2C pins
- Check that `CONFIG_ZMK_DISPLAY=y` is set in sofle.conf
- Verify display cables are secure and not damaged

**RGB underglow not working?**
- Check that `CONFIG_ZMK_RGB_UNDERGLOW=y` is enabled in sofle.conf
- Ensure RGB LED strips are properly connected
- Try toggling with `RAISE + RGBTOG`

**Bluetooth issues?**
- Clear pairings with `RAISE + BTCLR`
- Try different BT profiles: `RAISE + BT1-BT5`
- Power cycle both keyboard halves
- Reset keyboard with settings reset firmware

## 🤝 Contributing

Feel free to submit issues and pull requests! Areas for improvement:
- Custom display widgets
- Additional RGB patterns and effects
- Alternative keymap layouts
- Battery optimization features

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- [ZMK Firmware](https://zmk.dev/) team for the excellent keyboard firmware
- [Sofle Keyboard](https://github.com/josefadamcik/SofleKeyboard) by Josef Adamčík
- Original keymap inspiration from [klee813's config](https://github.com/klee813/zmk-config-sofle)

---

**Happy typing with your reliable split keyboard! ⌨️**
