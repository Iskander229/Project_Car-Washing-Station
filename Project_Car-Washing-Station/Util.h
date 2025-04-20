#pragma once
#include <vector>
#include <iostream>
#include <string>
class Util
{
public:
	//Reads a substring from buf until a comma is encountered
	static bool readUntillComma(std::string& buf, std::string& result) {
		result = "";
		for (int i = 0; i < buf.size(); i++) {
			if (buf[i] == ',') {
				result = buf.substr(0, i);
				buf = buf.substr(i + 1, buf.size() - i - 1);
				return true;
			}
		}
		return false; //if no comma found
	}


	//Adds a string to buf followed by a comma
	static void writeWithComma(std::string& buf, std::string& append) {
		buf = buf + (append + ",");
	}


	//Serializes a vector of strings into buf
	static void writeManyWithComma(std::string& buf, std::vector<std::string>& append) {
		size_t size = append.size();
		std::string sizeStr = std::to_string(size);
		writeWithComma(buf, sizeStr);
		for (int i = 0; i < size; i++) {
			writeWithComma(buf, append[i]);
		}
	}


	//Deserializes a vector of strings from buf.
	static bool readManyUntilComma(std::string& buf, std::vector<std::string>& result) {
		std::string sizeStr;
		if (!readUntillComma(buf, sizeStr)) {
			return false;
		}
		int size = std::stoi(sizeStr);
		for (int i = 0; i < size; i++) {
			std::string s;
			if (!readUntillComma(buf, s)) {
				return false;
			}
			result.push_back(s);
		}
		return true;
	}


	//Checks if substr exists in str(case-insensitive).
	static bool containsIgnoreCase(const std::string& str, const std::string& substr) {
		if (substr.size() > str.size()) {
			return false;
		}

		for (int i_1 = 0; i_1 <= str.size() - substr.size(); i_1++) {
			bool equal = true;
			for (int i_2 = 0; i_2 < substr.size(); i_2++) {
				unsigned char s1_lower = std::tolower(str[i_1 + i_2]);
				unsigned char s2_lower = std::tolower(substr[i_2]);
				if (s1_lower != s2_lower) {
					equal = false;
					break;
				}
			}
			if (equal) {
				return true;
			}
		}
		return false;
	}
};

