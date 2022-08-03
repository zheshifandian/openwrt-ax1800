#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/version.mk

PKG_NAME:=nss-firmware
PKG_RELEASE:=12.0.0
PKG_FLAGS:=nonshared

PKG_LICENSE_FILES:=LICENSE.md

PKG_MAINTAINER:=Robert Marko <robimarko@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/nss-firmware-default
  SECTION:=firmware
  CATEGORY:=Firmware
  DEPENDS:=@TARGET_ipq60xx
endef

define Package/nss-firmware-ipq6018
$(Package/nss-firmware-default)
  TITLE:=NSS firmware for IPQ60xx devices
endef

define Build/Compile

endef

define Package/nss-firmware-ipq6018/install
	$(INSTALL_DIR) $(1)/lib/firmware/
	$(INSTALL_DATA) ./retail_router0.bin $(1)/lib/firmware/qca-nss0.bin
endef

$(eval $(call BuildPackage,nss-firmware-ipq6018))
