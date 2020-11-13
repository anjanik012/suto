#!/bin/bash
# python3 tests/automated/test_1_remote.py &
sudo sed -i "1iauth sufficient libpam_suto.so" /etc/pam.d/su
sudo useradd -m -g users -s /bin/bash test_user
# sudo echo "test_user:test_pass"|sudo chpasswd
echo -e "test_pass\ntest_pass" |sudo passwd test_user
python3 tests/automated/test_1_remote.py &
./su-exec test_user ls
exit $?