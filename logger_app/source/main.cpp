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
    
    LOG_INFO(std::string("ARGUMENT COUNT : ") + std::to_string(argc));
    LOG_WARNING(std::string("PROGRAM        : ") + argv[0]);

    foo1();
    foo2();
    foo3();

	//for(int i = 0; i < 10; i++)
	//	Logger::Instance().LogFormat("VALUE : %d\n", Logger::LOG_LEVEL::_INFO, i);

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
