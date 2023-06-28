#ifndef ATLETE_H
#define ATLETE_H

#include <iostream>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "opencv.hpp"


class Atlete
{
   public:
      Atlete(Media *f);
      ~Atlete();
       
      //speed of the atlete from each frame comes from data 
      int CalculateSpeed(double * hipPoints, size_t len, double realPixelDistance);
      
      //will be called from the relay class.
      int GetSpeedArray(double *speed, size_t len);
      //debug
      int PrintSpeed();
      inline void SetLenSpeedArray(size_t len){lenSpeedArray = len;};
      inline size_t GetLenSpeedArray(){return lenSpeedArray;};
      inline int GetFrameRate(){return film->GetFrameRate();};
      inline int GetAmountFrames(){return film->GetAmountFrames();};
   private:
      Media *film;
      double *speed = NULL;
      size_t lenSpeedArray = 0;

      double* _ConvertHipPointToDistancePoints(double *distanceAframe, double* hipPoints , size_t len, 
                  double realPixelDistance);
      int _InitSpeedArray(size_t len);
      double _CalculateFrameTime(double frameRate);

      
};

#endif