#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

typedef int TColor;
typedef double TSignal;

class RecognizerSettings {
 public:
  static int NeuronHeight() {return 30;}
  static int NeuronWidth() {return 30;}

  static int CellHeight() {return 6;}
  static int CellWidth() {return 6;}

  static int PenRadius() {return 5;}
  static int FPS() {return 20;}

  static int DiagramWidth() {return 300;}
  static int DiagramHeight() {return 400;}

  static int NeuronTeachCorrectModifier() {return +5;}
  static int NeuronTeachIncorrectModifier() {return 0;}

  static const QString default_weights_dir() {return "weights";}
};

#endif // SETTINGS_H
