KDIR := /usr/src/linux-headers-4.14.0-qcomlt-arm64
ROOTFS := /lib/modules/4.14.0-qcomlt-arm64


obj-m += mydriver.o

module:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
install:
	@sudo $(MAKE) -C $(KDIR) M=$(PWD) INSTALL_MOD_PATH=$(ROOTFS) modules_install
clean:
	@$(MAKE) -C $(KDIR) M=$(PWD) clean
