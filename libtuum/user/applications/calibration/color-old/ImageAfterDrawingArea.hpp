/**
 *  @file ImageDrawingArea.hpp
 *  Color calibration application "after" image drawing area.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 21 November 2015
 */

#ifndef RTX_APPLICATIONS_CALIBRATION_COLOR_IMAGE_AFTER_DRAWING_AREA_H
#define RTX_APPLICATIONS_CALIBRATION_COLOR_IMAGE_AFTER_DRAWING_AREA_H

#include <vector>
#include <set>

#include <gtkmm.h>
#include <gdkmm/pixbuf.h>

#include "Camera.hpp"

#include "ImageDrawingArea.hpp"


namespace tuum {

  class ImageAfterDrawingArea: public ImageDrawingArea {

    public:
      ImageAfterDrawingArea(MainWindow*, Gtk::Scale*);
      virtual ~ImageAfterDrawingArea();

      void filterFromString(const std::string&);
      void calculateFilterBuffer(const std::vector<std::set<unsigned int>>&, const std::vector<std::set<unsigned int>>&);
      void addBufferToFilter();

      void updateFrame(Frame*, Frame*);

      std::string getOutput() const;

    protected:
      virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>&);
      virtual bool on_scroll_event(GdkEventScroll*);

    private:
      Glib::RefPtr<Gdk::Pixbuf> image;
      Glib::RefPtr<Gdk::Pixbuf> filteredImage;

      Frame *frame;
      Frame *rgbFrame;

      Gtk::Scale *deltaScale;

      std::vector<std::set<unsigned int>> filter;
      std::vector<std::set<unsigned int>> filterAdditionBufferList;
      std::vector<std::set<unsigned int>> filterRemovalBufferList;

      std::map<bool, std::map<bool, std::map<bool, std::map<bool, std::map<bool, std::map<bool, std::map<bool, std::map<bool, char>>>>>>>> savingMap;

      void initialiseProperties();
      void initialiseImage();
      void initialiseDeltaScale(Gtk::Scale*);
      void initialiseFilters();
      void initialiseSavingMap();

      void resetFilter();
      void resetFilterBuffers();

      bool applyFilter();
      bool drawImage(const Cairo::RefPtr<Cairo::Context>&);

  };

};

#endif // RTX_APPLICATIONS_CALIBRATION_COLOR_IMAGE_AFTER_DRAWING_AREA_H
