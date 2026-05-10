/**
 ***************************** 声明 - Declaration ********************************
 * @file           : zh_hash_boost.h
 * @original_author: FriedParrot (https://github.com/FriedParrot)
 * @author         : Ported by Ioqit (https://github.com/Ioqite)
 * @version        : v2.0-arduino
 * @original_date  : 2024-09-20
 * @date           : 2026-05-09 (last modified)
 * @derived_from   : by FriedParrot/zh_pinyin_decoder(v1.6) (https://github.com/FriedParrot/zh_pinyin_decoder)
 * @brief          : 拼音匹配的哈希码表文件 - hash code table file for pinyins match
 * @copyright      : Copyright (c) 2024 FriedParrot
 *                   Copyright (c) 2026 Ioqit (Arduino Port)
 * @license        : MIT license (https://opensource.org/license/mit)
 *****************************************************************************
 * @attention
 * 当选项 USE_ZH_HASH_BOOST 设置为 1 时，需要此文件
 * 使用此选项会多占用 2KB 的 ROM 空间，但搜索速度会快得多
 * This file is need when option USE_ZH_HASH_BOOST is set to 1
 * Using this option would cost 2kb more ROM space but can search much faster
 * 
 * @warning 不要修改此文件或 .bin 文件，否则解码将无法正常工作。
 * Don't modify this file, or decoding would not work correctly
 *****************************************************************************
 */
#ifndef __ZH_HASH_BOOST_H
#define __ZH_HASH_BOOST_H

#ifdef __cplusplus
    extern "C"{
#endif

#include <stdint.h>
#include  <stdlib.h>

#define ZH_HASH_TABLE_DIV     11

typedef struct zh_hash_node_t{
    uint8_t num;
    uint8_t* idx_list;
}__zh_hash_node_t;

extern const __zh_hash_node_t** hash_list[];

uint8_t zh_hash_inlist(const char* str);

#ifdef __cplusplus
    }
#endif


#endif
