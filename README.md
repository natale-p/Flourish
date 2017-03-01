# Flourish Plugin

Integration of the Flourish plugin in Aimsun.

## Compiling

We recommend using shadow builds, that is, have the compiled objects separated from source files. We also recommend to have Aimsun copied in a user folder and write the compiled plugins directly on it.

After installing Aimsun 8.2 in its default location, setup a working folder structure as:

```
mkdir -p ~/software/sources/
mkdir -p ~/software/build/Aimsun_8_2_debug/bin
```

Copy Aimsun 8.2 files into *~/software/build/Aimsun_8_2_debug/bin*.

Aimsun executable will be find in:

- Windows: *~/software/build/Aimsun_8_2_debug/bin/Aimsun.exe*
- Linux: *~/software/build/Aimsun_8_2_debug/bin/Aimsun*
- macOS: *~/software/build/Aimsun_8_2_debug/bin/Aimsun.app*

Place your project in:

*~/software/sources/Flourish*

The top folder contains required configuration files. The plugin code will be in:

*~/software/sources/Flourish/plugins/Flourish*

Edit the file build_path.pri to set the location of the build path and the Aimsun SDK if you are placing the binaries and the sources elsewhere. The default values are:

```
BLD_PATH = $$(HOMEDRIVE)$$(HOMEPATH)/software/build/8_2_QT5_6_vc2013_x86_64_NotTrident
AIMSUN_SDK_DIR = $$(HOMEDRIVE)$$(HOMEPATH)/software/sources/Flourish
```

Then create the Makefile manually as:

```
mkdir -p ~/software/build/Aimsun_8_2_debug/plugins
cd ~/software/build/Aimsun_8_2_debug/plugins
mkdir Flourish
cd Flourish
qmake -spec win32-msvc2013 CONFIG+=debug CONFIG-=debug_and_release CONFIG+=x86_64 CONFIG+=qml_debug -o Makefile ~/software/sources/Flourish/plugins/FlourishV2XFramework/FlourishV2XFramework.pro
```

Change -spec with the correct one for your OS. Examples:

- linux-g++
- macx-clang
- win32-msvc2013

Or use Qt Creator activating the **shadow build** option. 

Following this structure the compiler will place all the object files in the folder:

*~/software/build/Aimsun_8_2_debug/plugins/Flourish*

And the plugin in the Aimsun plug-ins folder:

- Windows: *~/software/build/Aimsun_8_2_debug/bin/plugins/*
- Linux: *~/software/build/Aimsun_8_2_debug/bin/plugins/*
- macOS: *~/software/build/Aimsun_8_2_debug/bin/Aimsun.app/Contents/PlugIns/*

## Registering the Plug-in

Copy the signed XML file (*01_FlourishV2XFramework.xml*) into the Aimsun plug-ins folder. This file is located in:

*~/software/sources/Flourish/plugins/FlourishV2XFramework*

