#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

typedef int TColor;
typedef double TSignal;

class RSettings {
 public:
  static int neuronHeight() {return 30;}
  static int neuronWidth() {return 30;}

  static int cellHeight() {return 6;}
  static int cellWidth() {return 6;}

  static int penRadiusSq() {return 20;}
  static int FPS() {return 20;}

  static int neuronTeachCorrectModifier() {return +20;}
  static int neuronTeachIncorrectModifier() {return -1;}

  static bool useLinearSmoothingForPixelMatrix() {return true;}

  static const QString neuronsDir() {return "neurons";}
  static const QString databaseDir() {return "base";}
  static const QString tesingDir() {return "tests";}  
};


class RMessages {
 public:
  static const QString& incorrectExampleHeight() {return incorrectExampleHeight_;}
  static const QString& incorrectExampleWidth() {return incorrectExampleWidth_;}
  static const QString& incorrectNeuronHeight() {return incorrectNeuronHeight_;}
  static const QString& incorrectNeuronWidth() {return incorrectNeuronWidth_;}
 private:
  static const QString incorrectExampleHeight_;
  static const QString incorrectExampleWidth_;
  static const QString incorrectNeuronHeight_;
  static const QString incorrectNeuronWidth_;
};


#endif // SETTINGS_H
