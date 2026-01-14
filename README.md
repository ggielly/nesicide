nesicide is an Integrated Development Environment (IDE) for the 8-bit Nintendo Entertainment System (NES).

This fork is a try to maintain and compile on recent computer.


## Products in Project

This project contains the following products:

* NESICIDE : the IDE itself
* A NES emulator : standalone package of the emulator used in the IDE
* [FamiTracker-qt](https://github.com/Prichman/famitracker-qt) : a fork of jsr's FamiTracker
* FamiPlayer : a music player for .ftm files

## Prerequisites

The following steps are required prior to building this project on any platform.

0. Install `git`
1. Install Qt 5.15 or later (tested with Qt 5.15.17). While Qt 5.12.6 was originally recommended, the project now builds successfully with newer Qt 5 versions.
2. Make sure qmake and your Qt installation is in your PATH.

### Debian/Ubuntu prerequisites

```sh
sudo apt update
sudo apt install -y git qt5-qmake qtbase5-dev qtbase5-dev-tools libqt5opengl5-dev \
    build-essential libasound2-dev liblua5.1-dev \
    libsdl1.2-dev libgl1-mesa-dev libjack-jackd2-dev \
    libqt5svg5-dev libqt5xmlpatterns5-dev
```

### Arch Linux prerequisites

```sh
sudo pacman -S git qt5-base qt5-tools lua sdl mesa wine jack
```

### Missing Dependencies

The project requires several dependencies that are not included in the repository:

1. **RtMidi**: MIDI library - will be automatically downloaded during build
2. **Boost**: C++ libraries - required for FamiTracker (version 1.64.0)
3. **QScintilla2**: Advanced text editor component
4. **QHexEdit2**: Hex editor component

If these are missing, the build script will attempt to download them from the original sources.

### Windows prerequisites

Install [GnuWin32](https://sourceforge.net/projects/getgnuwin32/) and [wget](http://gnuwin32.sourceforge.net/packages/wget.htm).

## Known Issues and Solutions

### Qt Version Compatibility

While the project was originally designed for Qt 5.12.6, it now builds successfully with Qt 5.15.x. If you encounter issues with newer Qt versions:

- **Solution 1**: Install Qt 5.15 LTS: `sudo apt install qt515base qt515-tools`
- **Solution 2**: Use the `greaterThan(QT_MAJOR_VERSION,5)` checks already present in the .pro files

### Missing RtMidi

If you get errors about missing RtMidi:

```sh
cd deps
git clone https://github.com/thestk/rtmidi.git rtmidi-source
cp rtmidi-source/RtMidi.h rtmidi/
```

### SDL not found

If SDL headers are not found, ensure you have `libsdl1.2-dev` installed and add the include path manually:

```sh
sudo apt install libsdl1.2-dev
```

## Building

This project builds for Linux, macOS, and Windows. To perform a build for any supported platform follow the instructions for the platform below.

`NOTE: The build process takes a while, so grab a snack while you wait. ;)`

### Linux

0. `./build/linux-build.sh`
1. `./build/linux-deploy.sh local`

### macOS

If you installed Qt from Homebrew you need to set the following environment variable so that the build process can find qmake (the qt5 Homebrew formula is keg-only):

```
PATH="/usr/local/opt/qt/bin:$PATH"
```

0. `./build/osx-build.sh`
1. `./build/osx-deploy.sh local`

### Windows

NOTE: The build process uses GnuWin32 tools and MinGW tools. Install these and make sure that `mingw32-make` and `wget` are on your path.

0. `./build/windows-build.sh`
1. `./build/windows-deploy.sh local`

## Running

The `deploy.sh` creates artifacts of the following form.

### Linux

Separate AppImage executables for each product of the project. See https://appimage.org/ for information on AppImage containers.

### macOS

Separate Apple Disk Images (DMGs) for each product of the project.

### Windows

Monolithic bzipped tarball containing all products of the project, extractable to anywhere.

Enjoy!
