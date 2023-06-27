#include "../inc/atlete.hpp"

Atlete::Atlete(Media *f){
   film = f;
   int res = SetAllData(film->GetHipPoints(), film->GetArrayHipPointLen(), 
                        film->GetRealPixelDistance());
  
   SetLenSpeedArray(0);
};

Atlete::~Atlete()
{
   if(speed != NULL)
      free(speed);
   if(data.distanceAframe != NULL)
      free(data.distanceAframe);
}
/**
 * @brief the function that sets the data from the opecv, and calculated
 *       the runned speed for each frame, & puts that in de 'speed' array;
 * @param distanceArray array with the runned distance for each frame
 * @param len length of each array
 * @param frameRate framerate of the filmed action
 * @param realPixelDistance distance of one pixel in real life
 * @return int -1 on error, 0 on success
 */
int Atlete::SetAllData(double* hipPoints, size_t len, double realPixelDistance)
{
   if(ConvertHipPointToDistancePoints(hipPoints, len, realPixelDistance) < 0)
   {
      fprintf(stderr, "Atlete::%s; SetData failed\n", __func__);
      return -1;
   }
   if(CalculateSpeed(realPixelDistance) < 0)
   {
      fprintf(stderr, "Atlete::%s; CalcculateSpeed failed\n", __func__);
      return -1;
   }
   return 0;
}


DataAtlete* Atlete::GetData()
{
   return &data;
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
int Atlete::ConvertHipPointToDistancePoints(double* hipPoints, size_t len, double realPixelDistance)
{
   if(len <= 0)
   {
      fprintf(stderr, "Atlete::%s; len <= 0\n", __func__);
      return -1;
   }
   if( hipPoints == NULL)
   {
      fprintf(stderr, "Atlete::%s; distaNceArray == NULL\n", __func__);
      return -1;
   }
   data.len = len;
   
   if(data.distanceAframe == NULL)
      data.distanceAframe = (double*)malloc(sizeof(double) * len);
   else{
      data.distanceAframe = (double*)realloc((double*)data.distanceAframe, sizeof(double)*len);
   }

   if(data.distanceAframe == NULL)return -1;
   
   double lastValue = 0;
   for(size_t i = 0; i < data.len ; i++)
   {
      if(hipPoints[i] != -1)
      {
         if(lastValue == 0)
            lastValue = hipPoints[i];

         double pixels = ((hipPoints[i] - lastValue) < 0) ? 
                  (hipPoints[i] - lastValue) * -1 : (hipPoints[i] - lastValue);
         double distance = pixels * realPixelDistance;
         data.distanceAframe[i] = distance;
         lastValue = hipPoints[i];
      }
      else
         data.distanceAframe[i] = -1;
      std::cout << "data.distanceAFrame[" << i << "] = " << data.distanceAframe[i] << std::endl;
   }

   return 0;
}
/**
 * @brief 
 * 
 * @param frameRate 
 * @param realPixelDistance 
 * @return int length of the set speed array, or -1 on error
 */
int Atlete::CalculateSpeed(double realPixelDistance)
{
   if(realPixelDistance <= 0)
   {
      fprintf(stderr, "Atlete::%s; realPixelDistance <= 0\n", __func__);
      return -1;
   }
   double frameRate = film->GetFrameRate();
   if(frameRate == (double)0)
   {
      fprintf(stderr, "Atlete::%s; frameRate == 0\n", __func__);
      return -1;
   }
   if(speed == NULL)
      speed = (double*)malloc(sizeof(double) * data.len);
   else{
      speed = (double*)realloc(speed, sizeof(double) * data.len);
   }
   if(speed == NULL)
   {
      fprintf(stderr, "Atlete::%s; cnat malloc/realloc speed\n", __func__);
      return -1;
   }

   //s(distance) = v(speed) * t(time)
   //v  = s/t;
   double frameTime = (double)(1.00 / (double)frameRate);
   if(frameTime <= 0.00)
   {
      fprintf(stderr, "Atlete::%s; frameTime == 0\n", __func__);
      return -1;
   }
   for(size_t i = 0; i < data.len; i++)
   {
      if(data.distanceAframe[i] != -1)
         speed[i] = (data.distanceAframe[i]) / frameTime;
      else 
         speed[i] = -1;

      std::cout << "speed[" << i << "] = " << speed[i] << std::endl;
   }
   SetLenSpeedArray(data.len);
   return data.len;
}

int Atlete::PrintSpeed()
{
   if(speed == NULL){
      fprintf(stderr, "Atlete::%s; no speed, calculated first...\n", __func__);
      return -1;
   }
   for(size_t i = 0; i < data.len; i++)
   {
      std::cout << speed[i] << std::endl;
   }
   return 0;
}