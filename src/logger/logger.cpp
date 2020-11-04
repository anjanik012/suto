/*
Copyright 2020 Shailesh Aanand <anaandshailu@gmail.com>

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

#include "logger.h"

void logger_init() {
#ifdef logging
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
#else
    boost::log::core::get()->set_filter(boost::log::trivial::severity > boost::log::trivial::fatal);
#endif //logging
}

