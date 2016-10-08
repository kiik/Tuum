#include <iostream>
#include "STM.hpp"

namespace tuum{
  class MyController : public Controller{
  public:
      MyController(Context _ctx) {}

      int run();
      void init();
      bool isRunnable();

    private:
      Context ctx;

  };

  class MyController2 : public Controller{
  public:
      MyController2(Context _ctx) {}

      int run();
      void init();
      bool isRunnable();

    private:
      Context ctx;

  };
}
