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

#ifndef SUTO_AUTHENTICATOR_H
#define SUTO_AUTHENTICATOR_H

#include <string>
#include <crypt.h>
#include <iostream>
#include "random_salt.h"
#include <shadow.h>

class authenticator {
private:
    std::string password_hash;
    std::string password_salt;
    std::string random_salt_str;

    random_salt m_random_salt;

    struct spwd *m_user;
public:
    explicit authenticator(void *);

    std::string get_salt();

    std::string get_random_salt();

    bool check_hash(const std::string &);
};


#endif //SUTO_AUTHENTICATOR_H
