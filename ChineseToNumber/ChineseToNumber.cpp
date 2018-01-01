//
// Created by Kangbeibei on 2018/1/1.
//

//
// Created by Kangbeibei on 2018/1/1.
//

#include "ChineseToNumber.h"

typedef struct{
    const char* name; //中文权位名称
    int value; //10的倍数值
    bool secUnit; //是否是节权位
}CHN_NAME_VALUE;
CHN_NAME_VALUE chn_name_value[]={
        {"十", 10, false},
        {"百", 100, false},
        {"千", 1000, false},
        {"万", 10000, true},
        {"亿", 100000000, true}
};
std::map<std::string, int> CHN_TO_NUM = {
        {"零", 0},{"一", 1},{"二", 2}, {"三", 3},{"四", 4},
        {"五", 5}, {"六", 6},{"七", 7},{"八", 8}, {"九", 9}
};

unsigned int ChineseToNumber(const std::string& chnStr){
    unsigned int rtn = 0;
    unsigned int section = 0;
    int number = 0;
    bool secUnit = false;
    /*避免因机器不同而溢出，使用size_type*/
    std::string::size_type pos = 0;

    while(pos < chnStr.length()){
        std::cout<<chnStr.substr(pos, CHN_CHAR_LENGTH)<<std::endl;
        int num = ChineseToValue(chnStr.substr(pos, CHN_CHAR_LENGTH));
        /*数字还是单位*/
        if(num>=0){
            number = num;
            pos += CHN_CHAR_LENGTH;
            /*最后一位是数字，直接结束*/
            if(pos >= chnStr.length()){
                section += number;
                rtn += section;
                break;
            }
        }else{
            int unit = ChineseToUnit(chnStr.substr(pos, CHN_CHAR_LENGTH), secUnit);
            /*是节权位说明一个节已经结束*/
            if(secUnit){
                section = (section + number) * unit;
                rtn += section;
                section = 0;
            }else{
                section += (number * unit);
            }
            number = 0;
            pos += CHN_CHAR_LENGTH;
            if(pos >= chnStr.length()){
                rtn += section;
                break;
            }
        }
    }
    return rtn;
}
int ChineseToValue(std::string ch){
    if (ch !="零" && !CHN_TO_NUM[ch]){
        std::cout<<ch<<std::endl;
        std::cout<<CHN_TO_NUM[ch]<<std::endl;
        return -1;
    }else{
        return CHN_TO_NUM[ch];
    }
}

int ChineseToUnit(std::string ch, bool &secUnit){
    for(int i = 0; i  < sizeof(chn_name_value)/ sizeof(chn_name_value[0]); i++){
        if(ch == chn_name_value[i].name){
            secUnit = chn_name_value[i].secUnit;
            return chn_name_value[i].value;
        }
    }
}
