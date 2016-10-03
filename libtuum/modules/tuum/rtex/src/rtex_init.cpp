
#include "rtex.h"

#include "tuum_platform.hpp"
#include "application.hpp"

int main(int argc, char* argv[]) {
  if(tuum::init(argc, argv) < 0) return -1;

  return usr::main(argc, argv);
}
