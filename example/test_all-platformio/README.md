### 本 example 包含所有测试

littlefs_data 目录 位于 本库的根目录下(example 内不存放副本),  存放的是 LittleFS 的数据
ffat_data 目录 位于 本库的根目录下(example 内不存放副本),  存放的是 FatFS(FFat) 的数据

## 使用方法：

### **1.将 本example 复制到一个文件夹中**
### **  将 zh_pinyin_decoder-arduino库 复制到 ./lib 中**
### **  将 本库根目录下的ffat_data中的所有文件(或littlefs_data) 复制到 ./data 中**

### 2.在 platformio.ini中 配置 你的开发板

### \[可选\] 3.在 user_config.h 中修改 Flash内用于存储 拼音码表和词库(json)文件 的文件系统:  \[推荐\] FatFS(FFat) 或 LittleFS：

```cpp
// 选择文件系统 (不要同时选择)
#define USE_FAT_FS               1  // [推荐] 使用 FatFS(FFat) 文件系统
#define USE_LITTLE_FS            0  // 使用LittleFS 文件系统
```

### \[可选\] 4.在 user_config.h 中修改 是否使用日志 及 日志输出方式

### 5.烧录文件系统：

> 注: 本 example 的根目录下提供了 推荐的 ESP32 分区表 (zh_pinyin_ffat_partition.csv) 与 推荐的 ESP32-S3 配置

#### (1) 使用 默认拼音码表与词库 或 自定义
** \[推荐\] 如果使用 默认拼音码表与词库， 就无需制作文件系统，直接跳至 (2) 即可 **

自定义拼音码表与词库，PlatformIO 中为以下步骤 (Arduino可参考 [ESP32 Arduino FAT文件系统详细使用教程](https://blog.csdn.net/weixin_42880082/article/details/129156012)):
打开本 example (VSCode或其他), 按以下步骤点击, 以制作文件系统:

<img>


#### (2) 根据单片机类型 烧录文件系统，此处以 ESP32 为例

PlatformIO 中为以下步骤(Arduino可参考 [ESP32 Arduino FAT文件系统详细使用教程](https://blog.csdn.net/weixin_42880082/article/details/129156012)):
按以下步骤点击, 以烧录文件系统:

<img>


### 6.Build and Flash 吧 ！


