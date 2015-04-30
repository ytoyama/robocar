#include "RcControl.h"
#include "IpmManager.h"
#include <unistd.h>
#include <string.h>

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
    }
    printf("Hello, the end of a cycle!\n");
  }

  return 0;
}
