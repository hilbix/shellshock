# Shellshock mitigation

Change following recipe to your needs:

```bash
git clone https://github.com/hilbix/shellshock.git
cd shellshock

make
strip -s shellshock
cp shellshock /srv/www/cgi-bin/.shellshock

cd /srv/www/cgi-bin
chown www-run.public .shellshock
chmod 555 .shellshock
mkdir ../shellshock
mv -i * ../shellshock/
for a in ../shellshock/*; do ln .shellshock "${a##*/}"; done
```

Do this with all your `cgi-bin` directories.  Look into your config if there are some directories which execute shell scripts without beeing named `cgi-bin`.  Be sure to replace the scripts with `shellshock`-wrapper, too (and that the new `shellshock`-directory is not reachable from web server, of course).

If you do not know what above means, get help, **now**!  In this case you do not have enough knowlege, which is needed to be able to see if you are vulnerable or not.  So better ask somebody, who groks this.

Please note that I cannot help you, sorry.


## What it does

- It is a simple wrapper which looks after it's name in `../shellshock/` and executes the script there.
- It looks into the ENV for variables which start with the famous string `() {` and prevents running the script if something like this is there.
- Move your script to directory `../shellshock/` such that it is outside your webserver tree.  Then hardlink `.shellshock` executable to the script name.  Use hardlinks, as not all webservers follow softlinks, such that the webserver executes `.shellshock` under the script's name instead of your script.
- To test it try `curl -D- -A '() {' http://your.web.example.com/cgi-bin/.shellshock`.  If properly invoked you see something like
```text
HTTP/1.1 403 shellshock rejected
Date: Sat, 27 Sep 2014 09:53:29 GMT
Server: Apache
Transfer-Encoding: chunked
Content-Type: text/plain

```

- You can leave in this wrapper even after your `bash` was updated.  Why not ;)


## Warning

- This is no full solution.  If your script extracts data from `QUERY_STING` and uses them, there might be problems with sub-shells. However it helps if you want to run shell scripts CGI under vulnerable bash for systems, until you can fully patch them.

- This is **not** designed to handle subdirectories in your `cgi-bin` like `http://your.web.example.com/cgi-bin/cgi-bin/scripts/realscript.sh`, sorry.  You have to fix this yourself, somehow.

## Disclaimer

Nobody is liable if this does not fully work.  You are responsible yourself if you use it.  If you break it you own all parts.

## License

This is free as in free beer, free speech and free humans, as humans are not encumbered with any Copyright.
