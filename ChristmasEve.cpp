// ChristmasEve.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<ctime>

#define DAYS_30 {4,6,9,11}

#define FEB 2

// months with 30 days
#define APRIL 4
#define JUNE 6
#define SEP 9
#define NOV 11


using namespace std;

// Gets the distance between any two days
int time_delta(tm day1, tm day2);

// gets christmas for current year
tm christmas_this_year();

int main(){

	time_t now = time(0);
	tm * ltm = new tm();
	localtime_s(ltm, &now);
	int diff = time_delta(*ltm, christmas_this_year());
	cout << "It's Christmas ";
	if (diff < 0) {
		diff = diff + 365;
		diff = ((ltm->tm_year + 1901) % 400 == 0) || ((ltm->tm_year + 1901) % 4 == 0 && (ltm->tm_year + 1901) % 100 != 0) ? 1 : 0;
	}
	if (diff == 0) {
		cout << "day!";
	}
	else{
		for (int i = 0; i < diff; i++)
		{
			cout << "eve ";
		}
	}
	cout << endl;
	getchar();
    return 0;
}

tm christmas_this_year() {
	tm result;
	tm * current_year = new tm();
	time_t now = time(0);
	localtime_s(current_year, &(now));
	current_year->tm_mday = 25;
	current_year->tm_mon = 11;

	return *current_year;
}

int time_delta(tm day1, tm day2){
	tm start, end;
	int mul = 1;
	// gets earliest day as the start day
	if (day1.tm_year > day2.tm_year) {
		end = day1;
		start = day2;
		mul = -1;
	}
	else if(day1.tm_year < day2.tm_year){
		end = day2;
		start = day1;
	}
	else {
		if (day1.tm_mon > day2.tm_mon) {
			end = day1;
			start = day2;
			mul = -1;
		}
		else if (day1.tm_mon < day2.tm_mon){
			end = day2;
			start = day1;
		}
		else {
			if (day1.tm_mday > day2.tm_mday){
				end = day1;
				start = day2;
				mul = -1;
			}
			else{
				end = day2;
				start = day1;
			}
		}
	}
	int result = 0;
	bool leap_year = ((start.tm_year + 1900) % 400 == 0) || ((start.tm_year + 1900) % 4 == 0 && (start.tm_year + 1900) %100 != 0);
	// counts number of days from start day to end day 
	while (start.tm_mday != end.tm_mday || start.tm_mon != end.tm_mon || start.tm_year != end.tm_year)
	{
		result++;
		start.tm_mday++;
		if (start.tm_mday == 29 && !leap_year && start.tm_mon == FEB){
			start.tm_mday = 1;
			start.tm_mon++;
		}
		else if (start.tm_mday == 30 && leap_year && start.tm_mon == FEB){
			start.tm_mday = 1;
			start.tm_mon++;
		}
		else if ((start.tm_mon == APRIL || start.tm_mon == JUNE || start.tm_mon == SEP || start.tm_mon == NOV) && start.tm_mday == 30){
			start.tm_mday = 1;
			start.tm_mon++;
		}
		else if (start.tm_mday == 31) {
			start.tm_mday = 1;
			start.tm_year += start.tm_mon / 12;
			leap_year = ((start.tm_year + 1900) % 400 == 0) || ((start.tm_year + 1900) % 4 == 0 && (start.tm_year + 1900) % 100 != 0);
			start.tm_mon = (start.tm_mon + 1) % 12;
		}
	}

	return result * mul;

}
