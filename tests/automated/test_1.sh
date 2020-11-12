#!/bin/bash
sudo useradd -m -g users -G wheel,storage,power -s /bin/bash test_user
echo "test_user:test_pass"|sudo chpasswd
test_1_remote.py &
su -c ls test_user
exit $?