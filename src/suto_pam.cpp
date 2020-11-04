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

#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <shadow.h>

#include <iostream>
#include <boost/asio/io_service.hpp>

#include "fast_connection.h"
#include "logger.h"

using boost::asio::io_service;

void logger_init() {
#ifdef logging
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
#else
    boost::log::core::get()->set_filter(boost::log::trivial::severity > boost::log::trivial::fatal);
#endif //logging

}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    logger_init();
    int retval;
    const char *p_username;
    retval = pam_get_user(pamh, &p_username, "Username: ");
    struct spwd *pam_user = getspnam(p_username);

    if (retval != PAM_SUCCESS) {
        return retval;
    }

    io_service service;
    fast_connection m_connection(service, pam_user);
    m_connection.start();
    if (m_connection.get_auth_status()) {
        retval = PAM_SUCCESS;
        std::cout<<"Auth Success\n";
    } else {
        retval = PAM_AUTH_ERR;
        std::cout<<"Auth Failed\n";
    }
    return retval;
}
