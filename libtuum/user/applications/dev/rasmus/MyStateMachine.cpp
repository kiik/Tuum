#include "MyStateMachine.hpp"
#include "controller.hpp"

namespace tuum {

    STM* MyStateMachine::stateMachine(){
        STM* stm = new STM();
        State *st, *st2;
        Context ctx;

        st = stm->createState("State1");
        ctx.st = st;
        st->addController(new tuum::MyController(ctx, "Controller 1"));

        st2 = stm->createState("state2");
        st2->setLastState(st);
        st->setNextState(st2);
        st = st2;
        ctx.st = st;
        st->addController(new tuum::MyController(ctx, "Controller 2"));

        return stm;

    }
}
