include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/version.mk

PKG_NAME:=ath11k-wifi
PKG_RELEASE:=$(COMMITCOUNT)
PKG_VERSION:=ipq6018
PKG_FLAGS:=nonshared

include $(INCLUDE_DIR)/package.mk

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
endef

#
# This is intended to be used on an interim basis until device-specific
# board data for new devices is available through the upstream compilation
#
# Please send a mail with your device-specific board files upstream.
# You can find instructions and examples on the linux-wireless wiki:
# <https://wireless.wiki.kernel.org/en/users/drivers/ath10k/boardfiles>
#

ALLWIFIBOARDS:= \
	gl-ax1800 \
	gl-axt1800

ALLWIFIPACKAGES:=$(foreach BOARD,$(ALLWIFIBOARDS),ath11k-wifi-$(BOARD))

define Package/ath11k-wifi-default
  SUBMENU:=ath11k Board-Specific Overrides
  SECTION:=firmware
  CATEGORY:=Firmware
  DEPENDS:=@TARGET_ipq60xx
  TITLE:=Custom Board
endef

define Package/ath11k-wifi-qcom-ipq6018
$(call Package/ath11k-wifi-default)
    TITLE:=board-2.bin for QCOM IPQ60xx eval kits
endef

define Package/ath11k-wifi-gl-ax1800
$(call Package/ath11k-wifi-default)
    TITLE:=gl-ax1800 bdf
endef

define Package/ath11k-wifi-gl-axt1800
$(call Package/ath11k-wifi-default)
    TITLE:=gl-axt1800 bdf
endef

# Blank line required at end of above define due to foreach context

define generate-ath11k-wifi-package
  define Package/ath11k-wifi-$(1)
    $(call Package/ath11k-wifi-default)
    TITLE:=board.bin Overrides for $(2)
    CONFLICTS:=$(PREV_BOARD)
  endef

  define Package/ath11k-wifi-$(1)/description
The $(2) requires board-specific, reference ("cal") data
that is not yet present in the upstream wireless firmware distribution.

This package supplies bdwlan.bin file(s) that, in the interim,
overwrite those supplied by the ath11k-firmware-* packages.

This is package is only necessary for the $(2).

Do not install it for any other device!
  endef

  PREV_BOARD+=ath11k-wifi-$(1)
endef

define Package/ath11k-wifi-qcom-ipq6018/install
	$(INSTALL_DIR) $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/
	$(INSTALL_DATA) ./board-2.bin.ipq60xx $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/board-2.bin
	$(INSTALL_DATA) ./qdss_trace_config.bin $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/qdss_trace_config.bin
endef

define Package/ath11k-wifi-gl-ax1800/install
	$(INSTALL_DIR) $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/
	$(INSTALL_DATA) ./board-gl-ax1800.bin.ipq60xx $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/board-2.bin
	$(INSTALL_DATA) ./qdss_trace_config.bin $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/qdss_trace_config.bin
endef

define Package/ath11k-wifi-gl-axt1800/install
	$(INSTALL_DIR) $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/
	$(INSTALL_DATA) ./board-gl-axt1800.bin.ipq60xx $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/board-2.bin
	$(INSTALL_DATA) ./qdss_trace_config.bin $(1)/lib/firmware/ath11k/ipq60xx/hw1.0/qdss_trace_config.bin
endef

$(eval $(call BuildPackage,ath11k-wifi-qcom-ipq6018))
$(eval $(call generate-ath11k-wifi-package,gl-ax1800,Gl.iNET AX1800))
$(eval $(call generate-ath11k-wifi-package,gl-axt1800,Gl.iNET AXT1800))

$(foreach PACKAGE,$(ALLWIFIPACKAGES),$(eval $(call BuildPackage,$(PACKAGE))))
