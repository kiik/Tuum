/**
 *  @file Filter.hpp
 *  Color calibration application filter class.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 14 November 2015
 */

#ifndef RTX_APPLICATIONS_CALIBRATION_COLOR_FILTER_H
#define RTX_APPLICATIONS_CALIBRATION_COLOR_FILTER_H

#include <vector>
#include <set>

#include "Camera.hpp"
#include "Mask.hpp"


namespace tuum {

  typedef std::set<unsigned int> FilterValueSet;
  typedef std::vector<FilterValueSet> FilterList;

  class Filter {

    public:
      Filter(const unsigned int&);
      virtual ~Filter();

      void reset();
      void reset(const unsigned int&);

      bool has(const unsigned int&, const unsigned int&, const unsigned int&, const unsigned int&) const;

      FilterList getValues() const;
      FilterValueSet getValues(const unsigned int&) const;

      FilterList getAdditionBuffers() const;
      FilterValueSet getAdditionBuffer(const unsigned int&) const;

      FilterList getRemovalBuffers() const;
      FilterValueSet getRemovalBuffer(const unsigned int&) const;

      void addMasksToBuffers(const Frame&, const MaskList&, const MaskList&);
      void addBuffersToFilter();

      std::string getString() const;

    private:
      unsigned int numberOfModes;

      FilterList values;
      FilterList additionBuffers;
      FilterList removalBuffers;

      void initialise();

      void resetValues(const unsigned int&);
      void resetBuffers(const unsigned int&);

  };

}

#endif // RTX_APPLICATIONS_CALIBRATION_COLOR_FILTER_H
