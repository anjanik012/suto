//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/6/20.
//

#include "authenticator.h"

authenticator::authenticator() : m_random_salt() {
    password_salt = "$6$covunfW1Qv6z7AfS";
    random_salt_str = "$6$" + m_random_salt.get_salt(16);
    auto hash = crypt("shailesh", password_salt.c_str());
    password_hash = std::string(hash);
}

bool authenticator::check_hash(const std::string &received_hash) {
    auto hash_2 = crypt(password_hash.c_str(), random_salt_str.c_str());
    auto hash_2_str = std::string(hash_2);
    std::cout << "AUTHENTICATOR: recalculated hash:- " << hash_2_str << std::endl;
    return hash_2_str == received_hash;
}

std::string authenticator::get_salt() {
    return password_salt;
}

std::string authenticator::get_random_salt() {
    return random_salt_str;
}
