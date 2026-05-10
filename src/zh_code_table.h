/**
 ***************************** 声明 - Declaration ********************************
 * @file           : zh_code_table.h
 * @original_author: FriedParrot (https://github.com/FriedParrot)
 * @author         : Ported by Ioqit (https://github.com/Ioqite)
 * @version        : v2.0-arduino
 * @original_date  : 2024-09-20
 * @date           : 2026-05-09 (last modified)
 * @derived_from   : by FriedParrot/zh_pinyin_decoder(v1.6) (https://github.com/FriedParrot/zh_pinyin_decoder)
 * @brief          : 中文拼音码表定义头文件 - Chinese pinyin code table definition header file
 * @copyright      : Copyright (c) 2024 FriedParrot
 *                   Copyright (c) 2026 Ioqit (Arduino Port)
 * @license        : MIT license (https://opensource.org/license/mit)
 *****************************************************************************
 * @attention
 * zh_code_table.h 和 zh_code.c 依赖于文件 "zh_pinyin.bin"
 * 其路径在 user_config.h 中指定
 * zh_code_table.h and zh_code.c relys on files "zh_pinyin.bin"
 * which path is specified in user_config.h
 *
 * @warning 不要修改此文件或 .bin 文件，否则解码将无法正常工作。
 * Don't modify this file, or decoding would not work correctly
 *****************************************************************************
 */
#ifndef __ZH_CODE_TABLE_H
#define __ZH_CODE_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>

typedef struct {
    const uint8_t   table_length;       // length of code table 
    const uint32_t  char_start;         // start location of each character

    const char**    code_table;         // following pinyin table
    const uint8_t*  code_table_num;     // number of chinese character
    const uint16_t* code_offset;        // each code table offset from start location
}__code_index_t;

extern const __code_index_t code_index[];

#ifdef __cplusplus
    }
#endif //

#endif

