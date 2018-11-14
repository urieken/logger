#include <logger.h>

int main(int argc, char** argv) {
	int nReturn{ 0 };
	{
		LOG_SCOPE(__FUNCTION__);
		LOG_INFO(std::string("ARGUMENT COUNT : ") + std::to_string(argc));
		LOG_WARNING(std::string("PROGRAM        : ") + argv[0]);

		LOG_TEST<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::INFO);
		LOG_TEST<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::WARNING);
		LOG_TEST<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::ERROR);
		LOG_TEST<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::FATAL);
		LOG_TEST(__FUNCTION__, Logger::LOG_LEVEL::INFO);
		LOG_TEST(__FUNCTION__, Logger::LOG_LEVEL::WARNING);
		LOG_TEST(__FUNCTION__, Logger::LOG_LEVEL::ERROR);
		LOG_TEST(__FUNCTION__, Logger::LOG_LEVEL::FATAL);

		__FATAL(__FUNCTION__); 
	}
	std::cin.get();

	return nReturn;
}
 