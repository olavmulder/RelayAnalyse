#include "../inc/opencv.hpp"
#include <fstream>
const char* outputFile = "output.txt";
Media::Media(char* fileName)
{
   
   int length1 = 0;
   if((length1 = GetVideo(fileName, &frames) ) < 0)
   {
      perror("%s; GetVideo\n");
      exit(0);
   }
   FILE *fp;
   char str[100];
   snprintf(str, sizeof(str), "python3 test.py -f %s", fileName);
   fp = popen(str, "r");
   if (fp == NULL) {
      printf("Failed to run script\n");
      return;
   }
   pclose(fp);
   int i = 0;
   double *output = NULL;
   output = GetDataFromFile(output, &i, outputFile);
   if(i < 0 )
   {
      return;
   }else
   {  
      std::cout << "i:" << i << " output in media: " << std::endl;
      for(int j = 0; j < i; j++)
      {
         std::cout << *(output+j) << std::endl;
      }
   }
   if(output != NULL)
      free(output);
}
/**
 * @brief 
 * 
 * @param output [out] output array with content of read file
 * @param file file name of file to read 
 * @return int -1 on failure, size of output on succes
 */
double* Media::GetDataFromFile(double *output, int *i, const char* file)
{
   
   std::ifstream inputFile(file);
   if(!inputFile)
   {  
      *i = -1;
      return NULL;
   }
   std::string line;
   while(std::getline(inputFile, line, ','))
   {
      if(line[0] != '-' && line[0] != '0')
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
         output[*(i)-1] = stod(line);
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
   for(uint64_t i = 0; i < (uint64_t)cap.get(cv::CAP_PROP_FRAME_COUNT); i++)
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

