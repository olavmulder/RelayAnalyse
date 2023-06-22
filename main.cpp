#include <iostream>
#include <errno.h>
#include <string.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

//g++ -o main src/main.cpp `pkg-config --cflags --libs opencv4`
std::string int2str(unsigned long long &i);
int GetVideo(char* fileName, std::vector<cv::Mat> *frames);
int MakeGray(std::vector<cv::Mat> *frames);

int main(int argc, char **argv)
{
   //handle input
   if(argc != 4)
   {
      perror("no arguments, 1: filename, 2: \
      filename 3: distnace in m between points\n"); 
      exit(0);
   }
   char *file = argv[1];
   char *file2 = argv[2];
   double distance = std::stod(argv[3]);
  
   
   return 0;

}
int MakeGray(std::vector<cv::Mat> *frames)
{
   /*cv::Mat img_gray;  
   for(auto i = begin(*(frames)); i != end(*frames); ++i)
   {

      //cv::cvtColor(i., img_gray, cv::COLOR_BGR2GRAY);
      i = img_gray;
      cv::imshow("action",i);
      if (cv::waitKey(0) == 27) //esc key
      {
         std::cout << "esc key is pressed by user" << std::endl;
         return -1;
      }
   }*/
   return 0;
}
/**
 * @brief Get the Video o
 * 
 * @param fileName 
 * @return int frames
 */
int GetVideo(char* fileName, std::vector<cv::Mat> *frames)
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

   return i;
}

