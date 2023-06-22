#include "inc/atlete.hpp"
#include "inc/relay.hpp"
#include <assert.h>

#define TEST_ATLETE
//#define TEST_RELAY_PUBLIC
#define TEST_RELAY_PRIVATE

//to test again, place function in public, not private !!
#ifdef TEST_RELAY_PRIVATE
void test_relay_private()
{
   Atlete b;
   Atlete a;
   Relay r1(&a, &b);
   double data[2] = {900, 900}; 
   double pixelDistance = (double)30 / (double)(1920);
   a.SetData(data, 2);
   b.SetData(data, 2);
   a.CalculateSpeed(2, pixelDistance);
   b.CalculateSpeed(2, pixelDistance);
   double res = r1.ExchangeDistance() ;
   assert(res != -1);
   std::cout << "exchange distance: "<<  res << std::endl;

   std::cout << __func__ << " completed" << std::endl;

}
#elif TEST_RELAY_PUBLIC
void test_relay()
{
   Atlete b;
   Atlete a;
   Relay r1(&a, &b);
   //no data set so -1
   assert(r1.FindCrossoverPoint() == -1);
   assert(r1.GetDistanceOfFrameNum(1) == -1);
   assert(r1.ExchangeDistance() == -1);
      //data is set
      double data[2] = {900, 900}; 
      double pixelDistance = (double)30 / (double)(1920);
      a.SetData(data, 2);
      b.SetData(data, 2);
      b.SetLenSpeedArray(0);
      a.SetLenSpeedArray(0);
      //fail because no array length
      assert(r1.FindCrossoverPoint() == -1);
      a.SetLenSpeedArray(1);
      assert(r1.FindCrossoverPoint() == -1);
      b.SetLenSpeedArray(1);
      // fail becuase speed is not set
      assert(r1.FindCrossoverPoint() == -1);
      a.CalculateSpeed(2, pixelDistance);
      b.CalculateSpeed(2, pixelDistance);
      //all set so output should be 2
      assert(r1.FindCrossoverPoint() >= 0);

   
   //GetDistanceOfFrameNum
   Atlete c,d;
   Relay r2(&c, &d);
   //no data set, so return -1
   assert(r2.GetDistanceOfFrameNum(0) == -1);
   c.SetData(NULL, 0);
   //data is null
   assert(r2.GetDistanceOfFrameNum(0) == -1);
      //set data
      c.SetData(data, 2);
      d.SetData(data, 2);
      c.CalculateSpeed(2, pixelDistance);
      d.CalculateSpeed(2, pixelDistance);
   //frame num is bigger than frames in data
   assert(r2.GetDistanceOfFrameNum(3) == -1);

   assert(r2.GetDistanceOfFrameNum(2) == 1800);
   double dataLen[4] = {100, 200, 300, 400};
   c.SetData(dataLen, 4);
   assert(r2.GetDistanceOfFrameNum(2) == 300);
   r1.Print();


   std::cout << __func__ << " completed" << std::endl;
}
#endif
void test_atlete()
{
   //10 frames, 
   //30 meters / 1920 pixels
   double data[2] = {900, 900}; 
   double pixelDistance = (double)30 / (double)(1920);
   Atlete b;
   assert(b.GetLenSpeedArray()  == 0);

   //invalid input SetData
   assert(b.SetData(NULL, 1) == -1);
   assert(b.SetData(&data[0], 0) == -1);
   assert(b.SetData(&data[0], 2) == 0);

      //check data 
      assert(b.data.distanceAframe[0] == 900);
      assert(b.data.distanceAframe[1] == 900);
   //no speed calculated so return -1
   assert(b.PrintSpeed() == -1);
   
   //CalculatedSpeed()
   assert(b.CalculateSpeed(0, 1) == -1);
   assert(b.CalculateSpeed(1, 0) == -1);
   assert(b.CalculateSpeed(2, pixelDistance) == 2);
   
   //GetSpeedArray
   Atlete c;
   double res[2];
   //speed is not set;
   assert(c.GetSpeedArray(res, 2) == -1);

   //set data
   assert(c.SetData(&data[0], 2) == 0);
   int length = c.CalculateSpeed(2, pixelDistance);
   assert(length == 2);
   
   //lenght must be 2
   assert(c.GetSpeedArray(res, length) == 0);
   for(int i = 0; i < length; i++)
   {
      std::cout << res[i] << std::endl;
      assert(res[i] != 0);
   }
   assert(c.data.len == 2);
   std::cout << __func__ << " completed" << std::endl;
}

int main()
{
   #ifdef TEST_ATLETE
      test_atlete();
   #endif

   #ifdef TEST_RELAY_PUBLIC
      test_relay();
   #endif
   #ifdef TEST_RELAY_PRIVATE
      test_relay_private();
   #endif
}