#include <logger.h>

int main(int argc, char** argv) {
	int nReturn{ 0 };
    Logger::Instance().Initialize();
	{
		LOG_SCOPE(__FUNCTION__);
		LOG_INFO(std::string("ARGUMENT COUNT : ") + std::to_string(argc));
		LOG_WARNING(std::string("PROGRAM        : ") + argv[0]);

		LOG<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::_INFO);
		LOG<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::_WARNING);
		LOG<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::_ERROR);
		LOG<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::_FATAL);
		LOG(__FUNCTION__, Logger::LOG_LEVEL::_INFO);
		LOG(__FUNCTION__, Logger::LOG_LEVEL::_WARNING);
		LOG(__FUNCTION__, Logger::LOG_LEVEL::_ERROR);
		LOG(__FUNCTION__, Logger::LOG_LEVEL::_FATAL);
		{
			LOG_SCOPE(__FUNCTION__);
			LOG(__FUNCTION__, Logger::LOG_LEVEL::_INFO);
			LOG(__FUNCTION__, Logger::LOG_LEVEL::_WARNING);
			LOG(__FUNCTION__, Logger::LOG_LEVEL::_ERROR);
			LOG(__FUNCTION__, Logger::LOG_LEVEL::_FATAL);
		}

		LOG_FATAL(__FUNCTION__); 
	}
	std::cin.get();

	return nReturn;
}
 
