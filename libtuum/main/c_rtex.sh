export MMODULE=rtex
export PLATFORM=deimos
export APP=$1

make -j4 &&
make
make
