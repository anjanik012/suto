#!/bin/bash
# python3 tests/automated/test_1_remote.py &
# sudo useradd -m -g users -s /bin/bash test_user
# sudo echo "test_user:test_pass"|sudo chpasswd
echo -e "test_pass\ntest_pass" |sudo passwd root
# sudo sed -i "1iauth sufficient libpam_suto.so" /etc/pam.d/sudo
echo "auth sufficient libpam_suto.so" > /etc/pam.d/sudo
python3 tests/automated/test_1_remote.py &
sudo ls
exit $?