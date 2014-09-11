#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-register"
#include <glibmm.h>
#include <gtkmm/widget.h>
#pragma clang diagnostic pop

#include <cstring>  // memcpy

#include "video_window.h"

VideoWindow::VideoWindow(unicap_device_t* device)
    : unicap_display_(unicapgtk_video_display_new_by_device(device)), options_{false, false} {

  if (unicap_display_)
    add(*Glib::wrap(unicap_display_));

  int default_ccm[3][3] = {{static_cast<int>(1.3 * 1024),
                            static_cast<int>(-0.2 * 1024),
                            static_cast<int>(-0.1 * 1024)},
                           {static_cast<int>(-0.2 * 1024),
                            static_cast<int>(1.4 * 1024),
                            static_cast<int>(-0.2 * 1024)},
                           {static_cast<int>(-0.1 * 1024),
                            static_cast<int>(-0.2 * 1024),
                            static_cast<int>(1.3 * 1024)}};

  std::memcpy(&debayer_data_.ccm, &default_ccm, sizeof (default_ccm));
  debayer_data_.use_ccm = 0;
  debayer_data_.use_rbgain = 0;
  debayer_data_.rgain = 1;
  debayer_data_.bgain = 1;
}

VideoWindow::VideoWindow() : VideoWindow(NULL) {}

VideoWindow::VideoWindow(unicap_device_t* device, int width, int height)
    : VideoWindow(device) {
  set_default_size(width, height);
}

bool VideoWindow::start() {
  gboolean res = unicapgtk_video_display_start(UNICAPGTK_VIDEO_DISPLAY(unicap_display_));
  unicapgtk_video_display_set_scale_to_fit(UNICAPGTK_VIDEO_DISPLAY(unicap_display_), TRUE);
  unicapgtk_video_display_set_color_conversion_callback(
      UNICAPGTK_VIDEO_DISPLAY(unicap_display_), VideoWindow::convert_colors, this);
  return (res == TRUE);
}

void VideoWindow::stop() {
  unicapgtk_video_display_stop(UNICAPGTK_VIDEO_DISPLAY(unicap_display_));
}

void VideoWindow::show() {
  show_all();
}

void VideoWindow::set_debayer(bool debayer) {
  options_.debayer = debayer;
}

void VideoWindow::set_automatic_white_balance(bool automatic_white_balance) {
  options_.automatic_white_balance = automatic_white_balance;
}

gboolean VideoWindow::convert_colors(unicap_data_buffer_t* dest, unicap_data_buffer_t* src,
                                 void* user_data) {
  VideoWindow* instance = reinterpret_cast<VideoWindow*>(user_data);
  if (instance->options_.automatic_white_balance)
    debayer_calculate_rbgain(src, &instance->debayer_data_.rgain,
                             &instance->debayer_data_.bgain);
  if (instance->options_.debayer)
    debayer_ccm_rgb24_edge(dest, src, &instance->debayer_data_);

  return TRUE;
}
