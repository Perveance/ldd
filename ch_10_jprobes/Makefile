### License: GPLv2 ###

obj-m +=  lab2_jprobes.o

export KROOT=/lib/modules/3.13.0-031300rc1-generic/build

allofit:  modules
modules:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules
modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install
kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(PWD) clean

clean: kernel_clean
	rm -rf   Module.symvers modules.order
