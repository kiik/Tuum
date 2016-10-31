# Tuum robot firmware

## Dependencies

sudo apt-get install libgtkmm-3.0-dev

sudo apt-get install qt5-default qttools5-dev-tools qtdeclarative5-dev

sudo apt-get install libglew1.5 libglew-dev freeglut3 freeglut3-dev libglm-dev

sudo apt-get install assimp-utils libassimp-dev

sudo apt-get install libwebsockets7 libwebsockets-dev

sudo apt-get install libboost-all-dev

Consolidated dependency install:
sudo bin/install-dependencies.sh


## Directory guide

#### Low level modules
- 'hal' : The hardware abstraction layer - contains interfaces for camera, motor drivers, RF communication etc.
- 'loc' : Localization functionality module.
- 'vision' : Low level image processing module.

#### Core function modules
- 'entities' : Contains definitions of objects that exist in the world.
- 'geometry' : Geometrical structures module.
- 'rtxmath' : Basic mathematical constructs module.

#### High-level logic modules
- 'system' : Contains system modules which continuously process information and control the platform hardware.
- 'user' : Contains application modules with different robot logic implementations


#### Misc
- 'build/target' : Compiled libraries output
-  'modules' : Contained directories define linking of modules within the build system.
-  'main' : Compilation execution directory.


## Build system guide

-  'tlm.mk' : Makefile for top level modules
  - 'top-level-module.mk' : Makefile for building modules
    - 'platform-id.mk' : Defines all available platforms
    - 'checks.mk' : Pre-build checks
    - 'module.mk' : Defines current module targets
    - 'macros.mk' : Recursive search, assertion, modular macro definitions
      - 'os.mk' : Define MAKE_OS for current operating system
      - 'verbose.mk' : "-v" parameter verbosity control
    - 'gcc-tools.mk'
      - 'common-tools.mk'
