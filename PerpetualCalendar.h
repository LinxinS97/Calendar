//# Elpis
//It's just some interesting codes~
#pragma once

//预处理12个月的汉字
string Month[] = { "一","二","三","四","五","六","七","八","九","十","十一","十二" };

//预处理每周的汉字
string week[] = { "日","一","二","三","四","五","六","七" };

//预处理二十四节气汉字
string The24SolarTerms[] = { "小寒","大寒","立春","雨水","惊蛰","春分","清明","谷雨","立夏","小满","芒种","夏至","小暑","大暑","立秋","处暑","白露","秋分","寒露","霜降","立冬","小雪","大雪","冬至" };

//预处理二十四节气在二十一世纪的C值
double C21[] = { 5.4055 , 20.12 , 3.87 , 18.73 , 5.63 , 20.646 , 4.81, 20.1, 5.52, 21.04, 5.678, 21.37, 7.108, 22.83, 7.5, 23.13, 7.646, 23.042, 8.318, 23.438, 7.438, 22.36, 7.18, 21.94  };

//预处理十二生肖
string TwelveSymbolicAnimals[] = { "猴","鸡","狗","猪","鼠","牛","虎","兔","龙","蛇","马","羊" };

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
	//Date operator+(int days);										//返回当前日期加上天数后得到的日期
	//Date operator-(int days);										//返回当前日期减去天数后得到的日期
	static int GetYearDays(int y);									//年份y的天数
	static bool IsLeapyear(int y);									//判断y年是否为闰年
	static int GetMonthDays(const Date &d);							//日期d当前月份的天数
	static int DateToNum(const Date &d);							//返回公元1年1月1日起的天数
	//static Date NumToDate(int n);									//由于从公元1年1月1日起的天数返回日期
	static int Week(const Date &d);									//返回日期是星期几
	static void T24ST(const Date &d,int*st,int n);					//计算二十四节气
	void Run();														//打印万年历
};

ostream &operator<<(ostream &out, const Date &d);					//重载输入运算符<<
istream &operator>>(istream &in, Date &d);							//重载输入运算符>>

/*
Date Date::operator+(int days) {
	int n = DateToNum(*this) + days;								//从公元1年1月1日起的天数
	return NumToDate(n);											//返回日期
}

Date Date::operator-(int days) {
	int n = DateToNum(*this) - days;								//从公元1年1月1日起的天数
	return NumToDate(n);											//返回日期
}
*/

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

/*
Date Date::NumToDate(int n) {
	int y, m, d, rest = n;											//年，月，日和剩余天数

	for (y = 1, rest = n; rest > GetYearDays(y); y++)				//计算年份
		rest -= GetYearDays(y);						
	for (m = 1; rest > GetMonthDays(Date(y, m, 1)); m++)			//计算月份
		rest -= GetMonthDays(Date(y, m, 1));

	d = rest;														//日

	return Date(y, m, d);											//返回日期
}
*/

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

void Date::T24ST(const Date &d,int *st,int n) {						//通过这个函数对main中的数组进行处理来获取当年24节气的日数
	int y;															//年
	y=d.GetYear();													//获取当前年
	for (int i = 0; i < n; i++) {
		st[i] = (y * 0.2422 + C21[i]) - ((y  / 4)-15);				//根据21世纪C值计算二十四节气日期,计算方法：[Y×D+C]-L 
	}


	//特殊情况
	if (y == 2026)
		st[1] -= 1;
	if (y == 2084)
		st[3] += 1;
	if (y == 2008)
		st[7] += 1;
	if (y == 2016)
		st[10] += 1;
	if (y == 2002)
		st[12] += 1;
	if (y == 2089) {
		st[17] += 1;
		st[18] += 1;
	}
	if (y == 2021)
		st[21] -= 1;
	if (y == 2019)
		st[22] -= 1;
	if (y == 2082)
		st[23] += 1;
}

void Date::Run() {
	Date d;
	cout << "*****************************************************" << endl;
	for (int i = 0; i < 5; i++) {
		if (i == 2) {
			cout << "**万年历—拓展版                                   **" << endl;
			cout << "**由于算法缺陷，二十四节气可能有1天的误差          **" << endl;
			continue;
		}
		cout << "**                                                 **"<<endl;	
	}
	cout << "*****************************************************" << endl;
	do{
		int y;
		cout << "输入年份:";
		cin >> y;
		d.SetYear(y);																	//**设置Date对象的年份
		
		cout << setw(25) << d.GetYear() << "年" << endl;								//打印Date对象中年份的属性
		cout << setw(24) << TwelveSymbolicAnimals[d.GetYear() % 12] << "年" << endl;	//打印十二生肖
		cout << "-------------------------------------------------" << endl;

		int n = 0;																		//定义二十四节气计数器
		for (int i = 0; i < 12; i++) {
			cout << setw(24) << Month[i] << "月" << endl;								//打印月份
			for (int j = 0; j < 7; j++) {
				cout << "星期" << week[j]<<setw(4);											//打印星期
			}
			cout << endl;
			
			d.SetMonth(i + 1);															//**设置Date对象的月份
			
			int solarTerms[24];
			d.T24ST(d,solarTerms,24);
			
			//for (int i = 0; i < 24; i++)
			//	cout << solarTerms[i]<<"  ";
			//cout << d;
			
			for (int k = 1; k <= d.GetMonthDays(d); k++) {								//从第二天开始循环，通过GetMonthDays()来获取当前月份的天数

				d.SetDay(k);
				//cout << d.Week(d);
				if (k == 1) {
					cout << setw((6 * d.Week(d)) + 6)  << k;							//第一天所在的星期数，通过Week()函数获取当前月份第一天为星期几，通过setw()来定位
					if ((d.Week(d) + 1) % 7 == 0) {										//若此天的星期数对7取余为0则换行
						cout << endl;
						cout << endl;
					}
					continue;
					//cout << setw(6 * (d.Week(d) + 1)) << d.Week(d);
				}

				cout << setw(6) << k;													//打印除了第一天的每一天
				if ((d.Week(d)+1) % 7 == 0) {											//若此天的星期数对7取余为0则换行
					cout << endl;
						for (int m = k; m >= k - 6; m--) {								//判断此周是否有天数与二十四节气吻合
							for (int y = n; y < n + 2; y++) {
								if (m == solarTerms[y]) {
									d.SetDay(m);
									cout << setw((6 * d.Week(d)) + 8)<< The24SolarTerms[y];
								}
							}
						}
					cout << endl;

				}
			}
			
			cout << endl;
			cout << "-------------------------------------------------" << endl;
			cout << "-------------------------------------------------" << endl;
			n += 2;																		//通过计数器n来计算二十四节气
		}
																		
		cout << "是否继续输入?" << endl;												//setw(7)=六个空格=星期X的字符长度
	} while (UserSaysYes());															//调用utility的UserSaysYes()函数判断是否继续
}
