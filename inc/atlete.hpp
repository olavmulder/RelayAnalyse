#ifndef ATLETE_H
#define ATLETE_H

#include <iostream>
#include <stdbool.h>
#include <math.h>
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
      Atlete();
      ~Atlete();
      //DataAtlete 
      DataAtlete data;
      DataAtlete* GetData();
      int SetData(double* distanceArray, size_t len);
      
      //speed of the atlete from each frame comes from data 
      int CalculateSpeed(unsigned int frameRate, double realPixelDistance);
      

      //function called in general process
      int SetAllData(double* distanceArray, size_t len,
                     unsigned int frameRate, double realPixelDistance);
      
      //will be called from the relay class.
      int GetSpeedArray(double *speed, size_t len);
      //debug
      int PrintSpeed();
      //private??
      inline void SetLenSpeedArray(size_t len){lenSpeedArray = len;};
      inline size_t GetLenSpeedArray(){return lenSpeedArray;};
   private:
      double *speed = NULL;
      size_t lenSpeedArray = 0;
};

#endif