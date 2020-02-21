#pragma once
#include <string>
#include <unordered_map>
#include <regex>
#include <iostream>

#include <SFML/Graphics/Color.hpp>

using std::string;
using std::unordered_map;

class ConfigFile
{
public:
	ConfigFile(const string& filepath);

	// T should be string, float, double, int
	template<typename T>
	std::tuple<T, bool> GetProp(const string& name)
	{
		if (const auto& entry = m_Map.find(name); entry != m_Map.end())
		{
			try
			{
				if constexpr (std::is_same<T, string>::value)
				{
					return std::make_tuple(entry->second, true);
				}
				else if constexpr (std::is_same<T, int>::value)
				{
					return std::make_tuple(std::stoi(entry->second), true);
				}
				else if constexpr (std::is_same<T, float>::value)
				{
					return std::make_tuple(std::stof(entry->second), true);
				}
				else if constexpr (std::is_same<T, double>::value)
				{
					return std::make_tuple(std::stod(entry->second), true);
				}
				else if constexpr (std::is_same<T, bool>::value)
				{
					return std::make_tuple(entry->second == "1" ? true : false, true);
				}
				else if constexpr (std::is_same<T, sf::Color>::value)
				{
					auto tokens = _strsplit(entry->second, ",");

					if (tokens.size() != 3)
					{
						std::cerr << "Invalid property: " << entry->second << "\n";
						std::exit(-1);
					}

					trim(tokens[0]);
					trim(tokens[1]);
					trim(tokens[2]);

					return std::make_tuple(sf::Color(
						std::stoi(tokens[0]),
						std::stoi(tokens[1]),
						std::stoi(tokens[2])
					), true);
				}
			}
			catch (...)
			{
				std::cerr << "Invalid property: " << entry->first << "-" << entry->second << "\n";
				std::exit(-1);
			}
		}

		std::cerr << "Can't find config option: " << name << "\n";
		
		return std::make_tuple(T(), false);
	}

	template<typename T>
	auto GetIfProp(const string& name, T def)
	{
		auto prop = GetProp<T>(name);

		return std::get<1>(prop) ? std::get<0>(prop) : def;
	}
	
	void Refresh();

	void PrintEntries();

	bool isValid() { return m_IsValid; };
private:
	std::string m_FilePath;
	bool m_IsValid { false };
	unordered_map<string, string> m_Map;
	void _parseLine(string& line);

	static std::vector<std::string> _strsplit(const string& input, const string& regex) {
		std::regex re(regex);
		std::sregex_token_iterator
			first{ input.begin(), input.end(), re, -1 },
			last;
		return { first, last };
	}
	
	static void ltrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
			}));
	}

	static void rtrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	static void trim(std::string& s) {
		ltrim(s);
		rtrim(s);
	}
	
};