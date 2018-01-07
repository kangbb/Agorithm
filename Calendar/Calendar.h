//
// Created by Kangbeibei on 2018/1/7.
//

#ifndef CALENDAR_CALENDAR_H
#define CALENDAR_CALENDAR_H
#define MONTHES_YEAR 12
#define WEEK_DAY 7
#include <iostream>
class Date{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int week;
public:
    Date();
    Date(const Date &date);
    Date(int y, int m, int d, int w = -1, int h = 0, int min = 0, int s = 0);
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMinute();
    int getSecond();
    int getWeek();

    Date& operator=(const Date &rhs);
};
bool isLeapYear(int year);
int getDaysOfMonths(int year, int month);
int calcWeek(Date date);
#endif //CALENDAR_CALENDAR_H
