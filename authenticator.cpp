//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/6/20.
//

#include "authenticator.h"
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
    std::cout << "AUTHENTICATOR: recalculated hash:- " << hash_2_str << std::endl;
    return hash_2_str == received_hash;
}

std::string authenticator::get_salt() {
    return password_salt;
}

std::string authenticator::get_random_salt() {
    return random_salt_str;
}
