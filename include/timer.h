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
 * Simple timer class
 */

#ifndef SHARK_TIMER_H_
#define SHARK_TIMER_H_

#include <ostream>
#include <chrono>

#include "utils.h"

namespace shark {

/**
 * A simple timer class that starts measuring time when created and returns
 * the elapsed time when requested.
 */
class Timer {

public:

	using clock = std::chrono::high_resolution_clock;
	using duration = typename std::chrono::nanoseconds::rep;

	/**
	 * Returns the number of milliseconds elapsed since the creation
	 * of the timer
	 *
	 * @return The time elapsed since the creation of the timer, in [ms]
	 */
	inline
	duration get() const {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - t0).count();
	}

private:
	clock::time_point t0 {clock::now()};

};

template <typename T>
inline
std::basic_ostream<T> &operator<<(std::basic_ostream<T> &os, const Timer &t) {
	os << ns_time(t.get());
	return os;
}

}  // namespace shark

#endif // SHARK_TIMER_H_