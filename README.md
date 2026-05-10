## 本仓库是 [zh_pinyin_decoder](https://github.com/FRIEDparrot/zh_pinyin_decoder) 的 Arduino 移植版本，将原本的文件系统操作改为了 LittleFS 或 FatFS(FFat)，将一些常用函数 (如: word_match, char_match) 封装的更简单易用了，加入了类，并进行了 ESP32 上的测试，制作成了Arduino库结构。

### 推荐使用 RAM 和 Flash 较为充裕的单片机 (如: ESP32系列), 否则 可能需要在 user_config.h 中某些降低配置

## 使用方法：

### 1.去 Release 下载 [zh_pinyin_decoder-arduino](https://github.com/ioqite/zh_pinyin_decoder-arduino/releases/latest)

### 2.添加到 Arduino 库目录中, 如果使用 PlatformIO, 请参照 example 目录下的 test_all-platformio
### !!!!! 如使用 PlatformIO 开发, 必须将 zh_pinyin_decoder-arduino库 复制到 example的lib 中

### \[可选\] 3.在 user_config.h 中修改 Flash内用于存储 拼音码表和词库(json)文件 的文件系统:  \[推荐\] FatFS(FFat) 或 LittleFS：

```cpp
// 选择文件系统 (不要同时选择)
#define USE_FAT_FS               1  // [推荐] 使用 FatFS(FFat) 文件系统
#define USE_LITTLE_FS            0  // 使用LittleFS 文件系统
```

### \[可选\] 4.在 user_config.h 中修改 是否使用日志 及 日志输出方式


### 5.烧录文件系统：

> 注: 在本库的根目录下提供了 推荐的 ESP32 分区表 (zh_pinyin_ffat_partition.csv), 该分区表适用于 Flash 为 8MiB及以上 的单片机, 可自行更改 ffat/spiffs(也就是littlefs)分区大小 以适配 Flash
> 原词库 和 原拼音码表 均存放在 ffat_data 目录中

#### (1) 使用 默认拼音码表与词库 或 自定义
** \[推荐\] 如果使用 默认拼音码表与词库， 就无需制作文件系统，直接跳至 (2) 即可 **

