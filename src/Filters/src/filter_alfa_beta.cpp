
#include "filter_alfa_beta.hpp"
#include "Timing.hpp"

using namespace stmepic::filters;

FilterAlfaBeta::FilterAlfaBeta(Ticker &_ticker): ticker(_ticker){
  alfa =0.2;
  beta = 0.1;
  ypri = 0;
  ypost = 0;
  vpri = 0;
  vpost = 0;
}


float FilterAlfaBeta::calculate(float x){
  float time = ticker.get_seconds();
  float dt = prev_time - time;
  ypri = ypost + dt*vpost;
  vpri = vpost;
  ypost = ypri + alfa*(x - ypri);
  vpost = vpri + beta*(x - ypri)/dt;
  prev_time =  time;
  return ypost;
}