# suto - sudo touch

suto is a Linux PAM authenticator using Android phone fingerprint over local network.

This repository is hosting the desktop module to be called by Linux PAM for authentication written in C++. Networking is
done by **Boost.Asio** library.

**This is largely work in progress.**

### Work done

* **Device detection over _UDP_** - This desktop module broadcasts _UDP_ packets with _SUTO_UDP_HELLO_ message on receiver
port _2020_ and waits for reply _SUTO_UDP_HELLO_REPLY_ on sender port _2021_. Currently after successfuly receiving a 
reply packet, it ends execution. 