# libtuum

## Dependencies

Consolidated dependency install:

sudo bin/install-dependencies.sh

Dependencies which might need to be compiled manually are specified in the script as well.

# libtuum architecture

## Directory guide

- 'lib' : Miscellaneous libraries

- 'hal' : The hardware abstraction layer - contains interfaces for camera, motor drivers, RF communication etc.
- 'ctrlmod' : Contains libraries for expressing logic which also link together the whole program.

- 'rtxmath' : Generic mathemathical functionality.
- 'geometry' : Generic geometry datastructure functionality.
- 'entities' : Generic entity definitions.

- 'user' : Application modules for controlling which subsystems are run. Mainly used for development purposes.
- 'system' : Contains classes for spawning a running robot instance with motion, localization and visioning processes.

- 'lpx' : External library interface proxy module. ( OpenGL, Gtk, GLIP-Lib, etc. )
- 'env' : General environment related functions module. ( time, logging, fs, dynamic resources handling, etc. )
- 'tdb' : Local Sqlite database interface.

- 'loc' : Localization functionality module
- 'vision' : Vision functionality module

- 'htgui' : Web interface module.
- 'qtgui' : Qt5 interface module. ( Currently deprecated. )

- 'tv9' : Google V9 engine bindings ( Work in progress. )

## Build system guide

The 'gyp' tool can be used for generating the compilation environment.
All of the modules' build settings are specified in their .gyp files.

# Authors

## Original Author
 * Meelik Kiik (kiik.meelik@gmail.com)

## Co-Author
 * Ants-Oskar Mäesalu (aomaesalu@gmail.com)

## Contributors
 * Todo
