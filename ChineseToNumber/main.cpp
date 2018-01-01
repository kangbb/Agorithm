#include <iostream>
#include "ChineseToNumber.h"
int main() {
    std::string str;
    std::cout << "请输入需要转换的中文数字：";
    std::cin>>str;
    std::cout<<ChineseToNumber(str)<<std::endl;
    return 0;
}