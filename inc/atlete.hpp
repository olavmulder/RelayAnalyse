#ifndef ATLETE_H
#define ATLETE_H

#include <iostream>
#include <stdbool.h>
#include <math.h>
typedef struct _dataAtlete
{
   double *distanceAframe = NULL;
   size_t len = 0;
}DataAtlete;

class Atlete
{
   public:
      Atlete();
      ~Atlete();
      DataAtlete* GetData();

      //debug
      int PrintSpeed();
      int GetSpeedArray(double *speed, size_t len);
      DataAtlete data;
      int SetData(double* distanceArray, size_t len);
      int CalculateSpeed(unsigned int frameRate, double realPixelDistance);
      
      inline void SetLenSpeedArray(size_t len){lenArray = len;};
      inline size_t GetLenSpeedArray(){return lenArray;};
   private:
      double *speed = NULL;
      size_t lenArray;
};

#endif