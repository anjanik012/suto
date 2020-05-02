Version 1.0

### Message types

`SUTO_UDP_HELLO` - Broadcasted by desktop upon beginning of auth process.

`SUTO_C_GET_SALT` - Sent by Android client to desktop after successfull _TCP_ connection. This message requests the 
Linux passwaord salt of the user. This is one-time only. The android client should save this for later use.

`SUTO_C_GET_RSTRING` - Sent by Android client to desktop after ensuring that it has password salt. This message requests
the random string from the desktop.

`SUTO_AUTH_SUCCESS` - Sent by desktop client after successfull authentication.

`SUTO_AUTH_FAILED` - Sent by desktop client after failure of authentication.