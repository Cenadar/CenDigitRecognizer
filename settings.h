#ifndef SETTINGS_H
#define SETTINGS_H

class RecognizerSettings {
 public:
  static int height() {return height_;}
  static int width() {return width_;}
 private:
  static const int height_ = 20;
  static const int width_ = 20;
};

#endif // SETTINGS_H
