HEAD := arch/head.o
LIB  := lib/lib.o
APP  := app/main.o
DIVER := diver/dev.o
KERNEL := kernel/core.o
INIT := init/init.o
COMPLIE_PATH := /opt/FriendlyARM/toolschain/4.4.3/bin
IMAGE := $(HEAD) $(APP) $(LIB) $(DIVER) $(KERNEL) $(INIT)
CC    := $(COMPLIE_PATH)/arm-linux-cc
LD    := $(COMPLIE_PATH)/arm-linux-ld
CP    := $(COMPLIE_PATH)/arm-linux-objcopy
DP    := $(COMPLIE_PATH)/arm-linux-objdump
TOP   := $(shell pwd)

MAKEC  := make -c
INCLUDE += -I$(TOP)/include/ -I$(TOP)/kernel/include/
CFLAGS += $(INCLUDE)
CFLAGS += -O1
export CC LD CP DP INCLUDE CFLAGS

all: $(IMAGE)
	$(LD)  -Tboot.lds -o image $(IMAGE) -lgcc -L/opt/FriendlyARM/toolschain/4.4.3/lib/gcc/arm-none-linux-gnueabi/4.4.3/ 
	$(CP) -O binary -S -v image image.bin
	$(DP) -D image > t1.txt
	$(DP) -d image > t2.txt
	$(DP) -h image > t3.txt
	@ls -l image*
$(HEAD):
	$(MAKE) -C arch
$(APP):
	$(MAKE) -C app
$(LIB):
	$(MAKE) -C lib
$(DIVER):
	$(MAKE) -C diver
$(KERNEL):
	$(MAKE) -C kernel
$(INIT):
	$(MAKE) -C init
	



clean:
	$(MAKE) clean -C arch/
	$(MAKE) clean -C app/
	$(MAKE) clean -C lib/
	$(MAKE) clean -C diver/
	$(MAKE) clean -C kernel/
	$(MAKE) clean -C init/
	@rm image image.bin
