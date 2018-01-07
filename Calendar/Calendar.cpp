//
// Created by Kangbeibei on 2018/1/7.
//
#include "Calendar.h"

int daysOfMonth[MONTHES_YEAR] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

Date::Date() {
    this->year = this->month = this->day =
    this->hour = this->minute = this->second =
    this->week = 0;
}

Date::Date(int y, int m, int d, int w, int h, int min, int s) {
    this->year = y;
    this->month = m;
    this->day = d;
    this->week = w;
    this->hour = h;
    this->minute = min;
    this->second = s;
}

Date::Date(const Date &date) {
    this->year = date.year;
    this->month = date.month;
    this->day = date.day;
    this->week = date.week;
    this->hour = date.hour;
    this->minute = date.minute;
    this->second = date.second;
}

int Date::getYear() {
    return year;
}

int Date::getMonth() {
    return month;
}

int Date::getDay() {
    return day;
}

int Date::getHour() {
    return hour;
}

int Date::getMinute() {
    return minute;
}

int Date::getSecond() {
    return second;
}

int Date::getWeek() {
    /* week未初始化，则求值
     * 已经初始化，直接返回week*/
    if (week == -1) {
//        week = calcWeek(*this);
        week = calcWeekOther(*this);
    }
    return week;
}

Date &Date::operator=(const Date &rhs) {
    if (this == &rhs) {
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

bool Date::operator<(const Date &rhs) {
    return (this->year < rhs.year || (this->year == rhs.year && this->month < rhs.month)
            || (this->year == rhs.year && this->month == rhs.month && this->day < rhs.day));
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int getDaysOfMonths(int year, int month) {
    if (month < 1 || month > MONTHES_YEAR) {
        return 0;
    }
    int days = daysOfMonth[month - 1];
    if (month == 2 && isLeapYear(year)) {
        days++;
    }

    return days;
}

/*---------------------------------------------------------------------
 * 计算星期：通过天数计算
 * 以1970年1月1日 星期四 为参照*/
int calcWeek(Date date) {
    Date dateBefore = Date(1970, 1, 1, 4);
    Date dateLater = Date(date);
    int tmp;
    long long int days = 0;
    if (dateLater < dateBefore) {
        dateLater = dateBefore;
        dateBefore = date;
    }
    /*两个日期相差一定年份*/
    if (dateBefore.getYear() < dateLater.getYear()) {
        /*计算两日期相隔的年数*/
        tmp = dateBefore.getYear() + 1;
        while (tmp < dateLater.getYear()) {
            if (isLeapYear(tmp)) {
                days += 366;
            } else {
                days += 365;
            }
            tmp += 1;
        }

        /*计算dateBefore剩余的天数*/
        tmp = dateBefore.getMonth();
        while (tmp <= MONTHES_YEAR) {
            if (tmp == dateBefore.getMonth()) {
                days -= dateBefore.getDay();
            }
            days += getDaysOfMonths(dateBefore.getYear(), tmp);
            tmp += 1;
        }

        /*计算dateLater已经过去的天数*/
        tmp = dateLater.getMonth();
        while (tmp >= 1) {
            if (tmp == dateLater.getMonth()) {
                days += dateLater.getDay();
            } else {
                days += getDaysOfMonths(dateLater.getYear(), tmp);
            }
            tmp--;
        }
    } else if (dateBefore.getMonth() < dateLater.getMonth()) {//两个日期位于同一年
        tmp = dateBefore.getMonth();
        while (tmp <= dateLater.getMonth()) {
            if (tmp == dateBefore.getMonth()) {
                days += getDaysOfMonths(dateBefore.getYear(), tmp) - dateBefore.getDay();
            } else if (tmp == dateLater.getMonth()) {
                days += dateLater.getDay();
            } else {
                days += getDaysOfMonths(dateBefore.getYear(), tmp);
            }
            tmp++;
        }
    } else {//两个日期位于同一个月
        days += dateLater.getDay() - dateBefore.getDay();
    }

    return static_cast<int>(dateBefore < date ?
                            ((days % 7) + 4) % 7 : (4 - days % 7 + 7) % 7);
}

/*-------------------------------------------------------------------
 * 计算星期
 * 每年计算一次，增大计算范围*/
int calcWeekOther(Date date) {
    int days = 0;
    int week;
    int tmp;
    Date stdDate = Date(1970, 1, 1);
    if (date.getYear() > stdDate.getYear()) { /*位于不同年份*/
        week = ((getLeftDays(1970, 1, 1) % 7) + 4) % 7;
        tmp = stdDate.getYear() + 1;
        while (tmp < date.getYear()) {
            if (isLeapYear(tmp)) {
                week = ((366 % 7) + week) % 7;
            } else{
                week = ((365 % 7) + week) % 7;
            }
            tmp++;
        }
        return ((getPassedDays(date.getYear(), date.getMonth(), date.getDay()) % 7) + week) % 7;
    } else if (date.getYear() == stdDate.getYear() &&
               date.getMonth() > stdDate.getMonth()) {/*位于同一年*/
        tmp = stdDate.getMonth();
        while (tmp <= date.getMonth()) {
            if (tmp == stdDate.getMonth()) {
                days += getDaysOfMonths(stdDate.getYear(), tmp) - stdDate.getDay();
            } else if (tmp == date.getMonth()) {
                days += date.getDay();
            } else {
                days += getDaysOfMonths(date.getYear(), tmp);
            }
            tmp++;
        }
        return ((days % 7) + 4) % 7;
    } else if (date.getYear() == stdDate.getYear() &&
               date.getMonth() == stdDate.getMonth() &&
               date.getDay() >= stdDate.getDay()){/*位于同一个月*/
        return  (((date.getDay() - stdDate.getDay()) % 7) + 4) % 7;
    } else{/*date比标准日期小*/
        week = ((4 - getPassedDays(1970, 1, 1) % 7) + 7) % 7;
        tmp = stdDate.getYear() - 1;
        while (tmp > stdDate.getYear()) {
            if (isLeapYear(tmp)) {
                week = ((week - 366 % 7) + 7) % 7;
            }
            week = ((week - 365 % 7) + 7) % 7;
            tmp--;
        }
        return (week - (getLeftDays(date.getYear(), date.getMonth(), date.getDay()) % 7) + 7) % 7;
    }
}

int getLeftDays(int year, int month, int day) {
    int days = 0;
    days += getDaysOfMonths(year, month) - day;
    for (int i = month + 1; i <= MONTHES_YEAR; i++) {
        days += getDaysOfMonths(year, i);
    }
    return days;
}

int getPassedDays(int year, int month, int day) {
    int days = 0;
    days += day;
    for (int i = month - 1; i >= 1; i--) {
        days += getDaysOfMonths(year, i);
    }
    return days;
}
/*--------------------------------------------------------------------*/