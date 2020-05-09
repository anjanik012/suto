//
// Created by Anjani Kumar <anjanik012@gmail.com> on 5/9/20.
//

#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <shadow.h>

#include <iostream>
#include <boost/asio/io_service.hpp>

#include "fast_connection.h"

using boost::asio::io_service;

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
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
    } else {
        retval = PAM_AUTH_ERR;
    }
    return retval;
}
