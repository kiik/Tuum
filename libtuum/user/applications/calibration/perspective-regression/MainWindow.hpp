/**
 *  @file MainWindow.hpp
 *  Perspective calibration application main window.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 19 November 2015
 */

#ifndef RTX_APPLICATIONS_CALIBRATION_PERSPECTIVE_MAIN_WINDOW_H
#define RTX_APPLICATIONS_CALIBRATION_PERSPECTIVE_MAIN_WINDOW_H

#include <vector>
#include <set>
#include <string>

#include <gtkmm.h>
#include <gtkmm/window.h>

#include "Camera.hpp"

#include "ImageDrawingArea.hpp"


namespace tuum {

  class MainWindow: public Gtk::Window {

    public:
      MainWindow(Camera*);
      virtual ~MainWindow();

      bool isPlaying() const;
      bool isCalculating() const;
      bool isColored(const unsigned int&, const unsigned int&) const;
      bool isColored(const unsigned int&, const unsigned int&, const unsigned int&, const unsigned int&) const;

      void setPlaying(const bool& = true);
      void setCalculating(const bool& = true);

      bool updateFrame();

    protected:
      Gtk::Grid grid;

      // Frames and boxes for the layout
      Gtk::Box generalButtonsBox;
      Gtk::Frame imageFrame;

      // Video control buttons
      Gtk::Button playButton;
      Gtk::Button stopButton;

      // General buttons
      Gtk::ComboBoxText fileChooseComboBox;
      Gtk::Button saveButton;
      Gtk::Button exitButton;

      // TODO: Add image options

      // Image drawing areas and contexts
      ImageDrawingArea imageArea;

      // Images
      Glib::RefPtr<Gdk::Pixbuf> image;

    private:
      Camera *camera;
      Frame frame;
      Frame rgbFrame;

      std::string filter;

      bool playing;
      bool calculating;

      void setProperties();

      void construct();
      void constructGrid();

      void constructGeneralButtonsBox();
      void constructImageFrame();

      void constructPlayButton(Gtk::Container&);
      void constructStopButton(Gtk::Container&);

      void constructFileChooseComboBox(Gtk::Container&);
      void constructSaveButton(Gtk::Container&);
      void constructExitButton(Gtk::Container&);

      void readFilterFromFile(const std::string&);
      void saveConstantsToFile(const std::string&);

      void on_playButton_clicked();
      void on_stopButton_clicked();
      void on_saveButton_clicked();

  };

};

#endif // RTX_APPLICATIONS_CALIBRATION_PERSPECTIVE_MAIN_WINDOW_H
