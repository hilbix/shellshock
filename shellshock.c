#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern char **environ;

int
main(int argc, char **argv)
{
  char *s = argv[0];
  char *p = strrchr(s, '/');
  char buf[256];
  struct stat st;
  char **env, *bug;

  if (p)
    s = p+1;
  
  snprintf(buf, sizeof buf, "../shellshock/%s", s);
  bug = NULL;

  for (env=environ; *env; env++)
    {
      p = *env;
      do
	if (!*p)
	  {
	    bug = *env;
	    break;
	  }
      while (*p++!='=');
      if (!strncmp(p, "() {", 4))
	bug = *env;
    }

  if (!bug)
    {
      if (!stat(buf, &st))
        {
	  int err;

          err = execv(buf, argv);
          sprintf(buf, "exec failed: %d", errno);
          bug = buf;
        }
      else 
        bug = "not found";
    }
  
  printf("Status: 403 shellshock rejected\r\nContent-type: text/plain\r\n\r\nBUG %s", bug);
  return 1;
}
