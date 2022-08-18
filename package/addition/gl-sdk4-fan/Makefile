#
#
# Copyright (C) 2019 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=gl-sdk4-fan
PKG_VERSION:=axt1800
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define KernelPackage/$(PKG_NAME)
	CATEGORY:=gl-sdk4
	SUBMENU:=Kernel modules
	DEPENDS:= +kmod-hwmon-pwmfan +libc
	TITLE:= glinet SDK4 fan module
	FILES:=$(PKG_BUILD_DIR)/driver/gl_fan_driver.ko
	AUTOLOAD:=$(call AutoLoad,81,gl_fan_driver,1)
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

KERNEL_MAKE_FLAGS?= \
	ARCH="$(LINUX_KARCH)" \
	CROSS_COMPILE="$(TARGET_CROSS)"

MAKE_OPTS:= \
	$(KERNEL_MAKE_FLAGS) \
	M="$(PKG_BUILD_DIR)/driver"

define Build/Compile
	$(call Build/Compile/Default)
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

define KernelPackage/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/gl_fan $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/etc/config/glfan $(1)/etc/config/glfan
	$(INSTALL_BIN) ./files/etc/init.d/gl_fan $(1)/etc/init.d/gl_fan

	$(INSTALL_DIR) $(1)/usr/lib/oui-httpd/rpc
	$(CP) ./files/fan.lua $(1)/usr/lib/oui-httpd/rpc/fan
endef

$(eval $(call KernelPackage,$(PKG_NAME)))
