/**
 *  @file ImageArea.hpp
 *  Vision testing application GUI preview area.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 21 November 2015
 */

#ifndef RTX_APPLIXATIONS_VISION_TEST_IMAGE_AREA_H
#define RTX_APPLIXATIONS_VISION_TEST_IMAGE_AREA_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>

#include "Color.hpp"
#include "Blob.hpp"


namespace tuum {

  class GUI;

  class ImageArea: public Gtk::DrawingArea {

    public:
      ImageArea(GUI*);
      virtual ~ImageArea();

      void initialise();

    protected:
      virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>&);

    private:
      GUI *gui;

      Glib::RefPtr<Gdk::Pixbuf> filteredImage;

      void colorBlob(const Blob*, guint8*, const unsigned int&, const unsigned int&);

      bool applyFilter();
      bool drawImage(const Cairo::RefPtr<Cairo::Context>&);

  };

}

#endif // RTX_APPLIXATIONS_VISION_TEST_IMAGE_AREA_H
