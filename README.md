# bootloader加密

## 1. bootloader加密原理
在设备启动时，获取flash固定内存区域的数据，如果没有数据，则获取当前芯片UID并加密写入flash固定内存区域后重启。如果有数据，则获取flash固定内存区域的数据并解密，解密后与当前芯片UID进行比较，如果相同则跳转至主程序正常启动，如果不同则擦除flash所有扇区的数据以保护程序。

## 2. 文件介绍
main.c ：主程序，包含验证UID和加密写入flash和跳转至主程序的代码

aes.c ：aes加密算法实现，详细见(https://github.com/kokke/tiny-AES-c)此仓库

## 3. 注意点
跳转app代码之前需要关闭所有调用过的外设，在app代码中重新初始化，在跳转后需要重定向中断向量表，否则会出现跳转后无法正常运行的情况。
