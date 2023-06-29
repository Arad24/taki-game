# include "../Header Files/stringFuncs.h"

std::string toLower(const std::string& text)
{
    std::string lowerTxt = text;
    std::transform(lowerTxt.begin(), lowerTxt.end(), lowerTxt.begin(), [](unsigned char c) { return std::tolower(c); });

    return lowerTxt;
}

std::vector<unsigned char> strToVec(const std::string& text)
{
    std::vector<unsigned char> vec(text.begin(), text.end());
    return vec;
}

std::string vecToString(std::vector<unsigned char> vec)
{
    std::stringstream ss;

    // Format vector elements as string
    for (const auto& elem : vec) 
    {
        ss << elem << " ";
    }

    return ss.str();
}