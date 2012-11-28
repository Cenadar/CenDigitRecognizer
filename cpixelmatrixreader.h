#ifndef CPIXELMATRIXREADER_H
#define CPIXELMATRIXREADER_H

#include "cpixelmatrix.h"
#include "cxmlparser.h"

class IPixelMatrixReader {
 public:
  virtual ~IPixelMatrixReader() {}

  virtual IPixelMatrix* read() = 0;
};


class CPixelMatrixReader: public IPixelMatrixReader {
 public:
  CPixelMatrixReader(IXMLParser* parser_): parser(parser_) {}
  ~CPixelMatrixReader() {delete parser;}

  IPixelMatrix* read();
 private:  
  IXMLParser* parser;
};

#endif // CPIXELMATRIXREADER_H
