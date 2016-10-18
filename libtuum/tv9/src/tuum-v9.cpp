/** @file tuum-v9.cpp
 *  Tuum scripting module 'v9'.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 4. October 2016
 */

#include <v8.h>

#include "tv9_env.hpp"
#include "tuum-v9.hpp"

using namespace v8;


/** TV9 functions
 *  1. Replace c++ process with script-program
 *  2. Run additional script-program when available
 */

#include "ModuleContext.hpp"

namespace tuum { namespace v9 {

  void scripting_test() {
    // Create a stack-allocated handle scope.

  }

  void setup() {
    test::v9_init();
    test::process();
  }

  int _ctx_hook(ModuleContext* ptr) {
    if(ptr == nullptr) return -1;
    return ptr->exec();
  }

  int _ctx_init(ModuleContext*& ptr) {
    if(ptr == nullptr) ptr = new ModuleContext();
    return 0;
  }

  namespace test {

    TV9_CTX();

    class TestClass {
    public:
      TestClass() {
        val = 1;
      }

      void testFn() {
        printf("[TestClass::testFn]%i\n", val);
      }

    private:
      int val;
    };

    int v9_init() {
      v8_init();

      TV9_CTX_INIT();
      TV9_CTX_INSERT(TestClass);
    }

    int process() {
      int res = TV9_CTX_HOOK();
      if(res >= 0) return res;

      /** Regular cpp logic **/
      printf("c++ routine.\n");

      return 0;
    }

  }

}}
