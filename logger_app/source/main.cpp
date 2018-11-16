#include <logger.h>

void foo1();
void foo2();
void foo3();
void foo4();
void foo5();
void foo6();

int main(int argc, char** argv) {
    int nReturn{ 0 };
    Logger::Instance().Initialize();
    LOG_SCOPE(__FUNCTION__);
    
    LOG_INFO("ARGUMENT COUNT : %d", argc);
    LOG_WARNING("PROGRAM        : %s", argv[0]);

    foo1();
    foo2();
    foo3();

	Logger::Instance().LogFormat(Logger::LOG_LEVEL::_INFO,
		"First argument : %d2 Second argument : %c Third argument : %f Fourth argument : %f",
		3, 'a', 1.999, 42.5);

	LOG_INFO("First argument : %d2 Second argument : %c Third argument : %f Fourth argument : %f",
		3, 'a', 1.999, 42.5);
	LOG_WARNING("First argument : %d2 Second argument : %c Third argument : %f Fourth argument : %f",
		3, 'a', 1.999, 42.5);
	LOG_ERROR("First argument : %d2 Second argument : %c Third argument : %f Fourth argument : %f",
		3, 'a', 1.999, 42.5);
	LOG_FATAL("First argument : %d2 Second argument : %c Third argument : %f Fourth argument : %f",
		3, 'a', 1.999, 42.5);

	Logger::Instance().LogFormat(Logger::LOG_LEVEL::_WARNING,
		"Decimal : %d, Octal : %o, Hexadecimal : %x", 14, 14, 14);

	Logger::Instance().LogFormat(Logger::LOG_LEVEL::_ERROR,
		"String : %s", "XXXXXXXXX");

	Logger::Instance().LogFormat(Logger::LOG_LEVEL::_FATAL,
		"String : %s", "SOME SORT OF ERROR");

	std::cin.get();

    return nReturn;
}


void foo1(){
    LOG_SCOPE(__FUNCTION__);
    LOG<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::_INFO);
    LOG<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::_WARNING);
    LOG<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::_ERROR);
    LOG<std::string, Logger::LOG_LEVEL>(__FUNCTION__, Logger::LOG_LEVEL::_FATAL);
}

void foo2(){
    LOG_SCOPE(__FUNCTION__);
    LOG(__FUNCTION__, Logger::LOG_LEVEL::_INFO);
    LOG(__FUNCTION__, Logger::LOG_LEVEL::_WARNING);
    LOG(__FUNCTION__, Logger::LOG_LEVEL::_ERROR);
    LOG(__FUNCTION__, Logger::LOG_LEVEL::_FATAL);
}

void foo3(){
    LOG_SCOPE(__FUNCTION__);
    foo4();
}

void foo4(){
    LOG_SCOPE(__FUNCTION__);
    foo5();
}

void foo5(){
    LOG_SCOPE(__FUNCTION__);
    foo6();
}

void foo6(){
    LOG_SCOPE(__FUNCTION__);
    foo1();
    foo2();
}
