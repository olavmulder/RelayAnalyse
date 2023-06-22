#include "../inc/atlete.hpp"
Atlete::Atlete(){
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
int Atlete::SetAllData(double* distanceArray, size_t len, 
                        unsigned int frameRate, double realPixelDistance)
{
   if(SetData(distanceArray, len) < 0)
   {
      fprintf(stderr, "Atlete::%s; SetData failed\n", __func__);
      return -1;
   }
   if(CalculateSpeed(frameRate, realPixelDistance) < 0)
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
int Atlete::SetData(double* distanceArray, size_t len)
{
   if(len <= 0)
   {
      fprintf(stderr, "Atlete::%s; len <= 0\n", __func__);
      return -1;
   }
   if( distanceArray == NULL)
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
   
   for(size_t i = 0; i < data.len ; i++)
   {
      data.distanceAframe[i] = distanceArray[i];
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
int Atlete::CalculateSpeed(unsigned int frameRate, double realPixelDistance)
{
   if(realPixelDistance <= 0)
   {
      fprintf(stderr, "Atlete::%s; realPixelDistance <= 0\n", __func__);
      return -1;
   }
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
   //s = amountPixels * distance1pixel
   double frameTime = (double)(1.00 / (double)frameRate);
   if(frameTime <= 0.00)
   {
      fprintf(stderr, "Atlete::%s; frameTime == 0\n", __func__);
      return -1;
   }
   for(size_t i = 0; i < data.len; i++)
   {
      speed[i] = (data.distanceAframe[i]*realPixelDistance) * frameTime;
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