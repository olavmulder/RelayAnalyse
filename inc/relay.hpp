#ifndef RELAY_H
#define RELAY_H

#include "atlete.hpp"

class Relay
{
   public:
      Relay(Atlete *a1, Atlete *a2);
      void Print();
     
      int TimeToReachExchange(double *time, Atlete *incoming, Atlete *outgoing );
      
      void SetExchangeDistance(double d){exchangeDistance =d;};
      double GetExchangeDistance(){return exchangeDistance;};

   private:
      //variables needed futher in calculation
      double exchangeDistance = 0;
      Atlete *incomingRunner;
      Atlete *outgoingRunner;


      //first find crosspoint
      int _FindCrossoverPoint(); 
      //then calculated distance of that crosspoint
      //by knowing the distance of the frame number 
      double _GetDistanceOfFrameNum(double frameNum);
      double _CalculatedExchangeDistance();

      double _GetAvgSpeedToPoint(Atlete *atlete);
};

#endif