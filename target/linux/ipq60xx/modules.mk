define KernelPackage/usb-phy-msm
  TITLE:=DWC3 USB QCOM PHY driver for IPQ60xx and IPQ807x
  DEPENDS:=@TARGET_ipq60xx +kmod-usb-dwc3-qcom
  KCONFIG:= \
	CONFIG_USB_QCOM_QUSB_PHY \
	CONFIG_USB_QCOM_QMP_PHY
  FILES:= \
	$(LINUX_DIR)/drivers/usb/phy/phy-msm-qusb.ko \
	$(LINUX_DIR)/drivers/usb/phy/phy-msm-ssusb-qmp.ko
  AUTOLOAD:=$(call AutoLoad,45,phy-msm-qusb phy-msm-ssusb-qmp,1)
  $(call AddDepends/usb)
endef

define KernelPackage/usb-phy-msm/description
 This driver provides support for the USB PHY drivers
 within the IPQ60xx and IPQ807x SoCs.
endef

$(eval $(call KernelPackage,usb-phy-msm))
