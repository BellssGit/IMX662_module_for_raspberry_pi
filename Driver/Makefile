obj-m += imx662.o

#dtbo-y += imx662.dtbo

KDIR ?= /lib/modules/$(shell uname -r)/build

#targets += $(dtbo-y)    

#always-y := $(dtbo-y)

all:
	make -C $(KDIR) M=$(shell pwd) modules

clean:
	make -C $(KDIR)  M=$(shell pwd) clean

%.dtbo: %.dts
	dtc -@ -I dts -O dtb -o $@ $<

