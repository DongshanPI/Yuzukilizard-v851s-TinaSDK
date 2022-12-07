# 编译开发

开始之前我们需要先获取 提前准备好 tina-sdk压缩包，压缩包分为国内国外两个存放位置，如下所示，大小大概11G，下载完成后，拷贝到提前配置好Host开发环境的ubuntu系统内，然后参考 下载的目录内的README.txt文档 进行解压缩。

- GoogleDriver：  https://drive.google.com/drive/folders/1_HAZRddR69hRMZAVrxFrPZXFFQiV3vE0?usp=share_link
- BaiduYun:   https://pan.baidu.com/s/115gVK-8Pt-vJi8jn2AWMYw?pwd=7n4q  提取码：7n4q 
  

解压缩命令

```bash
cat tina-v853-open.tar.gz*| tar zx
```

解压完成后，可以看到多出来一个 tina-v853-open的文件夹

```bash
book@virtual-machine:~/tina-v853-open$ ls
brandy  build  buildroot  build.sh  device  kernel  openwrt  platform  prebuilt  README.md  target  tools
```

由于默认的sdk并未支持此开发板，所以我们需要支持此开发板的配置 单独拷贝增加到tina-v853-open sdk内，首先clone此开发板补丁仓库，然后单独覆盖。

```bas
book@virtual-machine:~$ git clone  https://github.com/DongshanPI/Yzukilizard-v851s-TinaSDK
book@virtual-machine:~$ cp -rfvd  Yuzukilizard-v851s-TinaSDK/* tina-v853-open/
```

拷贝完成后，接下来就可以开始进行编译了, 先执行 source build/envsetup.sh 命令来配置tina-sdk的编译环境，然后执行 lunch 选择我们要编译的目标开发板，这里选择 1 ，选择完成后，等待配置完成，就可以执行 make 命令开始编译了。

```bash
book@virtual-machine:~/tina-v853-open$ source build/envsetup.sh

NOTE: The SDK(/home/book/tina-v853-open) was successfully loaded
load openwrt... ok
Please run lunch next for openwrt.
load buildroot,bsp...ok
Please run ./build.sh config next for buildroot,bsp.

book@virtual-machine:~/tina-v853-open$ lunch

You're building on Linux

Lunch menu... pick a combo:
     1  v851s-lizard-tina
     2  v853-vision-tina
Which would you like? [Default v853-vision]: 1
Jump to longan autoconfig

book@virtual-machine:~/tina-v853-open$ make -j32

```

编译完成后，需要再次执行 pack命令进行打包 生成对应可以烧录的镜像文件。

