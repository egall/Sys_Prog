/* writetest.c 
 * Author  Bjarni R. Einarsson 
 * Website: http://bre.klaki.net/blog/2011/12/27/
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc, char **argv) {
  char *filename = argv[1];
  unsigned char c;
  int i, fd, offset;

  /* Start 16 forks */
  for (offset = 0; offset < 15; offset++) {
    if (!fork()) break;
  }
  offset *= 0x100;

  /* Write sequences of 0..255 to a 256 byte block */
  fd = open(filename, O_CREAT | O_RDWR, S_IRWXU);
  for (c = 0x00; c < 0xef; c++) {
    for (i = 0; i < 0x100; i++) {
      lseek(fd, i+offset, SEEK_SET);
      write(fd, &c, 1);
    }
  }
  close(fd);
}
