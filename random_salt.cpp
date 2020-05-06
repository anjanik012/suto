//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/5/20.
//

#include "random_salt.h"

const char random_salt::symbols[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./";

std::string random_salt::get_salt(const uint8_t size) {
    std::string pass;
    pass.resize(size);
    for (char &pas : pass) {
        pas = symbols[dist(rng)];
    }
    return pass;
}
