/** @file LogicManager.hpp
 *  Logic machines loading class.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 28. November 2015
 */

#ifndef RTX_LOGIC_MANAGER_H
#define RTX_LOGIC_MANAGER_H

#include "STM.hpp"

namespace tuum {

  class LogicManager {
  public:
    static STM* loadKickoffReceiverPrepare();
    static STM* loadKickoffReceiver();

    static STM* loadKickoffPasserPrepare();
    static STM* loadKickoffPasser();

    static STM* loadOffensivePlay();
    static STM* loadDefensivePlay();
  };

}

#endif // RTX_LOGIC_MANAGER_H
