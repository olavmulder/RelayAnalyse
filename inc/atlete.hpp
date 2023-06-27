#ifndef ATLETE_H
#define ATLETE_H

#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "opencv.hpp"

//struct which must be filled from the opencv side
typedef struct _dataAtlete
{
   //dynamic array, with the distance runned for each frame seperatly
   double *distanceAframe = NULL;
   //len of distanceAframe array
   size_t len = 0;
}DataAtlete;

class Atlete
{
   public:
      Atlete(Media *f);
      ~Atlete();
      
      //DataAtlete 
      DataAtlete data;
      DataAtlete* GetData();
      int ConvertHipPointToDistancePoints(double* hipPoints , size_t len, 
                  double realPixelDistance);
      
      //speed of the atlete from each frame comes from data 
      int CalculateSpeed(double realPixelDistance);
      

      //function called in general process
      int SetAllData(double* distanceArray, size_t len,
                     double realPixelDistance);
      
      //will be called from the relay class.
      int GetSpeedArray(double *speed, size_t len);
      //debug
      int PrintSpeed();
      //private??
      int GetFrameRate(){return film->GetFrameRate();};
      int GetAmountFrames(){return film->GetAmountFrames();};

      inline void SetLenSpeedArray(size_t len){lenSpeedArray = len;};
      inline size_t GetLenSpeedArray(){return lenSpeedArray;};
   private:
      Media *film;
      double *speed = NULL;
      size_t lenSpeedArray = 0;
};

#endif