#
#	Makefile for notifier chain test.
#	Build & execute within kernel 3.13.0-44-generic.
#

CURRENT_PATH := $(shell pwd)
KERNEL_VERSION := $(shell uname -r)
KERNEL_PATH := /usr/src/linux-headers-$(KERNEL_VERSION)/

obj-m := publisher.o grocery.o bookstand.o supermarket.o

all:
	make -C $(KERNEL_PATH) M=$(CURRENT_PATH) modules

clean:
	make -C $(KERNEL_PATH) M=$(CURRENT_PATH) clean
