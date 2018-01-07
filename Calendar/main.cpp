#include <iostream>
#include "Calendar.h"
int main() {
    std::string Week[WEEK_DAY] = {
            "星期日","星期一","星期二","星期三","星期四","星期五","星期六"
    };

    Date date = Date(2018, 1, 7);
    std::cout << Week[date.getWeek()] << std::endl;
    return 0;
}