#ifndef CWEIGHTSREADER_H
#define CWEIGHTSREADER_H

class IWeightsReader {
 public:
  virtual ~IWeightsReader() {}
};


class CWeightsReader: IWeightsReader {
 public:
  CWeightsReader();
};

#endif // CWEIGHTSREADER_H
