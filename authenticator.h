//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/6/20.
//

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
