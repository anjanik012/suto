#!/bin/bash
sudo useradd -m -g users -G wheel,storage,power -s /bin/bash test_user
# sudo echo "test_user:test_pass"|sudo chpasswd
echo -e "linuxpassword\nlinuxpassword" | sudo passwd linuxuser
test_1_remote.py &
su -c ls test_user
exit $?