#include "std_lib_facilities.h"

// struct Reading {
// 	int day;
// 	int hour;

// };

const int not_a_reading = -7777; // less than absolute zero
const int not_a_month = -1;

class Day {
	vector<double> hours{vector<double>(24, not_a_reading)};
	//vector<double> hours(24,-1);
};

int main()
{
	vector<double> hours(24,-1);
}