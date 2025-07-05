# Sofle ZMK Firmware with Bongo Cat Display

This repository contains a complete ZMK firmware setup for the Sofle split keyboard with Nice!Nano controllers, featuring an animated bongo cat display that responds to your typing speed!

## 🐱 Features

- **Animated Bongo Cat Display**: ASCII art cat that changes based on your WPM
- **Real-time WPM Tracking**: Live words-per-minute display
- **3-Layer Keymap**: QWERTY base, symbols/functions, and navigation/system layers
- **RGB Underglow**: 35 WS2812 LEDs with customizable effects
- **Rotary Encoder Support**: Volume and page navigation
- **Bluetooth LE**: Connect up to 5 devices
- **Battery Monitoring**: Real-time battery level display

## 🚀 Quick Start

1. **Fork this repository** to your GitHub account
2. **Enable GitHub Actions** in your fork
3. **Wait for the build** to complete (about 5-10 minutes)
4. **Download the firmware** from the Actions tab
5. **Flash the firmware** to your Nice!Nano controllers

## 📁 Repository Structure

```
├── config/
│   ├── sofle.keymap          # Main keymap configuration
│   ├── sofle.conf            # Hardware configuration
│   ├── west.yml              # ZMK dependencies
│   ├── custom_status_screen.c # Bongo cat display implementation
│   └── CMakeLists.txt        # Build configuration
├── docs/
│   └── keymap-reference.md   # Complete keymap documentation
├── build.yaml               # GitHub Actions build matrix
└── README.md               # This file
```

## 🎮 Bongo Cat Animation States

The bongo cat responds to your typing speed:

- **😴 Idle (0 WPM)**: Calm sitting cat
- **🐾 Tapping (10+ WPM)**: Cat starts moving
- **⚡ Ready (30+ WPM)**: Cat prepares for intense typing  
- **🔥 Furious (50+ WPM)**: Cat goes crazy with rapid animation!

## 🔧 Customization

### Changing the Keymap
Edit `config/sofle.keymap` to modify key assignments. See [keymap-reference.md](docs/keymap-reference.md) for detailed layer documentation.

### Adjusting Display Settings
Modify the WPM thresholds and animation timing in `config/custom_status_screen.c`:

```c
// WPM thresholds
#define IDLE_WPM_THRESHOLD 0
#define TAP_WPM_THRESHOLD 10
#define PREP_WPM_THRESHOLD 30
#define FURIOUS_WPM_THRESHOLD 50
```

### RGB Underglow
Enable additional RGB effects by adding to `config/sofle.conf`:
```
CONFIG_ZMK_RGB_UNDERGLOW_HUE_STEP=10
CONFIG_ZMK_RGB_UNDERGLOW_SAT_STEP=10
CONFIG_ZMK_RGB_UNDERGLOW_BRT_STEP=10
CONFIG_ZMK_RGB_UNDERGLOW_EFF_START=0
```

## 🔋 Power Management

For optimal battery life:
- RGB underglow can be toggled with `RAISE + RGBTOG`
- Display automatically dims after inactivity
- Bluetooth deep sleep mode is enabled

## 📖 Documentation

- **[Keymap Reference](docs/keymap-reference.md)**: Complete layer documentation
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

**Bongo cat not animating?**
- Verify WPM tracking is enabled: `CONFIG_ZMK_WPM=y`
- Check that custom status screen is enabled: `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=y`

**Bluetooth issues?**
- Clear pairings with `RAISE + BTCLR`
- Try different BT profiles: `RAISE + BT1-BT5`

## 🤝 Contributing

Feel free to submit issues and pull requests! Areas for improvement:
- Additional bongo cat animation frames
- More display widgets (weather, time, etc.)
- Custom RGB patterns
- Additional keymap layouts

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- [ZMK Firmware](https://zmk.dev/) team for the excellent keyboard firmware
- [Sofle Keyboard](https://github.com/josefadamcik/SofleKeyboard) by Josef Adamčík
- Original keymap inspiration from [klee813's config](https://github.com/klee813/zmk-config-sofle)
- Bongo cat meme for providing endless entertainment while coding

---

**Happy typing with your new animated friend! 🐱⌨️**
