//
// ICRAR - International Centre for Radio Astronomy Research
// (c) UWA - The University of Western Australia, 2017
// Copyright by UWA (in the framework of the ICRAR)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

/**
 * @file
 *
 * Various utilities for shark
 */

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstring>
#include <functional>
#include <locale>
#include <string>
#include <sstream>

// gethostname
#ifdef _WIN32
# include <winsock.h>
#else
# include <unistd.h>
#endif // _WIN32

#include "utils.h"

namespace shark {

std::vector<std::string> tokenize(const std::string &s, const std::string &delims)
{
	auto lastPos = s.find_first_not_of(delims, 0);
	auto pos     = s.find_first_of(delims, lastPos);

	std::vector<std::string> tokens;
	while (std::string::npos != pos || std::string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delims, pos);
		pos = s.find_first_of(delims, lastPos);
	}
	return tokens;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}

// trim from both ends
void trim(std::string &s) {
	ltrim(rtrim(s));
}

void lower(std::string &s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

std::string lower(const std::string &s)
{
	std::string low(s);
	lower(low);
	return low;
}

void upper(std::string &s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
}

std::ifstream open_file(const std::string &name)
{
	std::ifstream f(name);
	if( !f ) {
		std::ostringstream os;
		os << "Error when opening file '" << name << "': " << strerror(errno);
		throw std::runtime_error(os.str());
	}
	return f;
}

bool empty_or_comment(const std::string &s) {
	return s.empty() || s[0] == '#';
}

std::string gethostname()
{
	/* is wrong to fix this to 100, but who cares (for now...) */
	char the_hostname[100];
	::gethostname(the_hostname, 100);
	return std::string(the_hostname);
}


}  // namespace shark
