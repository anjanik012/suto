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

#include "authenticator.h"
#include "logger.h"
#include <boost/algorithm/string/find.hpp>

authenticator::authenticator(void *user) : m_random_salt() {
    m_user = (struct spwd *)user;
    password_hash = std::string(m_user->sp_pwdp);
    auto r = boost::find_nth(password_hash, "$", 2);
    password_salt = std::string(password_hash.begin(), r.begin());
    random_salt_str = "$6$" + m_random_salt.get_salt(16);
}

bool authenticator::check_hash(const std::string &received_hash) {
    auto hash_2 = crypt(password_hash.c_str(), random_salt_str.c_str());
    auto hash_2_str = std::string(hash_2);
    BOOST_LOG_TRIVIAL(trace) << "AUTHENTICATOR: recalculated hash:- " << hash_2_str;
    return hash_2_str == received_hash;
}

std::string authenticator::get_salt() {
    return password_salt;
}

std::string authenticator::get_random_salt() {
    return random_salt_str;
}
