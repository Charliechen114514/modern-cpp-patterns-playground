#include "./Task.h"
#include <chrono>
#include <format>

Task::CTime::CTime(int y, int m, int d, int h, int min, int s)
    : year(y)
    , month(m)
    , day(d)
    , hour(h)
    , minute(min)
    , second(s) { }

std::string Task::CTime::dumpTimeString() const {
	return std::format(
	    "{}-{}-{} {}:{}:{}", year, month, day, hour, minute, second);
}

Task::CTime Task::CTime::now() {
	auto now_time_point = std::chrono::system_clock::now();

	std::time_t now_c_time = std::chrono::system_clock::to_time_t(now_time_point);

	struct tm* now_tm = std::localtime(&now_c_time);

	return CTime(
	    now_tm->tm_year + 1900,
	    now_tm->tm_mon + 1,
	    now_tm->tm_mday,
	    now_tm->tm_hour,
	    now_tm->tm_min,
	    now_tm->tm_sec);
}

bool operator>(const Task::CTime& t1, const Task::CTime& t2) {
	if (t1.year > t2.year)
		return true;
	if (t1.year < t2.year)
		return false;

	if (t1.month > t2.month)
		return true;
	if (t1.month < t2.month)
		return false;

	if (t1.day > t2.day)
		return true;
	if (t1.day < t2.day)
		return false;

	if (t1.hour > t2.hour)
		return true;
	if (t1.hour < t2.hour)
		return false;

	if (t1.minute > t2.minute)
		return true;
	if (t1.minute < t2.minute)
		return false;

	if (t1.second > t2.second)
		return true;
	if (t1.second < t2.second)
		return false;

	return true;
}