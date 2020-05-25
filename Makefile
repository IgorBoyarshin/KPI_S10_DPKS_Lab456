KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	# cp igorek4.ko igorek4.ko.unstripped
	# $(CROSS_COMPILE)strip -g igorek4.ko

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
