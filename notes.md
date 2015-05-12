# Notes for someone tommorow having nothing in his head

This is notes for a forgetful person. It is about ZMP RoboCar, Ubuntu, Fedora,
Linux kernel, other Unix and etc.
The copyright of this file resides in public domain. You can utilize anything
in it for yourself. See UNLICENSE file in the top level directory of the source
codes.

## How to compile 32-bit programs on 64-bit machines

On Intel and AMD processors, though that needs OS support, 32-bit programs
works natively on 64-bit machines.
To compile them on your 64-bit Ubuntu, the packages of 32-bit libc and so on
are necessary.

```
$ apt-get install g++-multilib libc6-dev-i386
```

Then, you can compile 32-bit c programs as follows

```
$ gcc -m32 -o <executable file> <source file>...
```

The '-m32' option indicates that gcc generates 32-bit binaries making int,
long and pointer types to the size of 32 bits.
It also works on some architectures other than Intel and AMD processors.
For further information, see gcc(1).

## Connecting to other unix via serial console with cu command

cu command is a traditional one to connect a host computer to another computer
which has serial consoles. After you connected them with a serial cable, you
will see ttyUSB<number> file in the /dev file system on your host computer as
the following example.

```
$ ls /dev
autofs
block
...
ttyS9
ttyUSB0
uhid
...
```

Then, you can connect to it and operate the remote computer typing the
following command.

```
$ cu -s <speed> -l /dev/ttyUSB<number>
```

The <speed> can usually be 9600, but ZMP RoboCar uses the practical max speed
of RS-232C, 115200. The unit of speeds is bps.
The <number> is the logical number corresponding to each serial cable connected
to your host computer. When you are using only one, it should be 0.

## Installing i386 packages on x86_64 Ubuntu
```
$ apt-get install <package name>:i386
```
Substitue the name of package you want for the <package name>.

## Creating a symbolic link to a missing library
The linker, ld differentiates the installed library,
/usr/lib/i386-linux-gnu/libxml2.so.2 from libxml2.so .
So I created a symbolic link to it in the same directory with the following
command.
```
$ cd /usr/lib/i386-linux-gnu
$ ln -s libxml2.so.2 libxml2.so
```

## X Window System programming on Ubuntu
You need the headers for Xlib, which are Xlib.h and Xutil.h.
```
$ apt-get install xorg-dev
```
Then, they should appear in /usr/include/X11 .


## IMAPCAR initialization problem
written by raviqqe on 2015/05/12

One day, I wrote a program which takes pictures using IMAPCAR board on my
RoboCar and it worked well.

Few days after, I wrote another program with bugs which does almost the same
but a little different thing. Then, I executed it on my RoboCar and of course
it didn't work because of the bugs. After soon, I executed the previous one,
which should work well but it didn't.

I haven't understand what is the cause of the problem. But, I found out it
works when the IMAPCAR board is reseted before its execution. So, I added a
subroutine to my program which initialize the whole system using the built-in
command prepared by its manufacturer, `ipm_serial`.

```c++
void
init_system() {
  system("ipm_serial S 0x04 0");
  system("ipm_serial S 0x01 0");
  usleep(250 * 1000);
  system("ipm_serial S 0x04 1");
  system("ipm_serial S 0x01 1");
  system("ipm_serial R 0x01");
}
``` 

Refer to the RoboCar manual about the meaning of each commands. This function
is based on the one in a sample program in the manual.
