#include "IDGenerator.h"

#include <iostream>

unsigned int IDGenerator::GenerateID()
{
	unsigned int id = std::rand() * std::rand() * std::rand() * std::rand();
	return id;
}
