
#ifndef _ _ UTILITY_H_ _
#define _ _ UTILITY_H_ _

#ifdef _MSC_VER
#if _MSE_VER==1200

#include<string.h>
#include<iostream.h>
#include<limits.h>
#include<math.h>
#include<fstream.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip.h>
#include<stdarg.h>
#include<assert.h>

#else

//ANSI C++标准库头文件
#include<string>
#include<iostream>
#include<limits>
#include<cmath>
#include<fstream>
#include<cctype>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<cstdarg>
#include<cassert>
using namespace std;

#endif

#else

//ANSI C++标准库头文件
#include<string>
#include<iostream>
#include<limits>
#include<cmath>
#include<fstream>
#include<cctype>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<cstdarg>
#include<cassert>
using namespace std;

#endif

char GetChar(istream &inStream);
bool UserSaysYes();

template<class ElemType>
void Swap(ElemType &el, ElemType &e2);

template<class ElemType>
void Display(ElemType elem[], int n);

class Timer;
class Error;
class Rand;

char GetChar(istream &in=cin){
	char ch;

	while((ch=in.peek())!=EOF
		&&((ch=in.get())==' '
		||ch=='\t'));
	return ch;
}


bool UserSaysYes() {
	char ch;
	bool initialResponse = true;
	
	do {
		if (initialResponse)cout << "(y,n)?";
		else cout << "用y或n回答:";
		while ((ch = GetChar()) == '\n');
		initialResponse = false;
	} while (ch != 'y'&&ch != 'Y'&&ch != 'n'&&ch != 'N');
	while(GetChar() != '\n');

	if (ch == 'Y' || ch == 'y') return true;
	else return false;
}

template<class ElemType>
void Swap(ElemType &e1, ElemType &e2) {
	ElemType temp;
	temp = e1; e1 = e2; e2 = temp;
}

template<class ElemType>
void Show(ElemType elem[], int n) {
	for (int i = 0; i < n; i++)
		cout << elem[i] << "    ";
	cout << endl;
}

class Timer {
private:
	clock_t startTime;

public:
	Timer() { startTime = clock(); }
	double ElapsedTime() const {
		clock_t endTime = clock();
		return (double)(endTime - startTime) / (double)CLK_TCK;
	}
	void Reset() { startTime = clock(); }
};

#define MAX_ERROR_MESSAGE_LEN 100
class Error {
private:
	char message[MAX_ERROR_MESSAGE_LEN];

public:
	Error(char mes[] = "一般性异常!") { strcpy_s(message, mes); }
	void Show() const { cout << message << endl; }
};

class Rand {
public:
	static void SetRandSeed() { srand((unsigned)time(NULL)); }
	static int GetRand(int n) { return rand() % n; }
	static int GetRand() { return rand(); }
};

#endif
