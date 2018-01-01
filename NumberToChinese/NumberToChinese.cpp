//
// Created by Kangbeibei on 2017/12/31.
//
#include "NumberToChinese.h"

#define CHN_NUM_CHAR_COUNT 10
const char *chnNumChar[CHN_NUM_CHAR_COUNT] = {
        "零", "一", "二", "三", "四", "五", "六", "七", "八", "九"
};
const char *chnUnitSection[] = {"", "万", "亿", "万亿"};
const char *chnUnitChar[] = {"", "十", "百", "千"};

//num = 0
void NumberToChinese(unsigned int num, std::string &chnStr) {
    int unitPos = 0; //weight position
    std::string strlns;
    std::string a = "中国";
    bool needZero = false;

    if (num == 0){
        chnStr.insert(0, chnNumChar[0]);
        return;
    }

    while (num > 0) {
        unsigned int section = num % 10000;
        if (needZero) {
            chnStr.insert(0, chnNumChar[0]);
        }
        SectionToChinese(section, strlns);
        /*是否需要节权位*/
        strlns += (section != 0) ? chnUnitSection[unitPos] : chnUnitSection[0];
        chnStr.insert(0, strlns);

        /*千位是0需要在下一个section补零*/
        needZero = (section < 1000) && (section > 0);
        num = num / 10000;
        unitPos++;
        strlns = "";
    }
}

void SectionToChinese(unsigned int section, std::string &chnStr) {
    std::string strlns;
    int unitPos = 0;
    bool zero = true;
    while (section > 0) {
        int v = section % 10;
        if (v == 0) {
            if((section == 0) || !zero){
                /*zero的作用是对多个连续的零，只保持一个零*/
                zero = true;
                chnStr.insert(0, chnUnitChar[v]);
            }
        }else{
            /*至少有一个数字不是零*/
            zero = false;
            /*此位对应中文数字*/
            strlns = chnNumChar[v];
            /*此位对应的中文权位*/
            strlns += chnUnitChar[unitPos];
            chnStr.insert(0, strlns);
        }
        unitPos++;
        section = section / 10;
    }
}