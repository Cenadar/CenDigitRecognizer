#include "cdigitneuron.h"
#include "settings.h"

CDigitNeuron::CDigitNeuron() {
}


TSignal CDigitNeuron::get_output(IPixelMatrix *input) {
  TSignal output = 0;

  int height = RecognizerSettings::height();
  int width = RecognizerSettings::width();
  for(int x = 0; x < height; ++x)
    for(int y = 0; y < width; ++y)
      output += w[x][y] * input->get_pixel(x, y);

  return output;
}
