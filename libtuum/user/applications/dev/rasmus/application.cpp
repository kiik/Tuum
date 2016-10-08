#include "controller.hpp"

namespace usr {
	int main(int, char**){
		tuum::Context ctx;
		tuum::MyController controller(ctx);
		controller.init();
		controller.run();
		/*
		while(true) {

		}
		*/
		return 0;
	}
}
