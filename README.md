# suto - sudo touch

suto is a Linux PAM authenticator which uses Android phone biometrics to verify user credentials for granting super-user
access.

This repository is hosting the desktop module to be called by Linux PAM for authentication written in C++. Networking is
done by **Boost.Asio** library.

### Dependencies

* _Boost C++ v1.42.0_

### Work done

* **Device detection over _UDP_** - This desktop module broadcasts _UDP_ packets with _SUTO_UDP_HELLO_ message on receiver
port _2020_ and listens for _TCP_ connection on sender port _2021_ asynchronously. 

* **TCP connection established with detected device**- The device upon receiving the broadcast message attempts to connect
with the desktop over _TCP_ and succeeds.

* **Authentication Protocol works** - The implementation of protocol in file `PROTOCOL.md` works. 

* **Sample test**- A test is written in python which mimics the behaviour of actual android client yet to be written.