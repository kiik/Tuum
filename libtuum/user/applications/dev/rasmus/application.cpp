#include "controller.hpp"
#include <chrono>
#include "STM.hpp"

namespace usr {

	int getCurrentTime(){
    using namespace std::chrono;

    auto epoch = high_resolution_clock::from_time_t(0);
    auto now   = high_resolution_clock::now();
    int mseconds = duration_cast<milliseconds>(now - epoch).count();
    return mseconds;
  }

	int main(int, char**){
		tuum::Context ctx;
		tuum::STM* stm = new tuum::STM();
		tuum::State *st, *st2, *st1;

		ctx.stm = stm;

		st1 = stm->createState("MyController 1");
		st = st1;
		ctx.st = st;
		st->addController(new tuum::MyController(ctx, "C1"));

		st2 = stm->createState("MyController 2");
		st2->setLastState(st);
		st->setNextState(st2);
		st = st2;
		ctx.st = st;
		st->addController(new tuum::MyController(ctx, "C2"));


		//controller.init();
		int startTime = getCurrentTime();
    bool isPrinted = false;

		stm->setup();

		while(true){
    	int currentTime = getCurrentTime();
    	int timeElapsed = currentTime - startTime;

    	if(timeElapsed % 1000 == 0 && !isPrinted){
				stm->process();
				isPrinted = true;
    	}
    	if(isPrinted && !(timeElapsed % 1000 == 0)){
      	isPrinted = false;
    	}
		}

		delete(stm);

    return 0;
  }
}
