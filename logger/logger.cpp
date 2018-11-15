#include "logger.h"

#include<ctime>
#include<chrono>
#include<iomanip>
#include<sstream>

#if defined WIN32 || defined WIN64
#include <Windows.h>
#endif

std::unique_ptr<Logger> Logger::m_pIinstance;
#if defined WIN32 || defined WIN64
std::once_flag Logger::m_onceFlag;
#endif

Logger& Logger::Instance() {
#if defined WIN32 || defined WIN64
	std::call_once(m_onceFlag, [] {
		m_pIinstance.reset(new Logger);
	});
#else
		m_pIinstance.reset(new Logger);
#endif
	return *m_pIinstance.get();
}

void Logger::Initialize() {
	m_line = 0;
}

std::string Logger::getLogLevelString(const Logger::LOG_LEVEL& _logLevel) {
	std::stringstream tempString{};
	switch (_logLevel) {
	case LOG_LEVEL::_INFO   : tempString << "INFO"    << std::setw(10) << std::setfill(' '); break;
	case LOG_LEVEL::_WARNING: tempString << "WARNING" << std::setw(10) << std::setfill(' '); break;
	case LOG_LEVEL::_ERROR  : tempString << "ERROR"   << std::setw(10) << std::setfill(' '); break;
	case LOG_LEVEL::_FATAL  : tempString << "FATAL"   << std::setw(10) << std::setfill(' '); break;
	default: tempString << "UNKNOWN" << std::setw(10) << std::setfill(' '); break;
	}
	return tempString.str();
}

std::string Logger::getTimeString() {
	typedef std::chrono::duration<int,
		std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type>days;

	std::chrono::system_clock::time_point now{ std::chrono::system_clock::now() };
	std::chrono::system_clock::duration tp{ now.time_since_epoch() };

	days d{ std::chrono::duration_cast<days>(tp) }; tp -= d;

	std::chrono::hours   h{ std::chrono::duration_cast<std::chrono::hours>(tp) };   tp -= h;
	std::chrono::minutes m{ std::chrono::duration_cast<std::chrono::minutes>(tp) };	tp -= m;
	std::chrono::seconds s{ std::chrono::duration_cast<std::chrono::seconds>(tp) }; tp -= s;
	std::chrono::milliseconds ms{ std::chrono::duration_cast<std::chrono::milliseconds>(tp) }; tp -= ms;

	time_t tt{ std::chrono::system_clock::to_time_t(now) };
	tm utc_tm;
	tm local_time;
	std::stringstream ss;
#if defined WIN32 || defined WIN64
	::gmtime_s(&utc_tm, &tt);
	::localtime_s(&local_time, &tt);
#else
	utc_tm = *::gmtime(&tt);
	local_time = *::localtime(&tt);
#endif

	ss << utc_tm.tm_year + 1900 << ':' << std::setw(2) << std::setfill('0');
	ss << utc_tm.tm_mon + 1     << ':' << std::setw(2) << std::setfill('0');
	ss << utc_tm.tm_mday        << ':' << std::setw(2) << std::setfill('0');
	ss << utc_tm.tm_hour        << ':' << std::setw(2) << std::setfill('0');
	ss << utc_tm.tm_min         << ':' << std::setw(2) << std::setfill('0');
	ss << utc_tm.tm_sec         << ':' << std::setw(3) << std::setfill('0');
	ss << ms.count();
	return ss.str();
}

void Logger::Log(const std::string& _entry, const Logger::LOG_LEVEL& _logLevel) {
	std::stringstream ss;
	ss << "[" << std::setfill('0') << std::setw(8) << ++m_line << "]["
		<< getTimeString() << "][" << getLogLevelString(_logLevel) << "]"
		<< _entry;

// Move this to a new class (LogWriter, ConsoleWriter, or FileWriter)
#if defined WIN32 || defined WIN64
	HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
	int color = 10;
	switch (_logLevel) {
	case LOG_LEVEL::_INFO:    color = 2;  break;
	case LOG_LEVEL::_WARNING: color = 6;  break;
	case LOG_LEVEL::_ERROR:   color = 4;  break;
	case LOG_LEVEL::_FATAL:   color = 12; break;
	default:                  color = 7;  break;
	}
	::SetConsoleTextAttribute(hConsole, color);
	std::cout << ss.str() << std::endl;
	::SetConsoleTextAttribute(hConsole, 7);	
#else
    std::string color{""};
	switch (_logLevel) {
	case LOG_LEVEL::_INFO:    color = "\033[32m]";  break;
	case LOG_LEVEL::_WARNING: color = "\033[33m]";  break;
	case LOG_LEVEL::_ERROR:   color = "\033[31m]";  break;
	case LOG_LEVEL::_FATAL:   color = "\033[1;31m]"; break;
	default:                  color = "\033[37m]";  break;
	}
	std::cout << color.c_str() << ss.str() << "\033[0m" << std::endl;
#endif
}

unsigned int ScopeLogger::DepthIndicator = 0;

ScopeLogger::ScopeLogger(const std::string& _entry) : m_entry{ _entry } {
	std::string scopeIndicator{ "[]" }; 
	scopeIndicator.insert(1, ++DepthIndicator, '>');
	LOG_INFO(scopeIndicator + m_entry);
}

ScopeLogger::~ScopeLogger() {
	std::string scopeIndicator{ "[]" }; 
	scopeIndicator.insert(1, DepthIndicator--, '<');
	LOG_INFO(scopeIndicator + m_entry);
}
