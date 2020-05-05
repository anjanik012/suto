Version 1.1

## For establishing connection between desktop and client.

### Message types

`SUTO_UDP_HELLO` - Broadcasted by desktop upon beginning of auth process. This will indicate the client to try to connect
with _TCP_ with the dedsktop on port _2021_.

## After TCP connection is established

### Message types

`SUTO_C_GET_SALT` - Sent by Android client to desktop after successfull _TCP_ connection. This message requests the 
Linux passwaord salt of the user. This is one-time only. The android client should save this for later use.

`SUTO_SALT_%s` - Sent by desktop upon salt request. _%s_ is a placeholder which will be replaced by the salt.

`SUTO_C_GET_RSTRING` - Sent by Android client to desktop after ensuring that it has password salt. This message requests
the random string from the desktop.

`SUTO_RSTRING_%s` - Sent by desktop upon random string request. _%s_ is a placeholder which will be replaced by the 
random string. 

`SUTO_C_F_HASH_%s` - Sent by the client for authentication. _%s_ is a placeholder which will be replaced by the final 
_sha512_ hash of _password hash + Random String_.

## Authentication done.

### Message types 

`SUTO_AUTH_SUCCESS` - Sent by desktop client after successfull authentication.

`SUTO_AUTH_FAILED` - Sent by desktop client after failure of authentication.

After this the _TCP_ connection can be dropped.
