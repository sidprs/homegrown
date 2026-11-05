#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
/*
 *  mmap -    medium speed, high ram usage, high page fault, high risk
 *  read -    fast speed,   super low ram,  medium switches, safe
 *  sendfile- fastest   ,   super low ram, lowest switches, safe
 */

#define SIZE 4096

bool process_file_dyn(int fd)
{
  if(fd == -1){
    perror("error\n");
  }
  
  struct stat stat_buff;
  size_t chunk_size = SIZE;
  
  if(fstat(fd, &stat_buff) == 0 && stat_buff.st_blksize > 0){
    chunk_size = stat_buff.st_blksize;
  }

  char* buffer = (char*)malloc(chunk_size);
  if(!buffer){
    perror("error [alloc]\n");
    
  }
    
  ssize_t bytes_read = 0;
  if((bytes_read = read(fd, buffer, sizeof(buffer))) > 0){
    int total_written = 0;
    while(total_written < bytes_read){
      size_t n = write(STDOUT_FILENO, buffer + total_written, bytes_read - total_written);
      if(n < 0){
        perror("write\n");
        close(fd);
        return 1;
      }
      total_written += n;
    }
  } else if(bytes_read < 0){
    perror("error [read]\n");
  }
  
  close(fd);
  free(buffer);
  return true;
}




int main(int argc, char* argv[])
{
    // includes the ./exe
  if(argc < 2 ){
    write(STDERR_FILENO, "usage: cat <filename>\n", 22);
    return 1;
  }

  int fd = open(argv[1], O_RDONLY);
  printf("fd %d\n", fd);
  process_file_dyn(fd);

  return 0;
}


