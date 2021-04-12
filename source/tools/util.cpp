#include "tools/util.h"

namespace util {

std::vector<std::string> split(const std::string& str, const std::string& delim) {
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(delim, prev);
		if (pos == std::string::npos) {
			pos = str.length();
		}
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) {
			tokens.push_back(token);
		}
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

bool equals(float f0, float f1) {
	return f0 >= f1 - ERROR && f0 <= f1 + ERROR;
}

}
