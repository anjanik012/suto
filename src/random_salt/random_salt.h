/*
Copyright 2020 Anjani Kumar <anjanik012@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SUTO_RANDOM_SALT_H
#define SUTO_RANDOM_SALT_H

#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace boost::random;

class random_salt {
private:
    static const char symbols[65];
    random_device rng;
    uniform_int_distribution<uint8_t> dist;
public:
    random_salt() : dist(0, 63) {}

    std::string get_salt(uint8_t);
};


#endif //SUTO_RANDOM_SALT_H
