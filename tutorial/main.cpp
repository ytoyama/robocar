#include "RcControl.h"
#include <unistd.h>

using namespace zmp::zrc;

void init_system()
{
  system("ipm_serial S 0x04 0");
  usleep(250 * 1000);
  system("ipm_serial S 0x04 1");
}

int main()
{
  init_system();
  RcControl rc;
  rc.init();
  rc.SetServoEnable(1);
  rc.SetSteerAngle(30);
  usleep(250 * 1000);
  rc.SetServoEnable(0);
}
