/**
 ***************************** 声明 - Declaration ********************************
 * @file           : user_config.h
 * @original_author: FriedParrot (https://github.com/FriedParrot)
 * @author         : Ported by Ioqit (https://github.com/Ioqite)
 * @version        : v2.0-arduino
 * @original_date  : 2024-09-20
 * @date           : 2026-05-09 (last modified)
 * @derived_from   : by FriedParrot/zh_pinyin_decoder(v1.6) (https://github.com/FriedParrot/zh_pinyin_decoder)
 * @brief          : 中文拼音解码输入法的用户配置文件 - User configuration file for chinese pinyin decoding inputting method
 * @copyright      : Copyright (c) 2024 FriedParrot
 *                   Copyright (c) 2026 Ioqit (Arduino Port)
 * @license        : MIT license (https://opensource.org/license/mit)
 *****************************************************************************
 * @attention
 * 此文件是中文拼音解码输入法的用户配置文件。
 * 推荐在此文件中修改设置以适应你的需求。
 * This file is the user configuration file for the Chinese Pinyin decoding input method.
 * It is recommended to modify the settings in this file to suit your needs.
 * 
 *****************************************************************************
 */

// =========================================================================

#include <Arduino.h>

// 是否使用日志
#define ZH_USE_LOG        1 
#if (ZH_USE_LOG == 1)
#define ZH_LOG(msg, ...)   Serial.printf(msg, ##__VA_ARGS__)
#endif

// =========================================================================

// 选择文件系统 (不要同时选择) - Choose File System (Don't choose both)
#define USE_FAT_FS               1  // [推荐] 使用 FatFS(FFat) 文件系统 - [Recommended] Use FatFS (FFat)
#define USE_LITTLE_FS            0  // 使用 LittleFS 文件系统 - Use LittleFS
// 如果要使用 Little FS, 请在分区表中取消SPIFFS的注释并注释FFat
// 注意：如果要使用词库功能，你需要使用FatFS（LittleFS因为某种原因无法写入过大文件（例如词库文件））

// If you want to use Little FS, please uncomment SPIFFS in the partition table and comment out FFat
// NOTE: If you want to use the dictionary feature, you need to
//       use FatFS (because LittleFS, for some reason, 
//       cannot write overly large files, such as dictionary files).

// =========================================================================

// 可选功能设置 - Optional Feature Settings
#if (USE_FAT_FS == 1)
// [推荐] 使用词库匹配 - [Recommended] Use match word support option
#define USE_ZH_WORD_MATCH           1
#endif
// [推荐] 使用哈希加速（匹配更快但占用更多ROM） - [Recommended] Use the hash table method (search faster but take more ROM)
#define USE_ZH_HASH_BOOST           1

// =========================================================================

// 文件路径设置 - File Path Settings：

//   码表文件名 - code table file name
#define ZH_CODE_TABLE_FILE_NAME      "/zh_pinyin.bin"
//   词库文件名 - dictionary json file name
#define ZH_WORD_DICTIONARY_FILE_NAME "/zh_word_dict.json" 

// =========================================================================

