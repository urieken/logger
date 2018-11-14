#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <memory>
#include <mutex>
#include <string>
#include <sstream>
#include <iostream>

// Move this to a proper place
#ifdef _MSC_VER
#define ASSERT(x) if (!(x)) __debugbreak()
#else
#endif // _MSC_VER


/*! \brief Class for logging events at runtime
*
* A singleton class that is used to display/log events at runtime.
*/
class Logger {
	//! Pointer to class instance.
	static std::unique_ptr<Logger> m_pIinstance;
	//! Flag to ensure that a routine is only called once.
	static std::once_flag m_onceFlag;
	//! Log entry counter
	unsigned int m_line;
	//! Default CTOR
	Logger() = default;
	//! Deleted copy constructor
	Logger(const Logger& _other) = delete;
	//! Deleted assignment operator
	Logger& operator=(const Logger& _other) = delete;
public:
	/*! \brief Log level enumeration.
	*
	* To indicate the log entry's level
	* \sa Logger::getLogLevelString
	* \sa Logger::Log
	*/
	enum class LOG_LEVEL {
		//! For information logs
		INFO = 0,
		//! For warning logs
		WARNING,
		//! For error logs
		ERROR,
		//! For fatal/crash logs
		FATAL
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
	/*! \brief Returns the log level string.
	*
	* \param _entry The information to entered into the log.
	* \param _logLevel The log level value.
	* \sa Logger::LOG_LEVEL
	*/
	void Log(const std::string& _entry, const Logger::LOG_LEVEL& _logLevel);
};

/*! \brief Log Helper for scope
*
* Logs the entry and exit points in the program.
*/
class ScopeLogger {
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
};

#if _DEBUG // Or Non distibution build
#define LOG_SCOPE(a)   ScopeLogger scopeLogger(a)

template<typename T>
constexpr auto LOG_INFO(T a) { return Logger::Instance().Log(a, Logger::LOG_LEVEL::INFO); }

template<typename T>
constexpr auto LOG_WARNING(T a) { return Logger::Instance().Log(a, Logger::LOG_LEVEL::WARNING); }

template<typename T>
constexpr auto LOG_ERROR(T a) { return Logger::Instance().Log(a, Logger::LOG_LEVEL::ERROR); }

template<typename T>
constexpr auto LOG_FATAL(T a) { return Logger::Instance().Log(a, Logger::LOG_LEVEL::FATAL); }

template<typename T>
constexpr auto __FATAL(T a) {return Logger::Instance().Log(a, Logger::LOG_LEVEL::FATAL); }

template<typename T1, typename T2>
constexpr auto LOG_TEST(T1 a, T2 b) { 
	//T1 temp = a;
	//T2 level;
	//switch (b)
	//{
	//case Logger::LOG_LEVEL::INFO: level = b; break;
	//case Logger::LOG_LEVEL::WARNING: level = b; break;
	//case Logger::LOG_LEVEL::ERROR: level = b; break;
	//case Logger::LOG_LEVEL::FATAL: level = b; break;
	//}
	//return Logger::Instance().Log(a, level); 
	return Logger::Instance().Log(a, b);
}
#else
#define LOG_SCOPE(a)    (void)(a)
#define LOG(a)          (void)(a)
#define LOG_INFO(a)     (void)(a)
#define LOG_WARNING(a)  (void)(a)
#define LOG_ERROR(a)    (void)(a)
#define LOG_FATAL(a)    (void)(a)
#define LOG_TEST(a,b)   (void)(a,b)
#endif

#endif // __LOGGER_H__
//void Logger::Log(const std::string& _entry, const Logger::LOG_LEVEL& _logLevel)