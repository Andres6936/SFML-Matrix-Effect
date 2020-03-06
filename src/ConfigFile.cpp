#include "ConfigFile.h"
#include <fstream>
#include <iostream>
#include <sstream>

ConfigFile::ConfigFile(const string& filepath)
{
	m_FilePath = filepath;

	Refresh();
}

void ConfigFile::Refresh()
{
	m_Map.clear();
	
	std::ifstream file(m_FilePath);
	if (!file.is_open())
	{
		m_IsValid = false;
		std::cerr << "Cannot open: " << m_FilePath;
	}
	
	std::string line;

	while (std::getline(file, line)) _parseLine(line);

	m_IsValid = true;
	
	file.close();
}

void ConfigFile::PrintEntries()
{
	std::cout << "CONFIG:\n";
	for (const auto& entry : m_Map)
	{
		std::cout << "\t" << entry.first << "=" << entry.second << "\n";
	}
}

void ConfigFile::_parseLine(string& line)
{
	auto tokens = _strsplit(line, "=");

	if (tokens.size() != 2)
	{
		std::cerr << "Invalid property: " << line << "\n";
		std::exit(-1);
	}

	if (tokens[0].empty() || tokens[1].empty())
	{
		std::cerr << "Invalid property: " << line << "\n";
		std::exit(-1);
	}

	trim(tokens[0]);
	trim(tokens[1]);

	m_Map[tokens[0]] = tokens[1];
}
