#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

int main(){
  printf(1, "Its 100 KB file, It will take some time\n");
  //Creating extent file 
  int fd = open("Extentfile.txt", O_CREATE|O_EXTENT|O_RDWR);
  
  if (fd <= 0){
    printf(1, "File opening failed \n");
    exit();
  }

  // creating array to write in file 2048
  char array[2048];
  int temp;
  temp = 0;
  while (temp < 2048){
    array[temp] = 'I';
    temp++;
  }

// writing in Extent file 
  temp = 0;
  while(temp < 50){
      int ret = write(fd, array, 2048);

      if (ret < 2048)
      {
        printf(2,"Extent Write failed. Returned code: %d\n", ret);
        exit();
      }
    temp++;

  }
  printf(1, "Wrote  100 kilobytes successfully in Extent File \n");

  //Printing Extent file size, address and length 
  struct stat Extentinfo;
  int ret = fstat(fd, &Extentinfo);
  if (ret != 0)
  {
    printf(2,"fstat failed, returned value: %d",ret);
    exit();
  }

  printf(1, "Extent File size is : %d bytes\n", Extentinfo.size);
  temp = 0;
  
while (Extentinfo.Extentfle[temp].lenth){
   
    printf(1,"Extent address is  :%d \nExtent Length is :%d\n", Extentinfo.Extentfle[temp].addrss, Extentinfo.Extentfle[temp].lenth);
    temp++;
    if (temp >= 12)
      break;
}
  printf(1,"Hit 'ls' to see created Extent file\n");

  exit();
}
