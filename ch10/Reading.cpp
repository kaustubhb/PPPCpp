#include "std_lib_facilities.h"
#include <map>

// Input file format:
// {year 1990}			
// {year 1991 {month jun }}		[upto 12 entries, no duplicates for months. No actual readings here]
// {year 1992 {month jan (1 0 61.5)} {month feb (1 1 64) (2 2 65.2)}}	
// 									[(day, hour, temp), upto 24 readings per day]
// {year 2000
//           { month feb (1 1 68 ) (2 3 66.66 ) ( 1 0 67.2)}
//           {month dec (15 15 –9.2 ) (15 14 –8.8) (14 0 –2) }
// }

namespace {
	string toLower(const string &str) {
		string result;
		for(size_t i=0;i<str.length();++i) {
			if(str[i] >= 'A' && str[i] <= 'Z')
				result += str[i] + 'a' - 'A';
			else
				result += str[i];
		}
		return result;
	}

	std::map<string, int> mtoi;
	void initialize_mtoi() {
		mtoi["jan"] = 0;
		mtoi["feb"] = 1;
		mtoi["mar"] = 2;
		mtoi["apr"] = 3;
		mtoi["may"] = 4;
		mtoi["jun"] = 5;
		mtoi["jul"] = 6;
		mtoi["aug"] = 7;
		mtoi["sep"] = 8;
		mtoi["oct"] = 9;
		mtoi["nov"] = 10;
		mtoi["dec"] = 11;
	}

	int monthToInt(const string &str) {
		string s = toLower(str);
		return mtoi[s];	
	}

	constexpr int not_a_reading = -7777; // less than absolute zero
	constexpr int not_a_month = -1;
}


struct Day {
	vector<double> hours{vector<double>(24, not_a_reading)};	
};

struct Month {
	int month {not_a_month};
	vector<Day> days{32};	// we are wasting one day here. 
							// To keep things simple, days[1] => 1st day of month
};

struct Year {
	int year;	
	vector<Month> months{12};
};

struct Reading {
	int day;
	int hour;
	double temperature;
};

// input format - (2 3 66.66)
istream& operator>>(istream& is, Reading &r) 
{
	char c1;

	// if we find format is wrong even when we start, we set failbit and 
	// return to calling function which can try something else
	if(is >> c1 && c1 != '(') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	char c2;
	int d, h;
	double t;
	is >> d >> h >> t >> c2;

	// since we have already started reading, and now we find wrong format or stream error,
	// we'll return the error.
	if(!is || c2 != ')')
		error("Reading: Bad input");
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}



istream& operator>>(istream &is, Month &m) {
	char c1;
	if(is >> c1 && c1 != '{') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	string monthMarker, strMon;
	if(is >> monthMarker >> strMon && monthMarker == "month") {
		m.month = monthToInt(strMon);
	}
	else {
		error("Month: Bad input");
	}

	Reading rd;
	while(is >> rd) {
		m.days[rd.day].hours[rd.hour] = rd.temperature;
	}
	if(!is.eof()) {
		is.clear();
		char c2;
		is >> c2;
		if(c2 != '}')
			error("Month: Bad input");
	}
	else {
		error("Month: Bad input");
	}
	return is;
}

istream& operator>>(istream &is, Year &y) {
	char c1;
	if(is >> c1 && c1 != '{') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	string yearMarker;
	int year;
	if(!(is >> yearMarker >> year && yearMarker == "year")) {
		error("Year: Bad input");
	}

	y.year = year;

	while(true) {
		Month m;
		is >> m;
		if(!is)
			break;
		if(m.month >=0 && m.month < 12) {
			y.months[m.month] = m;
		}
		else {
			cerr << "Invalid month value";
		}
	}

	if(!is.eof()) {
		is.clear();
		char c2;
		is >> c2;
		if(c2 != '}')
			error("Year: Bad input");
	}
	else {
		error("Year: Bad input");
	}

	return is;
}



//------------------------ TESTS ---------------------------------------------
ostream& operator<<(ostream& os, const Reading &r) {
	return os << "(" << r.day << ", " << r.hour << ", " << r.temperature << ")";
}

ostream& operator<<(ostream &os, const Month &m) {
	//return os << "Read month " << m.month;
	os << "Month: " << m.month << " => ";
	for(size_t id = 1; id < m.days.size(); ++id) {
		Day d = m.days[id];
		for(size_t ih=0; ih < d.hours.size(); ++ih) {
			if(d.hours[ih] != not_a_reading) {
				os << "(" << id << " " << ih << " " << d.hours[ih] << ") ";
			}
		}
	}
	return os;
}

ostream& operator<<(ostream &os, const Year &yr) {
	os << "Year: " << yr.year << endl;
	for(size_t im = 0; im < yr.months.size(); ++im) {
		if(yr.months[im].month != not_a_month) {
			os << yr.months[im] << endl;
		}
	}
	return os;
}

void testInputReading() {
	Reading r1, r2;
	string str = "(2 4 68) \n  (1 3 51)";
	stringstream ss(str);
	ss >> r1 >> r2;
	cout << r1 << endl << r2 << endl;
}

void testInputMonth() {
	Month m1;
	string str = "{ month jan (2 4 68) (1 3 51) }";
	//string str = "{year 2000 "
	// 		           "{ month feb (1 1 68 ) (2 3 66.66 ) ( 1 0 67.2)} "
		//string str = "{ month jan }";
	stringstream ss(str);
	ss >> m1;
	cout << m1 << endl;
}

void testInputYear() {
	Year y1;
	string str = "{year 2000 "
			           "{ month feb (1 1 68 ) (2 3 66.66 ) ( 1 0 67.2)}	 "
			           "{month dec (15 15 -9.2 ) (15 14 -8.8) (14 0 -2) }}";
	//string str = "{year 2000 {month jan (1 1 68)} "" {month dec (15 15 -9.2 )}}";
	stringstream ss(str);
	ss >> y1;
	cout << y1 << endl;
}


//------------------------------------------------------------------------


int main()
{
	initialize_mtoi();
	//testInputReading();
	//testInputMonth();
	testInputYear();
}