#include "inc/atlete.hpp"
#include "inc/relay.hpp"
#include <assert.h>

//#define TEST_ATLETE


#define TEST_MEDIA

void test_atlete()
{
   double hippoints[] = {10 , -1, -1 -1 , 9.89, 9.89, -1, -1, -1, 10.50, 11.50};
   size_t len = sizeof(hippoints) / sizeof(double);
   Media m("hoi", 10);
   Atlete a(&m);
   auto res = a.CalculateSpeed(hippoints, len, 10.00);
   
   assert (res > 0);

}
void test_media()
{
   //init
   char *fileName = "outgoing.mpeg";
   Media media(fileName,10);
   assert(media.GetRunnedDistance() == 10);
   assert(strcmp(fileName, media.GetFilename()) == 0);

   //CalculateRealDistance()
   assert(media.CalculatedRealDistance() == 0);
      //must be positive
   assert(media.GetRealPixelDistance() > 0);
   double ar[] = {10,1,2,3,4,5,6,78,9};
   media.SetHipPoints(ar, (double)sizeof(ar)/(double)sizeof(double));
   assert(media.GetArrayHipPointLen() == (double)sizeof(ar) / (double)sizeof(double));
   printf("%ld\n",media.GetArrayHipPointLen() );
   double *res = media.GetHipPoints();
   assert(res != NULL);
   for(unsigned long int i = 0; i < media.GetArrayHipPointLen() ;i++)
   {
      assert(ar[i] == *(res+i) );
   }
   //GetDataFromFiled
   double *arr = NULL;
   size_t i = 0;
   arr = media.GetDataFromFile(arr, &i, "coordinates.txt");
   assert(arr != NULL);
   assert(i == 2);
   assert(arr[0] == 34);
   assert(arr[1] == 1600);
   
   media.DoAll();
   assert(media.GetAmountFrames() != 0);
   assert(media.GetFrameRate() != 0);

}

int main()
{
   #ifdef TEST_MEDIA
   test_media();
   #endif
   #ifdef TEST_ATLETE
   test_atlete();
   #endif
   
}