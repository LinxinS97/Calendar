# Elpis
It's just some interesting codes~
#pragma once

class Date {
private:
//数据成员：
	int year;
	int month;
	int day;
public:
//公有函数：
	Date(int y=1,int m=1,int d=1):year(y),month(m),day(d){}			//构造函数
	void SetYear(int y) { year = y; }								//设置年
	void SetMonth(int m) { month = m; }								//设置月
	void SetDay(int d) { day = d; }									//设置日
	int GetYear()const { return year; }								//返回年
	int GetMonth()const { return month; }							//返回月
	int GetDay()const { return day; }								//返回日
	Date operator+(int days);										//返回当前日期加上天数后得到的日期
	Date operator-(int days);										//返回当前日期减去天数后得到的日期
	static int GetYearDays(int y);									//年份y的天数
	static bool IsLeapyear(int y);									//判断y年是否为闰年
	static int GetMonthDays(const Date &d);							//日期d当前月份的天数
	static int DateToNum(const Date &d);							//返回公元1年1月1日起的天数
	static Date NumToDate(int n);									//由于从公元1年1月1日起的天数返回日期
	static int Week(const Date &d);									//返回日期是星期几
};

ostream &operator<<(ostream &out, const Date &d);					//重载输入运算符<<
istream &operator>>(istream &in, Date &d);							//重载输入运算符>>

Date Date::operator+(int days) {
	int n = DateToNum(*this) + days;								//从公元1年1月1日起的天数
	return NumToDate(n);											//返回日期
}

Date Date::operator-(int days) {
	int n = DateToNum(*this) - days;								//从公元1年1月1日起的天数
	return NumToDate(n);											//返回日期
}

bool Date::IsLeapyear(int y) {
	if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0)					//闰年	
		return true;
	else															//平年
		return false;
}

int Date::GetYearDays(int y) {
	if (IsLeapyear(y))												//闰年 366天
		return 366;
	else															//平年 365天
		return 365;
}

int Date::GetMonthDays(const Date&d) {
	int n;															//天数

	switch (d.GetMonth()) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		n = 31;														//1 3 5 7 8 10 12大月，每月为31天
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		n = 30;														//4 6 9 11为小月，每月为30天
		break;
	case 2:
		if (IsLeapyear(d.GetYear()))								//判断是否为闰年，闰年2月为29天，平年为28天
			n = 29;
		else
			n = 28;
	}

	return n;
}

int Date::DateToNum(const Date &d) {
	int y, n = 0;													//年份与天数

	for (y = 1; y < d.GetYear(); y++)								//累加从公元1年到year-1年的天数
		n += GetYearDays(y);
	for (int m = 1; m < d.GetMonth(); m++)							//累加从公元1月到month-1月的天数
		n += GetMonthDays(Date(y, m, 1));							
	n += d.GetDay();												//累加当前月过的天数

	return n;														//返回天数
}

Date Date::NumToDate(int n) {
	int y, m, d, rest = n;											//年，月，日和剩余天数

	for (y = 1, rest = n; rest > GetYearDays(y); y++)				//计算年份
		rest -= GetYearDays(y);						
	for (m = 1; rest > GetMonthDays(Date(y, m, 1)); m++)			//计算月份
		rest -= GetMonthDays(Date(y, m, 1));

	d = rest;														//日

	return Date(y, m, d);											//返回日期
}

ostream &operator<<(ostream &out, const Date &d) {					//重载输出运算符
	out << d.GetYear() << "年" << d.GetMonth() << "月" << d.GetDay() << "日";//通过cout输出Date对象的年月日属性
	return out;
}

istream &operator>>(istream &in, Date &d) {							//重载输入运算符>>
	int year, month, day;

	cin >> year >> month >> day;									//通过cin来输入Date的对象属性
	d = Date(year, month, day);

	return in;
}

int Date::Week(const Date &d) {
	int w;															//星期数
	w = DateToNum(d) % 7;											//通过公元元年1月1日对7取余来判断当前月份的当前日期为星期几
	return w;
}
