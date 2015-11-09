#Makefile
ccflags-y := -Wall -O2 -std=gnu99 -Wno-unused-variable -Wno-declaration-after-statement -mno-sse

obj-m += MathDriver.o
MathDriver-objs := ./src/MathDriver.o
LIBS = libm.a

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
