#include "Logger.h"

#include "Time.h"
#include "Vector3.h"

#include <iostream>

void Logger::Log(const std::string & str)
{
	std::cout << str << std::endl;
}

void Logger::Log(Vector3 vec)
{
	std::cout << vec.Display() << std::endl;

}
