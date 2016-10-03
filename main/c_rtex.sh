export MMODULE=rtex
export PLATFORM=phobos
export APP=$1

make -j4 &&
make
make
