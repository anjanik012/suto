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
#include <boost/asio/io_context.hpp>

#include "fast_connection.h"
#include "logger.h"
#include "suto_version.h"

using boost::asio::io_context;

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    logger_init();
    int retval;
    const char *p_username;
    retval = pam_get_user(pamh, &p_username, "Username: ");
    if (retval != PAM_SUCCESS) {
        return retval;
    }
    struct spwd *pam_user = getspnam(p_username);
    std::cout << "SUTO Version: "
        << suto_VERSION_MAJOR << "."
        << suto_VERSION_MINOR << "."
        << suto_VERSION_REVISION << '\n';
    std::cout << "User: " << p_username << '\n';
    io_context context;
    fast_connection m_connection(context, pam_user);
    m_connection.start();
    if (m_connection.get_auth_status()) {
        retval = PAM_SUCCESS;
        std::cout<<"Authorization Successful\n";
    } else {
        retval = PAM_AUTH_ERR;
        std::cout<<"Authorization Failed\n";
    }
    return retval;
}
