# FAQ

Just a few things to note

## testing with `./shellshock` gives an endless loop

If you have compiled `shellshock` and then run it as `./shellshock`, it is invoked with name `shellshock`.
Hence it calls `../shellshock/shellshok` afterwards.  Which usually is itself.  Hence it must loop, this is the intended behavior.

Note that `shellshock` does not only call scripts.  It calls everything which can be execute, thanks to the `exec()` syscall.

To test `./shellshock` you can try `TEST='() {' ./shellshock; ret=$?; echo; echo $?` which will give you

```text
Status: 403 shellshock rejected
Content-type: text/plain

BUG TEST=() {
0
```

## `shellshock` is too verbose in the `BUG` line

This is for diagnostic purpose in case things go wrong.  If some user sees this you can get a clue what happened.

And it should be no problem, as the error is sent as `403` `text/plain`, so no bad things like XSS should happen - except you have a broken browser.

Also cloning and changing this is easy. The source use you can.


## Can you give me more information about Shellshock?

- [Please have a look into the CVE](https://www.us-cert.gov/ncas/alerts/TA14-268A) yourself.
- I am not related to this discovery, just another victim, as nearly everybody on this planet who uses `bash`.
- I do not even claim, that my `shellshock` tool catches all possible variants of Shellshock, but it is enough for me to be able to sleep again without worries again.  ;)

## Do you know other ways to block Shellshock?

Probably you can do this with `haproxy`.  Also please do not forget `HTTPS`!

Following is UNTESTED, so please do not rely on it without testing:

```text
  # Disallow QUERY_STRING to start with ()
  reqdeny ^[^:\ ]*\ [^?]*\?\(\)
  # Disallow QUERY_STRING arguments to start with =()
  reqdeny ^[^:\ ]*\ [^?]*\?.*=\(\)
  # Disallow headers to start with '() {'
  reqdeny ^[^:]:[[:space:]]*\(\)\ {
```

But please note that this `haproxy` rules are not perfect, you can probably work around them.


## CLL?

THis is just my variant of Public Domain.  You can do with it whatever you want, except one small exception:

If you ever add a Copyright to it, you will harm your trustworthiness.
