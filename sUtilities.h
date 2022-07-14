#pragma once
#include <sstream>
#include<iostream>
#include <string>
#include<chrono>
enum class SensorType
{
	TEMP = 0,
	HUM = 1,
	PRESS = 2
};
template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

static std::string getCurrentUTC() {
	struct tm newtime;
	std::string am_pm = "AM";
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.
	err = _localtime64_s(&newtime, &long_time);
	if (err)
	{
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}

	std::ostringstream oss;
	oss << std::put_time(&newtime, "%d-%m-%Y %H:%M:%S");

	return oss.str();
}