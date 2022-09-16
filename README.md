# 欢迎来到 适用于 IPQ60xx 的 Openwrt 源码仓库
基于 [lean 的 IPQ60xx 仓库](https://github.com/coolsnowwolf/openwrt-gl-ax1800)

## 注意

1. **不要用 root 用户进行编译**
2. 国内用户编译前最好准备好梯子
3. 默认登陆IP 192.168.1.1 密码 password

## 编译命令

1. 首先装好 Linux 系统， Ubuntu 20.04 LTS

2. 安装编译依赖

   ```bash
   sudo apt update -y
   sudo apt full-upgrade -y
   sudo apt install -y ack antlr3 asciidoc autoconf automake autopoint binutils bison build-essential \
   bzip2 ccache cmake cpio curl device-tree-compiler fastjar flex gawk gettext gcc-multilib g++-multilib \
   git gperf haveged help2man intltool libc6-dev-i386 libelf-dev libglib2.0-dev libgmp3-dev libltdl-dev \
   libmpc-dev libmpfr-dev libncurses5-dev libncursesw5-dev libreadline-dev libssl-dev libtool lrzsz \
   mkisofs msmtp nano ninja-build p7zip p7zip-full patch pkgconf python2.7 python3 python3-pip libpython3-dev qemu-utils \
   rsync scons squashfs-tools subversion swig texinfo uglifyjs upx-ucl unzip vim wget xmlto xxd zlib1g-dev
   ```

3. 下载源代码，更新 feeds 并选择配置

   ```bash
   git clone -b stable --single-branch https://github.com/zheshifandian/openwrt-ax1800
   cd openwrt-ax1800
   ./scripts/feeds update -a && ./scripts/feeds install -a
   make menuconfig
   ```

4. 下载 dl 库，编译固件
（-j 后面是线程数，为便于排除错误推荐用单线程）

   ```bash
   make download -j8
   make -j4 tools/compile
   make -j4 toolchain/compile
   make -j1 V=99
   ```

5. 二次编译：

   ```bash
   cd openwrt-ax1800
   git fetch -all && git reset --hard origin/stable
   ./scripts/feeds update -a && ./scripts/feeds install -a
   make defconfig
   make -j1 V=99
   ```

6. 如果需要重新配置：

   ```bash
   rm -rf .config
   make menuconfig
   make -j4 prepare
   make -j1 V=99
   ```

7. 编译完成后输出路径：bin/targets

本套代码不保证所有IPK可以编译成功。

你可以自由使用，但源码编译二次发布请注明 [lean 的  GitHub 仓库](https://github.com/coolsnowwolf/lede)
