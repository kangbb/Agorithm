#include <iostream>
#include "NumberToChinese.h"
int main() {
    std::string result;
    unsigned  int num;
    std::cout<<"请输入需转换的数字：";
    std::cin>>num;
    NumberToChinese(num, result);
    std::cout<<"转换结果："<<result<<std::endl;
}