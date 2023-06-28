#ifndef OPENCV_HPP
#define OPENCV_HPP

#include <vector>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class Media
{
   public:
      Media(char* filmName, double realDistance);
      ~Media(){
         if(arrayHipPoints != NULL)
            free(arrayHipPoints);
      };
      int DoAll();

      double* GetDataFromFile(double* output, size_t* i, const char* file);


      int GetAmountFrames(){return amountFrames;};
      void SetAmountFrames(int f){amountFrames = f;};

      int GetFrameRate(){
         if(frameRate == (double)0)
         {
            fprintf(stderr, "Atlete::%s; frameRate == 0\n", __func__);
            return -1;
         }
         return frameRate;
      };
      void SetFrameRate(int f){frameRate = f;};

      void SetArrayHipPointLen(size_t len){arrayHipPointLen = len;};
      size_t GetArrayHipPointLen(){return arrayHipPointLen;};

      void SetHipPoints(double *input, size_t len);
      double* GetHipPoints(){return arrayHipPoints;};

      void SetRealPixelDistance(double rpd){realPixelDistance = rpd;};
      double GetRealPixelDistance(){return realPixelDistance;};

      void SetRunnedDistance(double distance){runnedDistance = distance;};
      double GetRunnedDistance(){return runnedDistance;};
      int CalculatedRealDistance();

      char* GetFilename(){return fileName;};
   private:
      char fileName[100];
      int frameRate = -1;
      int amountFrames = -1;
      std::vector<cv::Mat> frames;
      double *arrayHipPoints = NULL; 
      size_t arrayHipPointLen = 0;
      double realPixelDistance = 0.0;
      double runnedDistance = 0;
      int GetVideo(char* fileName, std::vector<cv::Mat> *frames);
      int MakeGray(std::vector<cv::Mat> *frames);


};

#endif