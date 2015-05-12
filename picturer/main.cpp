#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>

#include "RcControl.h"
#include "IpmManager.h"

using namespace zmp::zrc;

void
init_system() {
  system("ipm_serial S 0x04 0");
  system("ipm_serial S 0x01 0");
  usleep(250 * 1000);
  system("ipm_serial S 0x04 1");
  system("ipm_serial S 0x01 1");
  system("ipm_serial R 0x01");
}

bool
take_pic(IpmManager *ipmm, const enum STEREO_ALG_OUTPUT_IMAGE_ID image_id,
    const char *filename) {
  ipmm->SelectImageOutput(image_id);
  ipmm->SelectResultOutput(SOR_NON);

  ipmm->Wait();

  if (ipmm->CollectImage()) {
    uchar data[ipmm->ImageLength()];
    memcpy(data, ipmm->ImageData(), sizeof(data));

    int fd;
    if ((fd = open(filename, O_WRONLY | O_CREAT)) != -1) {
      write(fd, data, sizeof(data));
      close(fd);
      return true;
    } else {
      warnx("ERROR: %s: failed to open a file", __func__);
      return false;
    }
  } else {
    warnx("ERROR: %s: failed to collect a image", __func__);
    return false;
  }
}

int
main() {
  IpmManager ipmm;

  init_system();
  ipmm.Init();
  ipmm.LoadProgram(IMAP_ALG_STEREO_OBSTACLES_1);
  ipmm.StartImap();

  while (!take_pic(&ipmm, SOF_INPUT_L, "left.raw"));
  while (!take_pic(&ipmm, SOF_INPUT_R, "right.raw"));
  while (!take_pic(&ipmm, SOF_NORMALIZED_L, "n_left.raw"));
  while (!take_pic(&ipmm, SOF_NORMALIZED_R, "n_right.raw"));
  while (!take_pic(&ipmm, SOF_NORMALIZED_STEREO, "stereo.raw"));

  return 0;
}
