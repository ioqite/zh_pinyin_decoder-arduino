/**
 ***************************** 声明 - Declaration ********************************
 * @file           : test_all-arduino.ino
 * @original_author: FriedParrot (https://github.com/FriedParrot)
 * @author         : Ported by Ioqit (https://github.com/Ioqite)
 * @version        : v2.0-arduino
 * @original_date  : 2024-09-20
 * @date           : 2026-05-09 (last modified)
 * @derived_from   : by FriedParrot/zh_pinyin_decoder(v1.6) (https://github.com/FriedParrot/zh_pinyin_decoder)
 * @brief          : 中文拼音输入法的解码器示例程序 - Decoder example program for chinese pinyin inputting method
 * @copyright      : Copyright (c) 2024 FriedParrot
 *                   Copyright (c) 2026 Ioqit (Arduino Port)
 * @license        : MIT license (https://opensource.org/license/mit)
 *****************************************************************************
 * @attention
 * 此文件是整个输入法的示例程序, 包含了所有测试用例。
 * This is the c++ example program for the whole inputting method.
 * 
 * test1 : 词库完整性测试 (library integrity test)
 * test2 : 单个汉字模糊匹配测试 (vague match test: input string for vague match)
 * test3 : 拼音分词测试 (pinyin split test : mixed pinyin string (no space))
 * test4 : 带词库的完整的输入法测试 (word match test : input mixed pinyin string (no space)) 
 * 所有测试用例的详细信息都可以在 https://github.com/FRIEDparrot/zh_pinyin_decoder 找到
 * All the test cases can be found in detail at https://github.com/FRIEDparrot/zh_pinyin_decoder
 * 
 * @note 原 note: 
 * 这种输入法是一种轻量的、可移植的中文拼音输入法。
 * 你可以将它移植到你的嵌入式平台（例如，stm32、esp32 或 Arduino）用于提供中文拼音输入识别支持。
 * This inputting method is a lightweight, portable Chinese pinyin inputting method.
 * You can port it to your embedded platform (for example, stm32, esp32 or audrino) 
 * to give support for Chinese pinyin input recognition. 
 *****************************************************************************
 */

#include <Arduino.h>
#include "zh_pinyin_decoder.hpp"

void test1();
void test2();
void test3();
void test4();
void zh_pinyin_show_split(String str, const match_case_list_t *m_list);

ZhPinyinDecoder zh_decoder;

void setup() {
    Serial.begin(115200);
    
    Serial.println("\n============================= Test Start ==================================");
    test1(); // 词库完整性测试
    test2(); // 单个汉字模糊匹配测试
    test3(); // 拼音分词测试 (无空格)
#if (USE_ZH_WORD_MATCH == 1)
    test4(); // 带词库的完整的输入法测试 (无空格)
#endif
    Serial.println("\n============================= Test END ==================================\n");
}

void loop() {}


// 词库完整性测试 (library integrity test)
void test1() {
    Serial.println("\n********** Test 1 : 词库完整性测试 (library integrity test) ***********");
    
    clock_t start_time = clock();
    char res_str[MAX_CODE_BUFF_SZ];
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < code_index[i].table_length; j++) {
            const char* str = code_index[i].code_table[j];
            memset(res_str, 0, sizeof(res_str));
            uint8_t br;
            if (!zh_match_code_prec(str, res_str, MAX_CODE_SEARCH_TYPES, &br)) {
                Serial.printf("%s : %d %s\n", str, br, String(res_str).c_str());
            } else {
                Serial.println("No file to match !");
                break;
            }
        }
    }
    Serial.printf("executing time : %d ms \n", clock() - start_time);
}

// 单个汉字模糊匹配测试 (vague match test: input string for vague match)
void test2() {
    Serial.println("\n*********** Test2: 单个汉字模糊匹配测试 (vague match test) ******************");

    for (String input_str : {"de", "di", "du", "hao", "shi", "jie"}) {
        clock_t start_time = clock(); // 计时

        auto result = zh_decoder.char_match(input_str); // 模糊匹配

        Serial.printf("\nMatch: %s, Time: %d ms\n", input_str.c_str(), clock() - start_time);
        if (result.empty()) {
            Serial.println("\nMatch failed : nothing to match");
        } else {
            // 显示匹配结果
            for (int i = 0; i < result.size(); i++) {
                Serial.printf("%d:%s  ", i+1, result[i].c_str());
            }
            Serial.println();
        }
    }
}

// 拼音分词测试 (无空格) (pinyin split test : mixed pinyin string (no space))
void test3() {
    Serial.println("\n*********** Test3: 拼音分词测试 (pinyin split test) ******************");

    for (String input_str : {"shijie", "nihao", "duqu", "haode", "wancheng"}) {
        clock_t start_time = clock();
        match_case_list_t* m_list = zh_pinyin_get_split(input_str.c_str());
        clock_t end_time = clock();

        zh_pinyin_show_split(input_str, m_list);
        Serial.printf("Time : %d ms\n", end_time - start_time);
    }
}

#if (USE_ZH_WORD_MATCH == 1)
// 带词库的完整的输入法测试 (无空格) (word match test : input mixed pinyin string (no space))
void test4() {
    Serial.println("\n******************* Test4: 带词库的完整的输入法测试 (word match test) *******************");
    for (String input_str : {"nihao", "shijie", "duqu", "shiwu", "weishenme"}) {
        String split_result;    // 分词结果
        
        clock_t start_time = clock(); // 记时开始
        auto result = zh_decoder.word_match_and_split(input_str, split_result); // 获取匹配结果
        clock_t end_time = clock();   // 记时结束
        
        if (result.empty()) {
            Serial.println("\nMatch failed : nothing to match");
            continue;
        }
        Serial.printf("\nMatch: %s, Time: %d ms\n", split_result.c_str(), end_time - start_time);
        
        for (uint8_t i = 0; i < result.size();) {
            Serial.printf("%d: %s  ", i+1, result[i++].c_str());
        }
        Serial.println();
    }
}
#endif

// 显示拼音分词结果
void zh_pinyin_show_split(String str, const match_case_list_t* m_list) {
    if (m_list == NULL || m_list->head == NULL) {
        Serial.println("\n找不到匹配的拼音字符串 !!!");
        return;
    }
    match_case_node_t* m = m_list->head;
    Serial.printf("-------------- 分割方法: %d 种 ----------------\n", m_list->num);
    for (int i = 0; i < m_list->num; i++) {
        int j = 0;
        for (int k = 0; k < str.length(); k++) {
            if (m->spm[j] == k) { // 获取分割点 并 判断是否打印空格
                Serial.print(" ");
                j++;
            }
            Serial.print(str[k]);
        }
        // 转换权重为二进制(字符串)
        char s_tmp[10];
        __itoa(m->wt, s_tmp, 2);
        Serial.printf("\t 长度: %d, 权重: %d (%s)\n", m->length, m->wt, s_tmp);
        m = m->next;
    }
}

