/**
 * @file MainWindow.hpp
 * Color calibration application main window.
 *
 * @authors Ants-Oskar Mäesalu
 * @version 0.1
 */

#ifndef RTX_APPLICATIONS_CALIBRATION_COLOR_MAIN_WINDOW_H
#define RTX_APPLICATIONS_CALIBRATION_COLOR_MAIN_WINDOW_H

#include <vector>
#include <set>
#include <string>

#include <gtkmm.h>
#include <gtkmm/window.h>

#include "Camera.hpp"

#include "ImageBeforeDrawingArea.hpp"
#include "ImageAfterDrawingArea.hpp"


namespace tuum {

  class MainWindow: public Gtk::Window {

    public:
      MainWindow(Camera*);
      virtual ~MainWindow();

      bool isPlaying() const;
      bool isMasking() const;

      std::vector<std::string> getModes() const;
      unsigned int getMode() const;

      void setPlaying(const bool& = true);
      void setMasking(const bool& = true);

      bool updateFrame();

      void sendToFilter(const std::vector<std::set<unsigned int>>&, const std::vector<std::set<unsigned int>>&);

    protected:
      Gtk::Grid grid;

      // Frames and boxes for the layout
      Gtk::Box drawingButtonsBox;
      Gtk::Box generalButtonsBox;
      Gtk::Frame imageBeforeFrame;
      Gtk::Frame imageAfterFrame;
      Gtk::Box imageBeforeOptionsBox;
      Gtk::Box imageAfterOptionsBox;

      // Drawing buttons and labels
      Gtk::Label modeChooseLabel;
      Gtk::ComboBoxText modeChooseComboBox;
      Gtk::Label brushSizeLabel;
      Gtk::Scale brushSizeScale;
      Gtk::Label deltaChooseLabel;
      Gtk::Scale deltaChooseScale;

      // Video control buttons
      Gtk::Button playButton;
      Gtk::Button stopButton;

      // General buttons
      Gtk::Button openButton;
      Gtk::Button saveButton;
      Gtk::Button exitButton;

      // Options buttons
      Gtk::CheckButton displayMaskBeforeButton;
      Gtk::CheckButton displayMaskAfterButton;

      // Image drawing areas and contexts
      ImageBeforeDrawingArea imageBeforeArea;
      ImageAfterDrawingArea imageAfterArea;

    private:
      Camera *camera;
      Frame frame;
      Frame rgbFrame;

      bool playing;
      bool masking;

      unsigned int mode;

      void setProperties();

      void construct();
      void constructGrid();

      void constructDrawingButtonsBox();
      void constructGeneralButtonsBox();
      void constructImageBeforeFrame();
      void constructImageAfterFrame();
      void constructImageBeforeOptionsBox();
      void constructImageAfterOptionsBox();

      void constructModeChooseComboBox(Gtk::Container&);
      void constructBrushSizeScale(Gtk::Container&);
      void constructDeltaChooseScale(Gtk::Container&);

      void constructPlayButton(Gtk::Container&);
      void constructStopButton(Gtk::Container&);

      void constructOpenButton(Gtk::Container&);
      void constructSaveButton(Gtk::Container&);
      void constructExitButton(Gtk::Container&);

      void saveFilterToFile(const std::string&);
      void readFilterFromFile(const std::string&);

      void on_openButton_clicked();
      void on_playButton_clicked();
      void on_stopButton_clicked();
      void on_modeChooseComboBox_changed();
      void on_saveButton_clicked();

  };

};

#endif // RTX_APPLICATIONS_CALIBRATION_COLOR_MAIN_WINDOW_H
