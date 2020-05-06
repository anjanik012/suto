//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/6/20.
//

#include "authenticator.h"
#include <crypt.h>
#include <iostream>

std::string authenticator::get_salt() {
    return password_salt;
}

authenticator::authenticator() : m_random_salt() {
    password_salt = "ABCDabcd./";
    random_salt_str = m_random_salt.get_salt(15);
    auto hash = crypt("shailesh", password_salt.c_str());
    password_hash = std::string(hash);
}

bool authenticator::check_hash(const std::string &received_hash) {
    auto hash_2 = crypt(password_hash.c_str(), random_salt_str.c_str());
    const std::string hash_2_str = std::string(hash_2);
    std::cout << "AUTHENTICATOR: recalculated hash:- " << hash_2_str << std::endl;
    return hash_2_str == received_hash;
}

std::string authenticator::get_random_salt() {
    return random_salt_str;
}