自定义拼音码表与词库，PlatformIO 中为以下步骤 (Arduino可参考 [ESP32 Arduino FAT文件系统详细使用教程](https://blog.csdn.net/weixin_42880082/article/details/129156012)):
打开本 example (VSCode或其他), 按以下步骤点击, 以制作文件系统:

<img>


#### (2) 根据单片机类型 烧录文件系统，此处以 ESP32 为例

PlatformIO 中为以下步骤(Arduino可参考 [ESP32 Arduino FAT文件系统详细使用教程](https://blog.csdn.net/weixin_42880082/article/details/129156012)):
按以下步骤点击, 以烧录文件系统:

<img>


### 6.开始使用吧 ！

详细使用方法, 见 examples
> 示例程序位于 examples 目录下


--------

# 以下是原 README.md：

=============== ⭐😀UPDATE TO VERSION V1.6 😀⭐ ==================

基于C语言的，面向 stm32, esp32, ARDUINO 等等嵌入式平台的，以轻量级, 高支持性, 易用性， 易移植为目标编写和构建的中文拼音输入法。

拼音码表(.bin文件)和词库(.json) 文件均可采用外置 Flash 进行存储, 码表文件仅越20kb, 词库文件仅约1MB, 在汉字输入方面支持几乎所有的 GB2312 汉字(约6000个常用汉字) , 同时外置 json 文件支持了超过 20000 词的词库搜索 (此词库具体词汇见项目 https://github.com/ling0322/webdict , 提取了其中词频超过2000的4字以下词汇作为 json 词库内容) 

- 可以通过选择宏 `USE_ZH_HASH_BOOST = 1` 支持一种更快的类似哈希算法， 提升约 50% 以上搜索速度。 同时词库是可选功能， 设置 `USE_ZH_WORD_MATCH = 1` 启用词库功能， 支持词库自定义添加词汇。

- 尤其适合配合 LVGL (默认UTF8编码)等图形库进行移植和使用， 保证对中文编码和输入法的支持。

## 工程构建和运行

方法一: 用于测试的可执行.exe 文件在 build 目录下, 可以直接找到, 直接运行即可

### 1. Visual Studio

##### 对于 visual studio, 直接打开 GB2312search.vcxproj 并运行, 主程序为 GB2312search.cpp, 平台选用x86，x64 均可, 直接运行即可。

### 2. Cmake

项目支持利用 CmakeLists.txt 进行构建工程并生成 .exe 可执行文件，具体方法是在 windows 平台下, 采用如下 shell 命令 : 

```shell
cd build 
cmake ..
mingw32-make
./GB2312_pinyin_decoder
```

即可运行可执行文件 :
![](attachments/2024-09-20-00-31-32-image.png)

## 快速运行第一个 demo

第一个测试 :  词库完整性测试, 正常测试结果如图所示 : 

![](attachments/2024-08-28-01-23-01-image.png)

第二个单个汉字模糊匹配测试,  示例测试如下 :

![](attachments/2024-08-28-01-24-39-image.png)

第三个为拼音分词测试， 示例测试和结果如下 : 

![](attachments/2024-08-28-01-25-34-image.png)

第四个为带词库的完整的输入法测试， 示例测试结果 : 

![](attachments/2024-09-01-11-54-52-image.png)

(其中 nhsj 由于n有精确匹配, 会舍弃 ni 的模糊匹配选项, 因此 nhsj 不会得到"你好世界"搜索结果) 

### 如何移植到你的嵌入式平台

- 此输入法全部源的文件都在文件夹 zh_pinyin_decoder 下, 只需包含 zh_pinyin_decoder.h 即可, 目前测试平台为 windows, 只需稍加修改文件读取函数即可, 如果需要词库支持, 则需要包含 cJSON 文件夹下的文件, 用于 json 词库解析。 
- 在使用 FATFS 文件系统的情况下, 只需要修改其中的文件读写函数就可以了 

> TODO : 之后会增加 stm32 平台的移植示例

### 在词库 json 文件中添加自定义词汇

此输入法虽然**不允许修改zh_pinyin.bin字库文件**, 但是词库是可以自定义进行添加词汇的。

>  说明 :  当前词库最高支持词汇中文长度是4,  因此不支持添加4字以上的词汇 

添加词汇需要查询词汇的Unicode码，首先找到 portable/softwares 中的中英字符编码查询， 查询到对应的字符 Unicode 编码

![](attachments/2024-09-01-11-32-47-image.png)

然后在 json 搜索到对应位置添加就行了(至少应当保证在首字母相同的一组中进行添加)

![](attachments/2024-09-01-11-57-20-image.png)

> 需要说明的是， 如果需要删除词库内容, 需要注意修改 zh_pinyin_decoder.c 中的 word_dict_offset 定义, 这个数组定义了每一个字母打头时，开始搜索的起始位置偏移(需要放到对应字母搜索的前一个拼音的位置, 在这之后至少保留一个 ], 符号

### 程序的时间和空间性能

如果不采用词库功能, 则约需要 2kb 的 ROM 存储对应的拼音码表索引，如果设置宏 USE_ZH_HASH_BOOST = 1 时, 则可以提高约一倍以上的搜索速度, 但也需要额外的 2kb 左右的相关表 ROM 内存。

对于单个汉字的拼音搜索匹配，x86 平台运行一般需要的时间都在 1ms 以内。

在采用词库的情况下, 可以通过 `ZH_WORD_DICT_BUFFER_SZ` 设置单次读取词库 json 文件的缓冲区大小, 而缓冲区设置的局部变量会占用相对较大的RAM空间, 默认设置为 4kb (建议使用词库情况下留出 2 * ZH_WORD_DICT_BUFFER_SZ 大小的RAM 空间), 此情况下 x86 平台绝大部分词语匹配在 5ms 以内, 一般不超过10ms

### 版本更新日志

**V1.0 (2024.8.23):** 初次发布， 

**V1.1(2024.8.23)** : 修复 输入子串以 0 开头时的出错问题 

<b><mark style="background: transparent; color: red">V1.2(2024.8.25)</mark></b> : <b><mark style="background: transparent; color: red">添加了一种类似哈希表的新型拼音搜索算法作为可选的搜索算法, 该种算法可以在增加 2kb 左右ROM 的代价下, 提高搜索速度效率</mark></b>

>  如何使用哈希搜索算法: 只需要将 zh_pinyin_decoder.h  中的宏 `USE_ZH_HASH_BOOST` 设置为 1 即可  

V1.3(2024.8.27)  : 

1. **修改了码表(zh_pinyin_decoder.h)中**的字顺序:   `好号浩豪耗郝昊皓毫灏嚎蒿濠蚝壕颢镐嗥薅貉嚆` 为 `嚆貉薅嗥镐颢壕蚝濠蒿嚎灏毫皓昊郝耗豪号好` 使其更符合实际词频。

2. 修改了部分头文件中的宏定义, 如 `MAX_PINYIN_BUFFER_SZ` 改为  `MAX_CODE_BUFFER_SZ`, `MAX_PINYIN_SEARCH_TYPES` 改为 `MAX_CODE_SEARCH_TYPES` 等。 

3. 添加了主要文件中的函数声明和 license 声明部分 

4. **增加了拼音分词功能**, 添加了相应的拼音分词示例, 同时修复了测试程序中空格导致字符分不同串的问题。

5. 修复了在测试文件中的 res_str 变量在程序结束时, 栈附近溢出的问题 (Run-Time Check Failure #2 - Stack around the variable 'res_str' was corrupted.)

6. 修复提交中bin文件的 clrf 转换导致的位置问题， 目前已经可以正常直接下载压缩包进行测试和使用 

**V1.5(2024.9.1)**: 

1. 更新词库 json 文件, 进行重新排列。

2. 在拼音部分， 添加了拼音分词结果过滤功能 。

3. **添加了对 json 搜索词库的支持， 支持了分词和词库模糊搜索功能**, 在 `USE_ZH_WORD_MATCH` 设置为 1 即可，测试文件中的输入法示例同时支持多字词汇和单个汉字查找。 目前已经支持超20000词库搜索模糊匹配功能， 能够实现体验感较好的带词库输入法以及词库模糊输入匹配**

4. 更新主程序声明部分， 添加了对于词库的测试  

5. 更改少部分zh_pinyin_decoder 中的宏定义

**V1.6(2024.9.20)(当前版本)** : 

**添加了对 Cmake 直接采用 GNU 构建项目的支持**

- 修改了GB2312Serach.cpp 中的 `<string>` 为 `<string.h>` 兼容 Cmake 编译

- 修改了 LOG 的部分宏定义

- 添加原始词库的子模块引用
