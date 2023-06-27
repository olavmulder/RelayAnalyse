#include "inc/relay.hpp"
#include "inc/opencv.hpp"

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
   Media incomingFilm(file, distance);   
   Media outgoingFilm(file2, distance); 
   Atlete in(&incomingFilm), out(&outgoingFilm);
   Relay r(&in, &out);
   


   return 0;
}
