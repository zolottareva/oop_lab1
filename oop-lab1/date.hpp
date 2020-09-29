//
//  date.hpp
//  oop-lab1
//
//  Created by Золотарева Марина Олеговна on 12.09.2020.
//

#ifndef date_hpp
#define date_hpp

#include <stdio.h>
#include "date.h"
#include <vector>
#include <exception>
#include <ctime>
#include <chrono>
#include <string>
#include <map>
using namespace date;
using namespace std::chrono;
using std::vector;
using std::string;
const vector <int> numberOfdays {0,31,28,31,30,31,30,31,31,30,31,30,31};
bool checkLeap(int y)
{
    if(y%4 != 0) return false;
    if(y%100 != 0) return true;
    if (y%400 == 0) return true;
    return false;
}
int dayToInt(const day &d)
{
    std::map<day, int> dayToInt{{day(1), 1}, {day(2), 2}, {day(3),3}, {day(4), 4}, {day(5), 5},{day(6), 6}, {day(6), 6}, {day(7),7}, {day(8), 8}, {day(9), 9},{day(10), 10}, {day(11), 11}, {day(12),12}, {day(13), 13}, {day(14), 14},{day(15), 15}, {day(16), 16}, {day(17),17}, {day(18), 18}, {day(19), 19},{day(20), 20}, {day(21), 21}, {day(22),22}, {day(23), 23}, {day(24), 24},{day(25), 25}, {day(26), 26}, {day(27),27}, {day(28), 28}, {day(29), 29},{day(30), 30}, {day(31), 31}};
    return dayToInt[d];
}
string weekdayToString(const weekday &wd)
{
    if(wd == weekday(0)) return "Sunday";
    if(wd == weekday(1)) return "Monday";
    if(wd == weekday(2)) return "Tuesday";
    if(wd == weekday(3)) return "Wednesday";
    if(wd == weekday(4)) return "Thursday";
    if(wd == weekday(5)) return "Friday";
    return "Saturday";
}
class Time
{
private:
    int hour;
    int minute;
    int second;
public:
    Time()
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
    Time(int h, int m, int s)
    {
        hour = h;
        minute = m;
        second = s;
    }
    bool ok()
    {
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) return 0;
        return 1;
    }
    int get_hour() const
    {
        return hour;
    }
    int get_minute() const
    {
        return minute;
    }
    int get_second() const
    {
        return second;
    }
    friend bool operator >(Time lhs, Time rhs);
    friend Time operator+(Time lhs, Time rhs);
    friend Time operator-(Time lhs, Time rhs);
};
bool operator>(Time lhs, Time rhs)
{
    if(lhs.hour > rhs.hour) return 1;
    if(lhs.hour < rhs.hour) return 0;
    if(lhs.minute > rhs.minute) return 1;
    if(lhs.minute < rhs.minute) return 0;
    if(lhs.second > rhs.second) return 1;
    if(lhs.second < rhs.second) return 0;
    return 0;
}
Time operator+(Time lhs, Time rhs)
{
    int secondsLhs = lhs.hour * 3600 + lhs.minute * 60 + lhs.second;
    int secondsRhs = rhs.hour * 3600 + rhs.minute * 60 + rhs.second;
    int plus = secondsLhs + secondsRhs;
    return {plus/3600, (plus - plus/3600)/60, plus - plus/3600 - (plus - plus/3600)/60};
}
Time operator-(Time lhs, Time rhs)
{
    int secondsLhs = lhs.hour * 3600 + lhs.minute * 60 + lhs.second;
    int secondsRhs = rhs.hour * 3600 + rhs.minute * 60 + rhs.second;
    int minus = secondsLhs - secondsRhs;
    return {minus/3600, (minus - minus/3600)/60, minus - minus/3600 - (minus - minus/3600)/60};
}
class Date
{
private:
    int yr;
    int month;
    int day;
    int hourZone;
    bool isLeap;
    string weekday;
public:
    Time time;
    Date(int y, int m, int d, int h, int min, int s, int hz)
    {
        auto ymd = year{y}/m/d;
        time = {h,min,s};
        if(!ymd.ok()) throw std::invalid_argument("Wrong data format");
        if(!time.ok()) throw std::invalid_argument("Wrong time format");
        yr = y;
        month = m;
        day = d;
        if(hz < -720 || hz > 720 || hz%15!=0) throw std::invalid_argument("Wrong hour zone");
        hourZone = hz;
        weekday = weekdayToString(year_month_weekday(ymd).weekday());
    }
    Date(int y, int m, date::weekday wd, int number, int h, int min, int s, int hz)
    {
        time = {h,min,s};
        auto ymd = year_month_day{m/wd[number]/y};
        if(!ymd.ok()) throw std::invalid_argument("Wrong data format");
        if(!time.ok()) throw std::invalid_argument("Wrong time format");
        yr = y;
        month = m;
        day = dayToInt(ymd.day());
        weekday = weekdayToString(wd);
    }
    Time get_time() const
    {
        return time;
    }
    int get_year() const
    {
        return yr;
    }
    int get_month() const
    {
        return month;
    }
    int get_day() const
    {
        return day;
    }
    int get_hourZone() const
    {
        return hourZone;
    }
    int numberOfDaysInCurrentYear() const
    {
        int result = 0;
        for(int i = 1; i < month; i++)
        {
            if(checkLeap(yr) && i == 2) result+=29;
            result+=numberOfdays[month];
        }
        result+=day;
        return result;
    }
    int countNumberOfWeekInTheMonth()
    {
        return day/7;
    }
    int countNumberOfWeekInTheYear()
    {
        return numberOfDaysInCurrentYear()/7;
    }
};
Date parseSecondsToDate(long long sec)
{
    int year = 1;
    while(sec > 3600*24*(365+checkLeap(year)))
    {
        sec -= 3600*24*(365+checkLeap(year));
        year++;
    }
    int month = 1;
    while(sec > 3600 * 24 * numberOfdays[month] || (checkLeap(year) && month == 2 && sec > 29 * 3600 * 24))
    {
        if(month > 12)
        {
            year++;
            month = 1;
        }
        sec-=3600 * 24 * numberOfdays[month];
        if(checkLeap(year) && month == 2) sec-=3600*24*1;
        month++;
    }
    int day = 1;
    while(sec > 3600 * 24)
    {
        if(day > numberOfdays[month] || (checkLeap(year) && month == 2 && day > 29))
        {
            month++;
            day = 1;
            
        }
        sec -= 3600 * 24;
        day++;
    }
    int hour = 0;
    while(sec > 3600)
    {
        sec-= 3600;
        hour++;
    }
    int minute = 0;
    while(sec > 60)
    {
        sec-= 60;
        minute++;
    }
    int second = sec;
    return {year, month, day, hour, minute, second, 0};
}
int operator-(Date lhs, Date rhs)
{
    struct std::tm a = {lhs.time.get_hour(),lhs.time.get_minute(),lhs.time.get_second(),lhs.get_day(),lhs.get_month()-1,lhs.get_year() - 1900};
    struct std::tm b = {rhs.time.get_hour(),rhs.time.get_minute(),rhs.time.get_second(),rhs.get_day(),rhs.get_month()-1,rhs.get_year() - 1900};
    std::time_t x = std::mktime(&a);
    std::time_t y = std::mktime(&b);
    int difference = std::difftime(x, y);
    return difference; // in seconds
}
Date operator+(Date lhs, int difference)
{
    int year = lhs.get_year();
    while(difference > 3600*24*(365+checkLeap(year)))
    {
        difference -= 3600*24*(365+checkLeap(year));
        year++;
    }
    int month = lhs.get_month();
    while(difference > 3600 * 24 * numberOfdays[month] || (checkLeap(year) && month == 2 && difference > 29 * 3600 * 24))
    {
        if(month > 12)
        {
            year++;
            month = 1;
        }
        difference-=3600 * 24 * numberOfdays[month];
        month++;
    }
    int day = lhs.get_day();
    while(difference > 3600 * 24)
    {
        if(day > numberOfdays[month] || (checkLeap(year) && month == 2 && day > 29))
        {
            month++;
            day = 1;
            
        }
        difference -= 3600 * 24;
        day++;
    }
    int hour = lhs.time.get_hour();
    while(difference > 3600)
    {
        difference-= 3600;
        hour++;
    }
    int minute = lhs.time.get_minute();
    while(difference > 60)
    {
        difference-= 60;
        minute++;
    }
    int second = difference;
    if (minute > 59)
    {
        minute = 0;
        hour++;
    }
    if(hour > 23)
    {
        hour = 0;
        month++;
    }
    if(day > numberOfdays[month] || (checkLeap(year) && month == 2 && day > 29))
    {
        day -= numberOfdays[month];
        month++;
    }
    if(month > 12)
    {
        month = 1;
        year++;
    }
    return {year, month, day, hour, minute, second, lhs.get_hourZone()};
}
Date operator-(Date date, int difference)
{
    int numberOfLeaps = date.get_year()/4 - date.get_year()/100 + date.get_year()/400;
    if(checkLeap(date.get_year()) && date.get_month() > 2) numberOfLeaps++;
    long long seconds = date.get_year() * 365 * 24 * 3600 + (date.numberOfDaysInCurrentYear() + numberOfLeaps)*24*3600 + date.time.get_hour()*3600+ date.time.get_minute()*60 + date.time.get_second();
    seconds -= difference;
    return parseSecondsToDate(seconds);
}
Date convertToNewHourZone(Date date, const int newHZ)
{
    int hzDifference = newHZ - date.get_hourZone();
    if(hzDifference > 0) return date+hzDifference;
    else return date-(-hzDifference);
}

#endif /* date_hpp */
