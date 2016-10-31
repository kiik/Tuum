/** @file tuum_visioning.hpp
 *  Visioning interface declaration.
 *
 *  @authors Ants-Oskar Mäesalu, Meelik Kiik
 *  @version 0.2
 *  @date 4. December 2015
 */

#ifndef TUUM_VISIONING_H
#define TUUM_VISIONING_H

#include <vector>

#include <boost/thread/mutex.hpp>

#include "hal.hpp"

#include "rtxmath.hpp"
#include "Feature.hpp"
#include "strms/ImageStream.hpp"

#include "tuum_buff.hpp"
#include "tuum_ppl.hpp"

#include "tuum_entities.hpp"
#include "tuum_detect.hpp"

using namespace boost;
using namespace tuum::vision;

namespace tuum {

  //TODO: replace this function's usage with an analoguous Entity method
  static double stateProbability(Transform* t1, Transform* t2) {
    const double A = 125.0;
    double px = A*gauss_prob2(t1->getX(), 120, t2->getX());
    double py = A*gauss_prob2(t1->getY(), 120, t2->getY());
    return 2*px*py / (px+py);
  }

  typedef std::vector<Feature*> FeatureSet;
  typedef std::vector<Ball*> BallSet;
  typedef std::vector<Robot*> RobotSet;

  typedef EDS<Ball>  BallDetect;
  typedef EDS<Goal>  GoalDetect;
  typedef EDS<Robot> RobotDetect;

  const uint8_t TUUM_CAM_N = 1;

  class Visioning;

  extern Visioning* gVision;

  class Visioning
  {
  public:
    struct Context {
      BallDetect  ballDetect;
      GoalDetect  goalDetect;
      //TODO: feature detect
    };

    Visioning();

    void init();
    void run();

    bool pplIsReady();

    int nextFrame();
    int readFrame(image_t&);

    int doFramePass();

    static void setup();
    static void process();

    template<typename T>
    T* get() {
      return nullptr;
    }

  protected:
    ImageStream* m_inpStreams[TUUM_CAM_N];
    TxFormat* m_format[TUUM_CAM_N];

    size_t m_cam_N, m_lid;
    image_t m_iFrame, m_oFrame;
    mutex m_iFrameLock, m_oFrameLock;
    Texture* m_tex;

    Context m_ctx;

    PipeBase m_plSimplify; // Color space conversion & simplification
    PipeBase m_plImFormat; // Get image in display color space
  };

}

#endif // TUUM_VISIONING_H
