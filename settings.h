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

  static int PenRadiusSq() {return 20;}
  static int FPS() {return 20;}

  static int NeuronTeachCorrectModifier() {return +20;}
  static int NeuronTeachIncorrectModifier() {return -1;}

  static bool useLinearSmoothingForPixelMatrix() {return true;}

  static const QString default_weights_dir() {return "weights";}
};


/*class RecognizerMessages {
 public:
  static const QString& IncorrectExampleHeight() {return IncorrectExampleHeight_;}
  static const QString& IncorrectExampleWidth() {return IncorrectExampleWidth_;}
  static const QString& IncorrectNeuronHeight() {return IncorrectNeuronHeight_;}
  static const QString& IncorrectNeuronWidth() {return IncorrectNeuronWidth_;}
 private:
  static const QString IncorrectExampleHeight_;
  static const QString IncorrectExampleWidth_;
  static const QString IncorrectNeuronHeight_;
  static const QString IncorrectNeuronWidth_;
};
*/

#endif // SETTINGS_H
