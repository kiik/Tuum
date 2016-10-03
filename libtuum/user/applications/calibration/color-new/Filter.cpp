/**
 *  @file Filter.cpp
 *  Color calibration application filter class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 14 November 2015
 */

#include "Filter.hpp"

#include <gdkmm/pixbuf.h>


namespace tuum {

  Filter::Filter(const unsigned int &numberOfModes) {
    // Set properties
    this->numberOfModes = numberOfModes;

    // Initialise filter values and buffers
    initialise();
  }

  Filter::~Filter() {
    // Nothing to do here
  }

  void Filter::initialise() {
    FilterValueSet emptySet;
    // TODO: Use set/vector initialisation constructors if possible
    for (unsigned int mode = 0; mode < numberOfModes; ++mode) {
      values.push_back(emptySet);
      additionBuffers.push_back(emptySet);
      removalBuffers.push_back(emptySet);
    }
  }

  void Filter::reset() {
    for (unsigned int mode = 0; mode < numberOfModes; ++mode) {
      reset(mode);
    }
  }

  bool Filter::has(const unsigned int &mode, const unsigned int &x, const unsigned int &y, const unsigned int &z) const {
    unsigned int index = x << 16 + y << 8 + z;
    return ((values[mode].find(index) != values[mode].end()) && (removalBuffers[mode].find(index) == removalBuffers[mode].end())) || (additionBuffers[mode].find(index) != additionBuffers[mode].end());
  }

  void Filter::reset(const unsigned int &mode) {
    resetValues(mode);
    resetBuffers(mode);
  }

  void Filter::resetValues(const unsigned int &mode) {
    values[mode].clear();
  }

  void Filter::resetBuffers(const unsigned int &mode) {
    additionBuffers[mode].clear();
    removalBuffers[mode].clear();
  }

  FilterList Filter::getValues() const {
    return values;
  }

  FilterValueSet Filter::getValues(const unsigned int &mode) const {
    return values[mode];
  }

  FilterList Filter::getAdditionBuffers() const {
    return additionBuffers;
  }

  FilterValueSet Filter::getAdditionBuffer(const unsigned int &mode) const {
    return additionBuffers[mode];
  }

  FilterList Filter::getRemovalBuffers() const {
    return removalBuffers;
  }

  FilterValueSet Filter::getRemovalBuffer(const unsigned int &mode) const {
    return removalBuffers[mode];
  }

  // TODO: Refactor for faster live usage (for example, by only adding necessary
  // modes)
  void Filter::addMasksToBuffers(const Frame &frame,
                                 const MaskList &additionMasks,
                                 const MaskList &removalMasks) {

    guint8 *pixels = frame.data;
    // TODO: Add to frame data structure
    unsigned int channels = 3;
    // TODO: Add as a method to frame data structure
    unsigned int stride = frame.width * channels;

    // TODO: Add to GUI
    int delta = 3;

    for (unsigned int mode = 0; mode < numberOfModes; ++mode) {

      resetBuffers(mode);

      // TODO: Remove duplicate code

      for (MaskValueSet::iterator i = additionMasks[mode].begin();
           i != additionMasks[mode].end(); ++i) {

        guint8 *pixel = pixels + ((*i) % frame.width) * channels +
                        ((*i) / frame.width) * stride;

        for (int x = -delta; x <= delta; ++x) {
          for (int y = -delta; y <= delta; ++y) {
            for (int z = -delta; z <= delta; ++z) {

              // TODO: format more nicely
              if (pixel[0] + x >= 0 && pixel[0] + x < 256 &&
                  pixel[1] + y >= 0 && pixel[1] + y < 256 &&
                  pixel[2] + z >= 0 && pixel[2] + z < 256) {
                additionBuffers[mode].insert((pixel[0] + x) << 16 +
                                             (pixel[1] + y) << 8 +
                                             (pixel[2] + z));
              }

            }
          }
        }

      }

      for (MaskValueSet::iterator i = removalMasks[mode].begin();
           i != removalMasks[mode].end(); ++i) {

        guint8 *pixel = pixels + ((*i) % frame.width) * channels +
                        ((*i) / frame.width) * stride;

        for (int x = -delta; x <= delta; ++x) {
          for (int y = -delta; y <= delta; ++y) {
            for (int z = -delta; z <= delta; ++z) {

              // TODO: format more nicely
              if (pixel[0] + x >= 0 && pixel[0] + x < 256 &&
                  pixel[1] + y >= 0 && pixel[1] + y < 256 &&
                  pixel[2] + z >= 0 && pixel[2] + z < 256) {
                removalBuffers[mode].insert((pixel[0] + x) << 16 +
                                            (pixel[1] + y) << 8 +
                                            (pixel[2] + z));
              }

            }
          }
        }

      }

    }

  }

  void Filter::addBuffersToFilter() {
    for (unsigned int mode = 0; mode < numberOfModes; ++mode) {
      for (FilterValueSet::iterator i = removalBuffers[mode].begin();
           i != removalBuffers[mode].end(); ++i) {
        values[mode].erase(*i);
      }
      for (FilterValueSet::iterator i = additionBuffers[mode].begin();
           i != additionBuffers[mode].end(); ++i) {
        values[mode].insert(*i);
      }
      resetBuffers(mode);
    }
  }

  // TODO: Refactor for faster output
  std::string Filter::getString() const {
    std::string output = "";
    for (unsigned int i = 0; i < 256 * 256 * 256; ++i) {
      char colorValue = 0;
      // We currently assume 0 < numberOfModes <= 8
      for (unsigned int mode = 0; mode < numberOfModes; ++mode) {
        bool modeValue = 0;
        if (values[mode].find(i) != values[mode].end()) {
          modeValue = 1;
        }
        colorValue = (colorValue << 1) + modeValue;
      }
      output += colorValue;
    }
    return output;
  }

}
