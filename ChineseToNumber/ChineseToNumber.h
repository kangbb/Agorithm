//
// Created by Kangbeibei on 2018/1/1.
//

#ifndef CHINESETONUMBER_CHINESETONUMBER_H
#define CHINESETONUMBER_CHINESETONUMBER_H

#include<iostream>
#include <map>
#define CHN_CHAR_LENGTH 3 //UTF-8,汉字占个字节

unsigned int ChineseToNumber(const std::string& chnStr);
int ChineseToValue(std::string ch);
int ChineseToUnit(std::string ch, bool &secUnit);
#endif //CHINESETONUMBER_CHINESETONUMBER_H
