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

If you do not know what above means, get help, **now**!  In this case you do not have enough knowlege, which is needed to be able to see if you are vulnerable or not.  So better ask somebody, who groks this.

Please note that I cannot help you, sorry.


## What it does

- It is a simple wrapper which looks after it's name in `../shellshock/` and executes the script there.
- It looks into the ENV for variables which start with the famous string `() {` and prevents running the script if something like this is there.
- just hardlink it to the `.shellshock` executable

## Warning

This is no full solution.  If your script extracts data from `QUERY_STING` and uses them, there might be problems with sub-shells.
However it helps if you want to run shell scripts CGI under vulnerable bash for systems, until you can fully patch them.

## Disclaimer

Nobody is liable if this does not fully work.  You are responsible yourself if you use it.  If you break it you own all parts.

## License

This is free as in free beer, free speech and free humans, as humans are not encumbered with any Copyright.
