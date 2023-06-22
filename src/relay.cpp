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
int Relay::FindCrossoverPoint()
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
double Relay::GetDistanceOfFrameNum(double frameNum)
{
   double distance = 0;
   DataAtlete *data = incomingRunner->GetData();
   if(data->len == 0 || data->distanceAframe == NULL)
   {
      fprintf(stderr, "Relay::%s, data.len == 0 || data.distanceFram == NULL\n", __func__);
      return -1;
   }
   if(frameNum > data->len) 
   {
      return -1;
      fprintf(stderr, "Relay::%s, frameNum > data.len...\n", __func__);
   }

   for(size_t i = 0; i < frameNum; i++)
   {
      distance += data->distanceAframe[i];
   }
   return distance;
}
double Relay::ExchangeDistance()
{
   int frameNum = FindCrossoverPoint();
   if(frameNum < 0)
   {
      fprintf(stderr, "Relay:%s findCross failed: %d\n", __func__, frameNum);
      return -1;
   }
   return GetDistanceOfFrameNum(frameNum);
}


//debug
void Relay::Print()
{
   std::cout << "Relay:" <<__func__ << std::endl;
   incomingRunner->PrintSpeed();
   outgoingRunner->PrintSpeed();
}