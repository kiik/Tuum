export MMODULE=tdrone
export PLATFORM=tracdrone
export APP=$1

make -j4 &&
make
make
