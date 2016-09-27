/**
 *  @file PreviewArea.hpp
 *  Color calibration application masking area.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 14 November 2015
 */

#ifndef RTX_APPLIXATIONS_CALIBRATION_COLOR_MASKING_AREA_H
#define RTX_APPLIXATIONS_CALIBRATION_COLOR_MASKING_AREA_H

#include "Brush.hpp"

#include <gtkmm.h>
#include <gdkmm/pixbuf.h>
#include <gtkmm/drawingarea.h>


namespace tuum {

  class Application;

  class MaskingArea: public Gtk::DrawingArea {

    public:
      MaskingArea(Application*);
      virtual ~MaskingArea();

      void initialise();

      void resetDrawingModes();

      void redraw();

    protected:
      virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>&);
      virtual bool on_button_press_event(GdkEventButton*);
      virtual bool on_button_release_event(GdkEventButton*);
      virtual bool on_motion_notify_event(GdkEventMotion*);
      virtual bool on_scroll_event(GdkEventScroll*);

    private:
      Application *application;

      Glib::RefPtr<Gdk::Pixbuf> maskedImage;
      Glib::RefPtr<Gdk::Pixbuf> brushedImage;

      Brush *brush;

      bool addingMode;
      bool removalMode;

      bool applyMask();
      bool locateBrush(const unsigned int&, const unsigned int&);
      bool applyBrush();
      bool drawImage(const Cairo::RefPtr<Cairo::Context>&);

  };

}

#endif // RTX_APPLIXATIONS_CALIBRATION_COLOR_MASKING_AREA_H
