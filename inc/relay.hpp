#ifndef RELAY_H
#define RELAY_H

#include "atlete.hpp"

class Relay
{
   public:
      Relay(Atlete *a1, Atlete *a2);
      void Print();
     
      double ExchangeDistance();
   private:
      Atlete *incomingRunner;
      Atlete *outgoingRunner;

      double GetDistanceOfFrameNum(double frameNum);
      int FindCrossoverPoint();
};

#endif