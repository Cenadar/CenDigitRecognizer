#ifndef CWEIGHTSREADER_H
#define CWEIGHTSREADER_H

class IWeightsReader {
 public:
  virtual ~IWeightsReader() = 0;
};


class CWeightsReader: I {
 public:
  CWeightsReader();
};

#endif // CWEIGHTSREADER_H
