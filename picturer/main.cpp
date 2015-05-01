#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "RcControl.h"
#include "IpmManager.h"

using namespace zmp::zrc;

void
init_system() {
  system("ipm_serial S 0x04 0");
  usleep(250 * 1000);
  system("ipm_serial S 0x04 1");
}

int
main() {
  IpmManager ipmm;

  init_system();
  ipmm.Init();
  ipmm.LoadProgram(IMAP_ALG_STEREO_OBSTACLES_1);
  ipmm.StartImap();

  ipmm.SelectImageOutput(SOF_INPUT_L);
  ipmm.SelectResultOutput(SOR_RESULT_HIST);

  while (1) {
    ipmm.Wait();
    if (ipmm.CollectResult()) {
      StereoResultHist result;
      ipmm.GetResultStereoHist(&result);
    }

    if (ipmm.CollectImage()) {
      ulong length = ipmm.ImageLength();
      uchar *data = new uchar[length];
      uchar *p = data;
      memcpy(data, ipmm.ImageData(), length);

      int fd;
      if ((fd = open("my_picture.raw", O_WRONLY | O_CREAT)) != -1) {
        write(fd, data, length);
        close(fd);
      } else
        puts("ERROR: failed to open a file");
    }
    puts("Hello, the end of a cycle!");
  }

  return 0;
}
