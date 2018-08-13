#ifndef HELPER_H
#define HELPER_H

#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

namespace Helper
{
	template <class T>

	std::string ToString(const T &);

	struct DateTime
	{
		int day, month, year, hour, minute, second;

		DateTime()
		{
			time_t sec;
			time(&sec);

			struct tm *info = localtime(&sec);

			day = info->tm_mday;
			month = info->tm_mon + 1;
			year = 1900 + info->tm_year;
			minute = info->tm_min;
			hour = info->tm_hour;
			second = info->tm_sec;
		}

		DateTime(int day, int month, int year, int hour, int minute, int second) :
			day(day), month(month), year(year), hour(hour), 
			minute(minute), second(second) {}

		DateTime(int day, int month, int year) : 
			day(day), month(month), year(year), hour(0), minute(0), second(0) {}

		DateTime Now() const
		{
			return DateTime();
		}

		std::string getDateString() const
		{
			return std::string(day < 10 ? "0" : "") + ToString(day) +
				   std::string(month < 10 ? ".0" : ".") + ToString(month) + "." +
				   ToString(year);
		}

		std::string getTimeString(const std::string &sep = ":") const
		{
			return std::string(hour < 10 ? "0" : "") + ToString(hour) + sep +
				   std::string(minute < 10 ? "0" : "") + ToString(minute) + sep +
				   std::string(second < 10 ? sep : "") + ToString(second);
		}

		std::string getDateTimeString(const std::string &sep = ":") const
		{
			return getDateString() + " " + getTimeString(sep);
		}
	};

	template <class T>

	std::string ToString(const T &eStr)
	{
		std::ostringstream outStr;
		outStr << eStr;

		return outStr.str();
	}

	void writeLogFile(const std::string &logStr)
	{
		std::ofstream outFile("LogFile.txt", std::ios::app);
		outFile << "[" << Helper::DateTime().getDateTimeString() << "]" <<
			"\n" << logStr << std::endl << "\n";

		outFile.close();
	}
}

#endif // HELPER_H
