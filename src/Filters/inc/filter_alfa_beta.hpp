
#include "filter.hpp"
#include "Timing.hpp"

#ifndef FILTER_ALFA_BETA_HPP
#define FILTER_ALFA_BETA_HPP

namespace stmepic::filters{

class FilterAlfaBeta: public FilterBase{
private:
  float ypri;
  float ypost;
  float vpri;
  float vpost;
  float prev_time;
  Ticker &ticker;
public:
  float alfa;
  float beta;
FilterAlfaBeta(Ticker &ticker);
 float calculate(float x);
};

} // namespace FILTERS
#endif