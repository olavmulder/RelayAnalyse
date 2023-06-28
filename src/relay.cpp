#include "../inc/relay.hpp"

/**
 * @brief Construct a new Relay:: Relay object
 * 
 * @param in incomingRunner
 * @param out outgoiningRunner
 */
Relay::Relay(Atlete *in, Atlete *out)
{
   incomingRunner = in;
   outgoingRunner = out;
}
/**
 * @brief 
 * 
 * @return int -1 invalid input values, -2 not fount 0> index in SpeedArray
 */
int Relay::_FindCrossoverPoint()
{
   size_t lenD1 = 0, lenD2 = 0;
   lenD1 = incomingRunner->GetLenSpeedArray();
   lenD2 = outgoingRunner->GetLenSpeedArray();
   if(lenD1 == 0 || lenD2 == 0 )
   {
      fprintf(stderr, "Relay::%s, lend1 or lend2 == 0, set first speed array\n", __func__);
      return -1;
   }
   double d1[lenD1];
   double d2[lenD2];
   int res = incomingRunner->GetSpeedArray(d1, lenD1);
   int res1 = incomingRunner->GetSpeedArray(d2, lenD2);
   if(res  < 0 || res1 < 0 )
   {
      fprintf(stderr, "Relay::%s, GetSpeedArray %d || %d, must be > 0 \n", __func__, res, res1);
      return -1;
   }
   size_t minlen = (lenD1 <= lenD2) ? lenD1 : lenD2;
   if(minlen == 0)
   {
      fprintf(stderr, "Relay::%s; minlen == 0, must be bigger\n", __func__);
      return -1;
   }
   for(size_t i = 0 ; i < minlen ; i++)
   {
      //incoming runner become faster
      std::cout << "speedD1[" << i << "]:" << d1[i] << std::endl;
      std::cout << "speedD2[" << i << "]:" << d2[i] << std::endl;
      std::cout << std::endl;
      if(d1[i] >= d2[i])
         return (int)i;
   }
   return -2;
}


/**
 * @brief 
 * 
 * @return int -1 on no frameCrosspoint error, claon success
 */
double Relay::_CalculatedExchangeDistance()
{
   int frameNum = _FindCrossoverPoint();
   if(frameNum < 0)
   {
      fprintf(stderr, "Relay:%s findCross failed: %d\n", __func__, frameNum);
      return -1;
   }

   
   return 0;
}
/**
 * @brief 
 * 
 * @param exchangeDistance 
 * @return double -1 on no valid exchangeDistance( == 0) 
 * else avg speed 
 */
double Relay::_GetAvgSpeedToPoint(Atlete* atlete)
{
   //v = s / t 
   double exchangeDistance = _CalculatedExchangeDistance();
   if(exchangeDistance <= 0){
      fprintf(stderr, "Relay::%s; exchangeDistnace == 0", __func__);
      return -1;
   }

   //frames per second
   double t = (double)(1.00 / (double)atlete->GetFrameRate());
   //time for all frames
   t = t * atlete->GetAmountFrames();
   //avg speed 
   double avgSpeed = exchangeDistance / t;
   return avgSpeed;

}
double CalculateRunnedDistanceForTime(Atlete *atlete, double time[0])
{
   /*//amount frames for runned time
   double amountFrames = time[0] / (1/ atlete->GetFrameRate());
   double *speed = atlete->GetSpeedArray();
   for(size_t i = 0; i < amountFrames ; i++)
   {

   }*/
   return 0;
}
int Relay::TimeToReachExchange(double *time, Atlete *incoming, Atlete *outgoing )
{
   double speedIn = _GetAvgSpeedToPoint(incoming);
   double speedOut = _GetAvgSpeedToPoint(outgoing);
   if(speedIn < 0 || speedOut < 0)
   {
      fprintf(stderr, "Relay::%s; _GetAvgSpeedToPoint < 0", __func__);
      return -1;
   }
   //is already set and checked in previous calcualtes, so dont check
   double distance = GetExchangeDistance();
   
   //t = s / v
   time[0] = distance / speedIn;
   time[1] = distance / speedOut;

   double timeDif = time[1] - time[0];
   std::cout <<" timeDif = " << time[1] << " - " << time[0] <<" = " << timeDif << std::endl;
   if(timeDif < 0) 
   {
      fprintf(stderr, "Relay::%s; timeDif is negative, so incoming runner is slower...", __func__);
      return -1;
   }  
   //take speed of first element in array
   //takeOffDistance = //extra meters to run to get in the same time to exchangepoint
   //CalculateRunnedDistanceForTime(incoming, time[0]);
   //CalculateRunnedDistanceForTime(outgoing, time[1]);

   return 0;
}




//debug
void Relay::Print()
{
   std::cout << "Relay:" <<__func__ << std::endl;
   incomingRunner->PrintSpeed();
   outgoingRunner->PrintSpeed();
}