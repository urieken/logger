#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <cstdio>
#include <memory>
#include <string>
#include <cstdarg>
#include <sstream>
#include <iostream>

/*! \brief Class for logging events at runtime
*
* A singleton class that is used to display/log events at runtime.
*/
class Logger {
	//! Class instance.
	static Logger m_Instance;
	//! Log entry counter
	unsigned int m_line;

	//! Default CTOR
	Logger();
	//! Deleted copy constructor
	Logger(const Logger& _other) = delete;
	//! Deleted assignment operator
	Logger& operator=(const Logger& _other) = delete;
	/*! \Brief Convert integer number into octal, hex, etc.
	*
	* \param number The number to be converted
	* \param base The base for the number to be converted into
	*/
	char* Convert(unsigned int number, int base);
public:
	/*! \brief Log level enumeration.
	*
	* To indicate the log entry's level
	* \sa Logger::getLogLevelString
	* \sa Logger::Log
	*/
	enum class LOG_LEVEL {
		//! For information logs
		_INFO = 0,
		//! For warning logs
		_WARNING,
		//! For error logs
		_ERROR,
		//! For fatal/crash logs
		_FATAL
	};
	//! DTOR
	inline virtual ~Logger() {}
	/*! \brief Method to get the instance of the class
	*
	* \return Returns a reference for the instance of the class
	*/
	static Logger& Instance();
	//! Initialze/Set the data members' default values.
	void Initialize();
	/*! \brief Returns the current time string
	*
	* \return Returns a properly formatted date for year, month, day, hour, minute, secods
	*/
	std::string getTimeString();
	/*! \brief Returns the log level string.
	*
	* \param _logLevel The log level value.
	* \return Returns the string representing the log level.
	* \sa Logger::LOG_LEVEL
	*/
	std::string getLogLevelString(const Logger::LOG_LEVEL& _logLevel);
	/*! \brief Prints the log entry.
	*
	* \param _entry The information to entered into the log.
	* \param _logLevel The log level value.
	* \sa Logger::LOG_LEVEL
	*/
	void Log(const std::string& _entry, const Logger::LOG_LEVEL& _logLevel);

	/*! \brief Prints the log entry.
	*
	* \param _entry The information to entered into the log.
	* \param _logLevel The log level value.
	* \sa Logger::LOG_LEVEL
	*/
	void LogFormat(const Logger::LOG_LEVEL& _logLevel, const char* format, ...);
};

/*! \brief Log Helper for scope
*
* Logs the entry and exit points in the program.
*/
class ScopeLogger {
    //! The scope indicator
    static std::string ScopeIndicator;
	//! The entry to label the entry and exit points.
	std::string m_entry;
	//! Scope indicator
	static unsigned int  DepthIndicator;
public:
	/*! \brief The default constructor
	*
	* \param _entry The label for the entry and exit points.
	*/
	ScopeLogger(const std::string& _entry);
	//! Deleted copy constructor
	ScopeLogger(const ScopeLogger& _other) = delete;
	//! Class destructor
	virtual ~ScopeLogger();
	//! Deleted assignment operator
	ScopeLogger& operator =  (const ScopeLogger& _other) = delete;
    //! Gets the current depth of the call stack
    static unsigned int Depth();
    //! Gets the scope indicator
    static std::string& Scope();
};

//template<typename T>
//constexpr auto LOG_INFO(T a) { return Logger::Instance().Log(a, Logger::LOG_LEVEL::_INFO); }
//
//template<typename T>
//constexpr auto LOG_WARNING(T a) { return Logger::Instance().Log(a, Logger::LOG_LEVEL::_WARNING); }
//
//template<typename T>
//constexpr auto LOG_ERROR(T a) { return Logger::Instance().Log(a, Logger::LOG_LEVEL::_ERROR); }
//
//template<typename T>
//constexpr auto LOG_FATAL(T a) { return Logger::Instance().Log(a, Logger::LOG_LEVEL::_FATAL); }
//
//template<typename T>
//constexpr auto __FATAL(T a) {return Logger::Instance().Log(a, Logger::LOG_LEVEL::_FATAL); }

template<typename T1, typename T2>
constexpr auto LOG(T1 a, T2 b) { return Logger::Instance().Log(a, b); }

#if _DEBUG // Or Non distibution build
#define LOG_SCOPE(a)    ScopeLogger scopeLogger(a)
//#define LOG_INFO(a)     LOG(a, Logger::LOG_LEVEL::_INFO)
//#define LOG_WARNING(a)  LOG(a, Logger::LOG_LEVEL::_WARNING)
//#define LOG_ERROR(a)    LOG(a, Logger::LOG_LEVEL::_ERROR)
//#define LOG_FATAL(a)    LOG(a, Logger::LOG_LEVEL::_FATAL)

#define LOG_INFO(a, ...) Logger::Instance().LogFormat(Logger::LOG_LEVEL::_INFO, a, ##__VA_ARGS__)
#define LOG_WARNING(a, ...) Logger::Instance().LogFormat(Logger::LOG_LEVEL::_WARNING, a, ##__VA_ARGS__)
#define LOG_ERROR(a, ...) Logger::Instance().LogFormat(Logger::LOG_LEVEL::_ERROR, a, ##__VA_ARGS__)
#define LOG_FATAL(a, ...) Logger::Instance().LogFormat(Logger::LOG_LEVEL::_FATAL, a, ##__VA_ARGS__)

#else
#define LOG_SCOPE(a)    (void)(a)
#define LOG_INFO(a)     (void)(a)
#define LOG_WARNING(a)  (void)(a)
#define LOG_ERROR(a)    (void)(a)
#define LOG_FATAL(a)    (void)(a)
#define LOG_TEST(a,b)   (void)(a,b)
#endif

#endif // __LOGGER_H__
