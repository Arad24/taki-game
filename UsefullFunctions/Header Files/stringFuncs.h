#pragma once
# include <algorithm>
# include <cctype>
# include <string>
# include <vector>
# include <sstream>


// Lower string text
std::string toLower(const std::string& text);
std::vector<unsigned char> strToVec(const std::string& text);
std::string vecToString(std::vector<unsigned char> vec);