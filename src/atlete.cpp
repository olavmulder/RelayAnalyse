#include "../inc/atlete.hpp"

Atlete::Atlete(Media *f){
   film = f;
};

Atlete::~Atlete()
{
   if(speed != NULL)
      free(speed);
}
/**
 * @brief 
 * 
 * @param frameRate 
 * @param realPixelDistance 
 * @return int length of the set speed array, or -1 on error
 */
int Atlete::CalculateSpeed(double * hipPoints, size_t len, double realPixelDistance)
{
   double *distanceArray = (double*)malloc(sizeof(double)*len);
   if(distanceArray == NULL)
   {
      fprintf(stderr, "Atlete::%s; malloc went wrong\n", __func__);
      return -1;
   }

   distanceArray = _ConvertHipPointToDistancePoints(distanceArray, hipPoints, len, realPixelDistance);
   if(distanceArray == NULL)
   {
      fprintf(stderr, "Atlete::%s; convert hip points went wrong\n", __func__);
      return -1;
   }
   
   double frameRate, frameTime;
   if( (frameRate = film->GetFrameRate())          < 0 )return -1;
   if( (frameTime = _CalculateFrameTime(frameRate)) < 0 )return -1;
   if(_InitSpeedArray(len)                          < 0 )return -1;

   //s(distance) = v(speed) * t(time)
   //v  = s/t;
   
   size_t j  = 1;
   for(size_t i = 0; i < len; i++)
   {
      if(distanceArray[i] != -1)
      {
         speed[i] = (distanceArray[i]) / (frameTime*j);
         while(j > 1)
         {
            speed[i-j-1] = speed[i];
            j--;
         }
         j = 1;
      }
      else 
      {
         speed[i] = -1;
         j++;
      }
   }
   SetLenSpeedArray(len);
   PrintSpeed();
   free(distanceArray);
   return len;
}

/**
 * @brief 
 * 
 * @param s double*[out]
 * @param len size_t [in] length of array 's'
 * @return int 0 on valid, -1 when speed is not set
 */
int Atlete::GetSpeedArray(double *s, size_t len)
{
   if(speed == NULL)
   {
      fprintf(stderr, "Atlete::%s; speed == NULL\n", __func__);
      return -1;
   }
   for(size_t i = 0; i < len; i++)
   {
      s[i] = speed[i];
   }

   return 0;
}
/**
 * @brief sets data.distanceAfram array, with data from distanceArray 
 * @param distanceArray [in]
 * @param len lenght of array
 * @return int -1 on invalid input or malloc error, 0 on valid
 */
double* Atlete::_ConvertHipPointToDistancePoints(double *distanceAframe, double* hipPoints, size_t len, double realPixelDistance)
{
   
   if(len <= 0)
   {
      fprintf(stderr, "Atlete::%s; len <= 0\n", __func__);
      return NULL;
   }
   if( hipPoints == NULL)
   {
      fprintf(stderr, "Atlete::%s; distaNceArray == NULL\n", __func__);
      return NULL;
   }
     
   double lastValue = 0;
   for(size_t i = 0; i < len ; i++)
   {
      if(hipPoints[i] != -1)
      {
         if(lastValue == 0)
            lastValue = hipPoints[i];

         double pixels = ((hipPoints[i] - lastValue) < 0) ? 
                  (hipPoints[i] - lastValue) * -1 : (hipPoints[i] - lastValue);
         double distance = pixels * realPixelDistance;
         distanceAframe[i] = distance;
         lastValue = hipPoints[i];
      }
      else
         distanceAframe[i] = -1;
      std::cout << "data.distanceAFrame[" << i << "] = " << distanceAframe[i] << std::endl;
   }

   return distanceAframe;
}
double Atlete::_CalculateFrameTime(double frameRate)
{
   double frameTime = (1.00 / frameRate);
   if(frameTime <= 0.00)
   {
      fprintf(stderr, "Atlete::%s; frameTime == 0\n", __func__);
      return -1;
   }
   return frameTime;
}
int Atlete::_InitSpeedArray(size_t len)
{
   if(speed == NULL)
      speed = (double*)malloc(sizeof(double) * len);
   else{
      speed = (double*)realloc(speed, sizeof(double) * len);
   }
   if(speed == NULL)
   {
      fprintf(stderr, "Atlete::%s; cnat malloc/realloc speed\n", __func__);
      return -1;
   }
   return 0;
}


int Atlete::PrintSpeed()
{
   if(speed == NULL){
      fprintf(stderr, "Atlete::%s; no speed, calculated first...\n", __func__);
      return -1;
   }
   for(size_t i = 0; i < GetLenSpeedArray(); i++)
   {
      std::cout << speed[i] << std::endl;
   }
   return 0;
}