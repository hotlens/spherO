#ifndef SPHERO_VIDEOWINDOW_H
#define SPHERO_VIDEOWINDOW_H

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-register"
#include <gtkmm/window.h>
#pragma clang diagnostic pop

extern "C" {
#include <unicapgtk.h>
}

#include "debayer.h"

class VideoWindow : public Gtk::Window {
public:
  struct options {
    bool debayer;
    bool automatic_white_balance;
  };
  VideoWindow();
  VideoWindow(unicap_device_t*);
  VideoWindow(unicap_device_t*, int, int);

  virtual ~VideoWindow() {}

  bool start();
  void stop();
  void show();

  void set_debayer(bool debayer = true);
  void set_automatic_white_balance(bool automatic_white_balance = true);

protected:
  GtkWidget* unicap_display_;
  options options_;
  debayer_data_t debayer_data_;

  static gboolean convert_colors(unicap_data_buffer_t*, unicap_data_buffer_t*, void*);
  void debayer_buffer(unicap_data_buffer_t*);
};

#endif  // SPHERO_VIDEOWINDOW_H
