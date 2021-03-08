#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

void write_to_extfile_w_Lseek();

int main(){
  int temp = 1;
  // calling each test case for lseek in extent file -:
  while(temp <= 7) {
      
      if(temp == 1)
        write_to_extfile_w_Lseek("EXTlseekfile_1", -20);
      if(temp == 2)
        write_to_extfile_w_Lseek("EXTlseekfile_2", 0);
      if(temp == 2)
        write_to_extfile_w_Lseek("EXTlseekfile_3", 1);
      if(temp == 3)
        write_to_extfile_w_Lseek("EXTlseekfile_4", 50);
      if(temp == 4)
        write_to_extfile_w_Lseek("EXTlseekfile_5", 1800);
      if(temp == 5)
        write_to_extfile_w_Lseek("EXTlseekfile_6", 2047);
      if(temp == 6)
        write_to_extfile_w_Lseek("EXTlseekfile_7", 2048);
      if(temp == 7)
        write_to_extfile_w_Lseek("EXTlseekfile_8", 2060);
    temp ++;
  }
    printf(1,"Hit 'ls' to see created Extent file\n");

  exit();

}


void 
write_to_extfile_w_Lseek(char *file, uint off_set){
  uint offset;
  //Creating extent file 
  int fd = open(file, O_CREATE|O_RDWR|O_EXTENT);
  // cheking error
  if (fd <= 0){
    printf(1, "File opening failed\n");
    exit();
  }
  // creating array to write in file 2048
  char array[2048];
  int n = 0 ;
  while(n < 2048){
    array[n] = 'V';
    n++;
  }
  //Writing in file above array elements
  n = 0; 
  while (n < 1){
    int ret;
    if ((ret = write(fd, array, 2048)) != 2048){
      printf(2, "Extent Write failed. Return code %d\n", ret);
      exit();
    }
    n++;
  }

  //new array to write into file that is off_setted
  char arr2[1024];
  n = 0;
  while(n < 1024){
    arr2[n] = 'V';
    n++;
  }
  //setting offset 
  if((offset = lseek(fd, off_set)) == -1) {
    printf(1, "Extent lseek failed, returned value: %d\n", offset);
    return;
  } else {
    printf(1, "Extent lseek succeeded, off_set is: %d\n", offset);
  }
  // writing arr2[1024] to file 
  n = 0;
  while( n < 1){
    int ret;
    if ((ret = write(fd, arr2, 1024)) != 1024){
      printf(2, "Extent Write failed. Returned value : %d\n", ret);
      exit();
    }
    n++;
  }
  //Printing Extent file size, address and length 
  struct stat ExtentInfo;
  int ret = fstat(fd, &ExtentInfo);
  if (ret != 0)
  {
    printf(2,"fstat failed, retruned value: %d",ret);
    exit();
  }

  printf(1, "Extent File size is %d bytes after writing new array\n", ExtentInfo.size);
  n = 0;

  while (ExtentInfo.Extentfle[n].lenth){
   
    printf(1,"Extent address :%d. Extent Length :%d\n", ExtentInfo.Extentfle[n].addrss, ExtentInfo.Extentfle[n].lenth);
    n++;
    if (n >= 12)
      break;
  }

}
