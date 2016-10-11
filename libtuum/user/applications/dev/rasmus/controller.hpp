
#include <string>
#include <iostream>

#include "STM.hpp"

namespace tuum {

  class MyController : public Controller{
  public:
      MyController(Context _ctx, std::string);

      int run();
      void init();
      bool isRunnable();

    private:
      Context ctx;
      std::string m_tekst;
  };

}
