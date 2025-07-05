# Build Instructions

This guide covers how to build and flash the Sofle keyboard firmware using ZMK.

## Table of Contents
- [GitHub Actions (Recommended)](#github-actions-recommended)
- [Local Build Environment](#local-build-environment)
- [Manual Building](#manual-building)
- [Flashing Firmware](#flashing-firmware)
- [Troubleshooting](#troubleshooting)

---

## GitHub Actions (Recommended)

The easiest way to build firmware is using GitHub Actions, which automatically builds firmware when you make changes.

### Setup
1. **Fork or create repository** on GitHub with your keymap files
2. **Push changes** to trigger automatic builds
3. **Download firmware** from the Actions tab

### Workflow
1. Make changes to `config/sofle.keymap` or `config/sofle.conf`
2. Commit and push to GitHub
3. Go to **Actions** tab in your repository
4. Wait for build to complete (usually 2-5 minutes)
5. Download the firmware artifacts
6. Extract and flash the `.uf2` files

### Build Artifacts
- `sofle_left-nice_nano_v2-zmk.uf2` - Left half firmware
- `sofle_right-nice_nano_v2-zmk.uf2` - Right half firmware

---

## Local Build Environment

For development and testing, you can build firmware locally.

### Prerequisites

#### Windows
```powershell
# Install Chocolatey (if not already installed)
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# Install required tools
choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
choco install ninja gperf python git dtc-msys2
```

#### macOS
```bash
# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required tools
brew install cmake ninja gperf python3 ccache qemu dtc
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install -y \
  git cmake ninja-build gperf \
  ccache dfu-util device-tree-compiler wget \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
  make gcc gcc-multilib g++-multilib libsdl2-dev
```

### West Installation
```bash
# Install Python package manager if needed
pip3 install --user -U west

# Add to PATH (Linux/macOS)
echo 'export PATH=~/.local/bin:"$PATH"' >> ~/.bashrc
source ~/.bashrc

# Windows: Add %USERPROFILE%\AppData\Roaming\Python\Python39\Scripts to PATH
```

### ZMK Setup
```bash
# Clone ZMK
git clone https://github.com/zmkfirmware/zmk.git
cd zmk

# Initialize west workspace
west init -l app/
west update

# Install dependencies
west zephyr-export
pip3 install --user -r zephyr/scripts/requirements-base.txt
```

---

## Manual Building

### Building Sofle Firmware

1. **Navigate to ZMK directory**:
```bash
cd zmk/app
```

2. **Build left half**:
```bash
west build -p -d build/left -b nice_nano_v2 -- -DSHIELD=sofle_left -DZMK_CONFIG="path/to/your/config"
```

3. **Build right half**:
```bash
west build -p -d build/right -b nice_nano_v2 -- -DSHIELD=sofle_right -DZMK_CONFIG="path/to/your/config"
```

4. **Firmware files will be generated**:
- `zmk/app/build/left/zephyr/zmk.uf2`
- `zmk/app/build/right/zephyr/zmk.uf2`

### Build Script Example

Create a build script for convenience:

**Linux/macOS (`build.sh`)**:
```bash
#!/bin/bash
CONFIG_PATH="$(pwd)/config"
ZMK_PATH="path/to/zmk"

cd "$ZMK_PATH/app"

echo "Building left half..."
west build -p -d build/left -b nice_nano_v2 -- -DSHIELD=sofle_left -DZMK_CONFIG="$CONFIG_PATH"

echo "Building right half..."
west build -p -d build/right -b nice_nano_v2 -- -DSHIELD=sofle_right -DZMK_CONFIG="$CONFIG_PATH"

echo "Copying firmware files..."
cp build/left/zephyr/zmk.uf2 "$CONFIG_PATH/../sofle_left.uf2"
cp build/right/zephyr/zmk.uf2 "$CONFIG_PATH/../sofle_right.uf2"

echo "Build complete!"
```

**Windows (`build.bat`)**:
```batch
@echo off
set CONFIG_PATH=%cd%\config
set ZMK_PATH=path\to\zmk

cd /d "%ZMK_PATH%\app"

echo Building left half...
west build -p -d build/left -b nice_nano_v2 -- -DSHIELD=sofle_left -DZMK_CONFIG="%CONFIG_PATH%"

echo Building right half...
west build -p -d build/right -b nice_nano_v2 -- -DSHIELD=sofle_right -DZMK_CONFIG="%CONFIG_PATH%"

echo Copying firmware files...
copy build\left\zephyr\zmk.uf2 "%CONFIG_PATH%\..\sofle_left.uf2"
copy build\right\zephyr\zmk.uf2 "%CONFIG_PATH%\..\sofle_right.uf2"

echo Build complete!
```

---

## Flashing Firmware

### Nice!Nano Flashing Process

1. **Enter bootloader mode**:
   - Double-tap the reset button on the Nice!Nano
   - The board will appear as a USB drive named "NICENANO"

2. **Flash firmware**:
   - Copy the appropriate `.uf2` file to the NICENANO drive
   - The board will automatically reboot with new firmware

3. **Repeat for both halves**:
   - Flash `sofle_left.uf2` to the left Nice!Nano
   - Flash `sofle_right.uf2` to the right Nice!Nano

### Flashing Order
1. **Flash left half first** (usually the master/primary side)
2. **Flash right half second**
3. **Reset both halves** if they don't connect immediately

### Connection Issues
If the halves don't connect:
1. Clear Bluetooth bonds: Hold `RAISE` + `BTCLR`
2. Reset both controllers
3. Power cycle both halves
4. Wait 30 seconds for automatic connection

---

## Troubleshooting

### Build Errors

**Missing Dependencies**:
```bash
# Update west and dependencies
west update
pip3 install --user -r zephyr/scripts/requirements-base.txt
```

**Config File Not Found**:
- Ensure the `-DZMK_CONFIG` path is correct
- Use absolute paths when possible
- Check file permissions

**Shield Not Found**:
- Verify shield name: `sofle_left` and `sofle_right`
- Check ZMK version compatibility

### Runtime Issues

**Keys Not Working**:
- Check keymap syntax
- Verify key codes are valid
- Test with simple keymap first

**Bluetooth Issues**:
- Clear bonds and re-pair
- Check for interference
- Ensure both halves are powered
- Try different Bluetooth profiles

**RGB Not Working**:
- Check `sofle.conf` RGB settings
- Verify LED strip configuration
- Check power consumption

**Encoder Issues**:
- Verify encoder is properly seated
- Check `sofle.conf` encoder settings
- Test encoder behavior in each layer

### Getting Help

1. **ZMK Documentation**: https://zmk.dev/docs
2. **ZMK Discord**: https://zmk.dev/community/discord/invite
3. **ZMK GitHub Issues**: https://github.com/zmkfirmware/zmk/issues
4. **Reddit r/ErgoMechKeyboards**: Community support

### Debug Logging

Enable logging for debugging:

In `sofle.conf`:
```conf
# Enable logging
CONFIG_ZMK_USB_LOGGING=y
CONFIG_LOG=y
CONFIG_LOG_MODE_IMMEDIATE=y
```

Build with logging and check output via USB serial connection.

---

## Quick Reference

### Common Commands
```bash
# Clean build
west build -p

# Build specific shield
west build -b nice_nano_v2 -- -DSHIELD=sofle_left

# Update ZMK
west update

# Check build configuration
west build -t menuconfig
```

### File Locations
- **Firmware**: `zmk/app/build/[left|right]/zephyr/zmk.uf2`
- **Config**: `config/sofle.keymap` and `config/sofle.conf`
- **Logs**: Check serial output when USB logging enabled

### Build Times
- **GitHub Actions**: 2-5 minutes
- **Local Build**: 30 seconds - 2 minutes (after initial setup)
- **Initial Setup**: 10-30 minutes depending on system
