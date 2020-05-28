/*
** B, 2019
** Utils / Logger.cpp
*/

#include "B/Utils/Logger.hpp"

#include <sys/time.h>
#include <cstring>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

Logger::Level Logger::s_level = Logger::Level::Trace;
bool Logger::s_useColors = true;

////////////////////////////////////////////////////////////////////////////////

std::ostream &Logger::log(Logger::Level level)
{
	static std::ostream nullstream(nullptr);
	if (level < s_level) {
		return nullstream;
	}

	struct timeval tv;
	gettimeofday(&tv, NULL);
	int millisec = tv.tv_usec / 1000.0;

	struct tm *lt = localtime(&tv.tv_sec);
	char tbuf[16] = {0};
	int n = strftime(tbuf, sizeof(tbuf), "%H:%M:%S", lt);
	snprintf(tbuf + n, sizeof(tbuf) - n - 1, ".%03d", millisec);

	return std::cout << tbuf << " " << levelString(level) << " " << std::dec;
}

char *Logger::levelString(Logger::Level level)
{
	static struct { Logger::Level level; const char *name; const char *color; } levelColors[] = {
		{Logger::Level::Trace, "TRACE", "\x1b[90m"},
		{Logger::Level::Debug, "DEBUG", "\x1b[35m"},
		{Logger::Level::Info,  "INFO ", "\x1b[32m"},
		{Logger::Level::Warn,  "WARN ", "\x1b[33m"},
		{Logger::Level::Error, "ERROR", "\x1b[31m"},
		{Logger::Level::Fatal, "FATAL", "\x1b[31;1m"},
	};
	static char levelStr[32] = {0};

	memset(levelStr, 0, sizeof(levelStr));

	if (s_useColors)
		strcat(levelStr, levelColors[level].color);
	strcat(levelStr, levelColors[level].name);
	if (s_useColors)
		strcat(levelStr, "\x1b[0m");

	return levelStr;
}

////////////////////////////////////////////////////////////////////////////////

}