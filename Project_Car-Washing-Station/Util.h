#pragma once
#include <vector>
#include <iostream>
class Util
{
public:

	static bool readUntillComma(std::string& buf, std::string& result) {
        result = "";
        for (int i = 0; i < buf.size(); i++) {
            if (buf[i] == ',') {
                result = buf.substr(0, i);
                buf = buf.substr(i + 1, buf.size() - i - 1);
                return true;
            }
        }
        return false;
	}

    static void writeWithComma(std::string& buf, std::string& append) {
        buf = buf + (append + ",");
    }
};

