#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

typedef unsigned int TColor;

class RecognizerSettings {
 public:
  static int height() {return 64;}
  static int width() {return 64;}

  static int cell_height() {return 8;}
  static int cell_width() {return 8;}

  static int PenRadius() {return 5;}
  static int FPS() {return 40;}

  static int DiagramWidth() {return 100;}
  static int DiagramHeight() {return 200;}

  static const QString default_weights_dir() {return "weights";}
};

#endif // SETTINGS_H
