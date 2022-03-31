PART_NAME=firmware
REQUIRE_IMAGE_METADATA=1

RAMFS_COPY_BIN='fw_printenv fw_setenv'
RAMFS_COPY_DATA='/etc/fw_env.config /var/lock/fw_printenv.lock'

platform_check_image() {
	return 0;
}

platform_do_upgrade() {
	board=$(board_name)
	case $board in
	cmiot,ax18|\
	glinet,gl-ax1800|\
	glinet,gl-axt1800|\
	huasifei,wf-hr6001|\
	zn,m2)
		nand_do_upgrade "$1"
		;;
	esac
}
