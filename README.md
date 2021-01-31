# ModuleLoding
linux sample driver loading



$ make
make -C /lib/modules/5.4.0-62-generic/build M=/home/kishore/Documents/gitPrctise/ModuleLoding modules
make[1]: Entering directory '/usr/src/linux-headers-5.4.0-62-generic'
  CC [M]  /home/kishore/Documents/gitPrctise/ModuleLoding/helloworld.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC [M]  /home/kishore/Documents/gitPrctise/ModuleLoding/helloworld.mod.o
  LD [M]  /home/kishore/Documents/gitPrctise/ModuleLoding/helloworld.ko
make[1]: Leaving directory '/usr/src/linux-headers-5.4.0-62-generic'

kishore@ubuntu:~/Documents/gitPrctise/ModuleLoding$ ls
helloworld.c   helloworld.mod    helloworld.mod.o  Makefile       Module.symvers
helloworld.ko  helloworld.mod.c  helloworld.o      modules.order  README.md

kishore@ubuntu:~/Documents/gitPrctise/ModuleLoding$ sudo insmode helloworld.ko
sudo: insmode: command not found

kishore@ubuntu:~/Documents/gitPrctise/ModuleLoding$ sudo insmod helloworld.ko
kishore@ubuntu:~/Documents/gitPrctise/ModuleLoding$ sudo dmesg -c
[270414.851885] Hello world!
kishore@ubuntu:~/Documents/gitPrctise/ModuleLoding$ sudo rmmod helloworld
kishore@ubuntu:~/Documents/gitPrctise/ModuleLoding$ sudo dmesg -c
[270439.500157] End of the world

