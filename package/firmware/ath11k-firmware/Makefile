include $(TOPDIR)/rules.mk

PKG_NAME:=ath11k-firmware
PKG_RELEASE:=1
PKG_FLAGS:=nonshared

PKG_MAINTAINER:=John Crispin <john@phrozen.org>

include $(INCLUDE_DIR)/package.mk

define Package/ath11k-firmware-default
  SECTION:=firmware
  CATEGORY:=Firmware
  URL:=$(PKG_SOURCE_URL)
  DEPENDS:=
endef

define Package/ath11k-firmware-ipq6018
$(Package/ath11k-firmware-default)
  TITLE:=ath11k firmware for IPQ60xx devices
  DEPENDS:=@TARGET_ipq60xx
endef

define Package/ath11k-firmware-ipq6018/description
Standard ath11k firmware for IPQ60xx from QCA
endef

define Build/Compile

endef

define Package/ath11k-firmware-ipq6018/install
	$(INSTALL_DIR) $(1)/lib/firmware/IPQ6018
	$(INSTALL_DATA) ./files/IPQ6018/* \
		$(1)/lib/firmware/IPQ6018/
endef

$(eval $(call BuildPackage,ath11k-firmware-ipq6018))
