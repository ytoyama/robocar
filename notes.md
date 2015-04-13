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
of RS-232C, 115200. The <number> is the logical number corresponding to each
serial cable connected to your host computer. When you are using only one, it
should be 0.
