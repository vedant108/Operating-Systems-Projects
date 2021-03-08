#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

void Write_to_regular_file();
void Write_to_regular_file_w_lseek();


int main(){
  int temp = 0;
  // calling each test case for lseek in Regular file -:

  while (temp <= 8) {
      if (temp == 0)
        Write_to_regular_file("Regular_1");
      if(temp == 1)
        Write_to_regular_file("Regular_2");
      if(temp == 2)
        Write_to_regular_file_w_lseek("Reglseekfile_1", -20);
      if(temp == 3)
        Write_to_regular_file_w_lseek("Reglseekfile_2", 1);
      if(temp == 4)
        Write_to_regular_file_w_lseek("Reglseekfile_3", 50);
      if(temp == 5)
        Write_to_regular_file_w_lseek("Reglseekfile_4", 1650);
      if(temp == 6)
        Write_to_regular_file_w_lseek("Reglseekfile_5", 2047);
      if(temp == 7)
        Write_to_regular_file_w_lseek("Reglseekfile_6", 2048);
      if(temp == 8)
        Write_to_regular_file_w_lseek("Reglseekfile_7", 2060); 
    temp ++;
  }
  printf(1,"Hit 'ls' to see created Regualar file\n");
  exit();
}

void 
Write_to_regular_file(char *file){
 //creating Regular file 
 int fd = open(file, O_CREATE|O_RDWR);

  if (fd <= 0){
    printf(1, "File opening failed \n");
    exit();
  }

  // creating array to write in file 2048
  char array[2048];
  int temp;
  temp = 0;
  while(temp < 2048){
    array[temp] = 'I';
    temp++;
  }
  //Writing in file above array elements

  temp = 0;
  while( temp < 1){
    int ret;
    if ((ret = write(fd, array, 2048)) != 2048){
      printf(2, "Regualr File, Writing failed. Return %d\n", ret);
      exit();
    }
    temp++;
  }
}

void 
Write_to_regular_file_w_lseek(char *file, uint off_set){
  uint offset;
  // creating Regular file 
  int fd = open(file, O_CREATE|O_RDWR);

  if (fd <= 0){
    printf(1, "File opening failed \n");
    exit();
  }
  
  // creating array to write in file 2048
  char array[2048];
  int temp;
  temp = 0;
  while(temp < 2048){
    array[temp] = 'I';
    temp++;
  }
  //Writing in file above array elements

  temp = 0;
  while(temp < 1){
    int ret;
    if ((ret = write(fd, array, 2048)) != 2048){
      printf(2, "Regular file Writing failed. Return %d\n", ret);
      exit();
    }
    temp++;
  }

// we are creating a array to write into the file which will be offseted.
 
  char arr2[1024];
  temp = 0;
  while( temp < 1024){
    arr2[temp] = 'v';
    temp++;
  }
// setting offset
  if((offset = lseek(fd, off_set)) == -1) {
    printf(1, "Regular file lseek failed, returned value: %d\n", offset);
    return;
  } else {
    printf(1, "Regular file lseek succeedded, off_set is: %d\n", offset);
  }

  // writing arr2[1024] to file
  temp = 0;
  while(temp < 1){
    int ret;
    if ((ret = write(fd, arr2, 1024)) != 1024){
      printf(2, "Regular file Write failed. Returned value :  %d\n", ret);
      exit();
    }
  temp++;
  }
  
}


  



