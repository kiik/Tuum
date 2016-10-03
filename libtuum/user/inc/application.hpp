/** @file application.hpp
 *  Consolidated application systems header.
 *
 *  @authors Meelik Kiik
 *  @version 0.1
 *  @date 2. November 2015
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "tuum_platform.hpp"

#include "hal.hpp"

#include "tuum_visioning.hpp"
#include "tuum_navigation.hpp"
#include "tuum_localization.hpp"
#include "tuum_motion.hpp"

namespace usr {

  int main(int, char*[]);

}

#endif // APPLICATION_H
