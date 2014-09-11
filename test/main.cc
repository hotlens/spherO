#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-register"
#include <gtkmm/main.h>
#pragma clang diagnostic pop

#include "video_window.h"

int main(int argc, char* argv[]) {
  Gtk::Main app(argc, argv);

  VideoWindow video;
  video.show();
  video.set_debayer(true);
  video.set_automatic_white_balance(true);
  video.start();
  app.run(video);
}
