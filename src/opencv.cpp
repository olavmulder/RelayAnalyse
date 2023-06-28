#include "../inc/opencv.hpp"
#include <fstream>
const char* outputFile = "output.txt";
Media::Media(char* fn, double realDistance)
{
   snprintf(fileName, sizeof(fileName), "%s",fn);
   SetRunnedDistance(realDistance);
}

int Media::DoAll()
{
   int length1 = 0;
   if((length1 = GetVideo(fileName, &frames) ) < 0)
   {
      perror("%s; GetVideo\n");
      return -1;
   }
   FILE *fp;
   char str[250];
   snprintf(str, sizeof(str), "python3 videoHandling.py -f %s", fileName);
   fp = popen(str, "r");
   if (fp == NULL) 
   {
      printf("Failed to run script\n");
      return -1;
   }
   pclose(fp);
   size_t i = 0;
   double *output = NULL;
   output = GetDataFromFile(output, &i, outputFile);
   if(output == NULL)
   {
      return -1;
   }
   //do something with output
   if(CalculatedRealDistance() < 0)
   {
      return -1;
   }

   if(output != NULL)
   {
      SetHipPoints(output, i);
      free(output);
   }
   return 0;
}
//get points of pion
//calculated realpixel distance between poin by knonw distance & pixel amount
int Media::CalculatedRealDistance()
{
   double output[2];
   size_t i = 0;
   const char *fileName = "coordinates.txt";
   
   std::ifstream inputFile(fileName);
   if(!inputFile)
   {  
      return -1;
   }
   std::string line;
   while(std::getline(inputFile, line, ','))
   {
      output[i] = stod(line);
      i++;
   }
   /*test*/
   i  = 2;
   output[0]  = 34;
   output[1]  = 1600;
   /*end test*/
   if(i != 2)
   {
      std::cout << __func__ << "i != 2" << std::endl;
      return -1;
   }
   double pixelDistance = output[0] - output[1];
   pixelDistance = (pixelDistance < 0) ? pixelDistance * -1 : pixelDistance;
   std::cout << "pixelDistance: " << pixelDistance << std::endl;
   pixelDistance = GetRunnedDistance() / pixelDistance;
   std::cout << "pixelDistance: " << pixelDistance << std::endl;
   SetRealPixelDistance(pixelDistance);
   return 0;
}
/**
 * @brief set array with the hip points gatherd from the python script
 * 
 * @param input 
 * @param len 
 */
void Media::SetHipPoints(double *hipArray, size_t len)
{
   double *arrayHipPoints = (double*)malloc(sizeof(double) * len);
   for(size_t i = 0 ; i < len; i++)
   {
      if(*(hipArray+i) < 1)
         arrayHipPoints[i] = -1;
      else 
         arrayHipPoints[i] = *(hipArray+i);
   }
   SetArrayHipPointLen(len);
}
/**
 * @brief 
 * 
 * @param output [out] output array with content of read file
 * @param file file name of file to read 
 * @return int -1 on failure, size of output on succes
 */
double* Media::GetDataFromFile(double *output, size_t *i, const char* file)
{
   
   std::ifstream inputFile(file);
   if(!inputFile)
   {  
      return NULL;
   }
   std::string line = "0";
   while(std::getline(inputFile, line, ','))
   {
      if(line[0] == ' ')
      {
         printf("\nfout\n");
      }
      else
      {
         if( *i == 0)
         {
            output = (double*)malloc(sizeof(double) * 1);
            *i = 1;
         }
         else
         {
            *i = *i + 1;
            output = (double*)realloc(output, sizeof(double)  * *i);
         }
         double value = stod(line);
         if(value < 1)
            value = -1;
         output[*(i)-1] = value;
      }
   }
   return output;
}
/**
 * @brief Get the Video, set frameRate & amountFrames;
 * 
 * @param fileName 
 * @return int amount of frames frames
 */
int Media::GetVideo(char* fileName, std::vector<cv::Mat> *frames)
{
   cv::VideoCapture cap(fileName);
   if(!cap.isOpened()){
      std::cout << "Error opening video stream or file" << std::endl;
      return -1;
   }
   unsigned long long i = 0;
   for(i = 0; i < (uint64_t)cap.get(cv::CAP_PROP_FRAME_COUNT); i++)
   {
      cv::Mat frame;
      cap >> frame;
      frames->push_back(frame.clone());

      /*cv::imshow("action",frame);
      if (cv::waitKey(0) == 27) //esc key
      {
         std::cout << "esc key is pressed by user" << std::endl;
         break;
      }*/
   }
   SetAmountFrames(i);
   SetFrameRate(cap.get(cv::CAP_PROP_FPS));

   return i;
}

