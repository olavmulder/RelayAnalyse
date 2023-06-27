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
      ~Media(){};
      double* GetDataFromFile(double* output, size_t* i, const char* file);


      int GetAmountFrames(){return amountFrames;};
      void SetAmountFrames(int f){amountFrames = f;};

      int GetFrameRate(){return frameRate;};
      void SetFrameRate(int f){frameRate = f;};

      void SetArrayHipPointLen(size_t len){arrayHipPointLen = len;};
      size_t GetArrayHipPointLen(){return arrayHipPointLen;};

      void SetHipPoints(double *input, size_t len);
      double*GetHipPoints(){return arrayHipPoints;};
 
      void SetRealPixelDistance(double rpd){realPixelDistance = rpd;};
      double GetRealPixelDistance(){return realPixelDistance;};

      void SetRunnedDistance(double distance){runnedDistance = distance;};
      double GetRunnedDistance(){return runnedDistance;};
      int CalculatedRealDistance();
   private:
      int frameRate = -1;
      int amountFrames = -1;
      std::vector<cv::Mat> frames;
      double arrayHipPoints[1000]; // 60fps, 1000 / 60 = 16.6 seconds 
      size_t arrayHipPointLen = 0;
      double realPixelDistance = 0.0;
      double runnedDistance = 0;
      int GetVideo(char* fileName, std::vector<cv::Mat> *frames);
      int MakeGray(std::vector<cv::Mat> *frames);


};

#endif