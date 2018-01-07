//
// Created by Kangbeibei on 2018/1/7.
//
#include "Calendar.h"
int daysOfMonth[MONTHES_YEAR] = {
        31, 28, 31, 30, 31, 30 ,31, 31, 30, 31, 30, 31
};
Date::Date(){
    this->year = this->month = this->day =
    this->hour = this->minute = this->second =
    this->week = 0;
}
Date::Date(int y, int m, int d, int w, int h, int min, int s){
    this->year = y;
    this-> month = m;
    this->day = d;
    this->week = w;
    this->hour = h;
    this->minute = min;
    this->second = s;
}
Date::Date(const Date &date){
    this->year = date.year;
    this->month = date.month;
    this-> day = date.day;
    this->week = date.week;
    this->hour = date.hour;
    this-> minute = date.minute;
    this->second = date.second;
}
int Date::getYear(){
    return year;
}
int Date::getMonth(){
    return month;
}
int Date::getDay(){
    return day;
}
int Date::getHour(){
    return hour;
}
int Date::getMinute(){
    return minute;
}
int Date::getSecond(){
    return second;
}
int Date::getWeek(){
    /* week未初始化，则求值
     * 已经初始化，直接返回week*/
    if(week == -1){
        week = calcWeek(*this);
    }
    return week;
}
Date& Date::operator=(const Date &rhs){
    if(this == &rhs){
        return *this;
    }

    this->year = rhs.year;
    this->month = rhs.month;
    this->day = rhs.day;
    this->week = rhs.week;
    this->hour = rhs.hour;
    this->minute = rhs.minute;
    this->second = rhs.second;
}
bool isLeapYear(int year){
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
int getDaysOfMonths(int year, int month){
    if(month < 1 || month > MONTHES_YEAR){
        return 0;
    }
    int days = daysOfMonth[month - 1];
    if(month == 2 && isLeapYear(year)){
        days++;
    }

    return days;
}

/*计算星期：通过天数计算
 * 以1970年1月1日 星期四 为参照*/
int calcWeek(Date date){
    Date dateBefore = Date(1970, 1, 1, 4);
    Date dateLater = Date(date);
    int tmp;
    long long int days = 0;
    if(dateBefore.getYear() > dateLater.getYear()){
        dateLater = dateBefore;
        dateBefore = date;
    }

    /*计算两日期相隔的年数*/
    tmp = dateBefore.getYear() + 1;
    while (tmp < dateLater.getYear()){
        if(isLeapYear(tmp)){
            days += 366;
        }else{
            days += 365;
        }
        tmp += 1;
    }

    /*计算dateBefore剩余的天数*/
    tmp = dateBefore.getMonth();
    while(tmp <= MONTHES_YEAR){
        if(tmp == dateBefore.getMonth()){
            days -= dateBefore.getDay();
        }
        days +=  getDaysOfMonths(dateBefore.getYear(), tmp);
        tmp += 1;
    }


    /*计算dateLater已经过去的天数*/
    tmp = dateLater.getMonth();
    while(tmp >= 1){
        if(tmp == dateLater.getMonth()){
            days += dateLater.getDay();
        }else{
            days += getDaysOfMonths(dateLater.getYear(), tmp);
        }
        tmp--;
    }

    return static_cast<int>(dateBefore.getYear() == 1970 ?
                  ((days % 7) + 4) % 7 : (4 - days % 7 + 7) % 7);
}
