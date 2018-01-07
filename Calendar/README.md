# Calendar
# 功能
1. 计算星期
2. 阳历、农历转换
3. 计算二十四节气
# 使用
### 1.计算星期
创建一个Date,使用Date的getWeek()即可获取星期。
```objectivec
std::string Week[WEEK_DAY] = {
            "星期日","星期一","星期二","星期三","星期四","星期五","星期六"
    };

Date date = Date(1960, 1, 3);
std::cout << Week[date.getWeek()] << std::endl;
return 0;
```