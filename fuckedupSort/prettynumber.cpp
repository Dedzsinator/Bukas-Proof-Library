#pragma once

//i want to make the numbers pretty by adding spacing between 3 digits
#include <string>
#include <sstream>

using namespace std;

string prettyNumber(int num) {
    std::ostringstream oss;
    oss << num;
    std::string numStr = oss.str();
    int len = numStr.length();
    if (len <= 3) {
        return numStr;
    }

    int numCommas = (len - 1) / 3;
    int firstGroupSize = len - numCommas * 3;
    std::string prettyNum;
    prettyNum.reserve(len + numCommas);
    prettyNum.append(numStr.substr(0, firstGroupSize));
    for (int i = firstGroupSize; i < len; i += 3) {
        prettyNum.push_back(',');
        prettyNum.append(numStr.substr(i, 3));
    }

    return prettyNum;
}
