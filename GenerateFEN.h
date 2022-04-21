#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct GenerateFEN
{
	std::vector<std::string> mateIn_X;
	GenerateFEN();
	GenerateFEN(std::string file_name);
	std::pair<std::string, std::string> randomFEN();
};

