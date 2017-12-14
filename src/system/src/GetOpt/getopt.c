/*
 * Implement the C library function getopt(3) for SAC.
 * Use classic short getopt without some of the GNU extensions.
 * I.e., it don't support the dash '-' and plus '+' as part of the optstring.
 * When an argument is part of an option, like for "-oarg", then
 * recognize "arg" is as an argument, not as an option.
 * See the getopt(3) manual page for details.
 *
 * Use 'optind' to specify the next argv to consider.
 * Use 'opterr' to enable/disable error reporting.
 * Use 'optopt' to return the most recent option.
 * Use 'optarg' to return the option argument, if any.
 * Use 'argind' to specify the next option as argv[optind][argind].
 */

#include <string.h>
#include <stdio.h>
#include "sac.h"

/*
 * Import the following two prototypes from SAC's commandline parser:
 *
 *     stdlib/world/system/src/CommandLine/CommandLine.c
 */
int SACargc( void);
char *SACargv(int n);

int optind = 1;
int opterr = 1;
int optopt;
char *optarg;

static int argind = 1;

int optEND(void)
{
  return '\0';
}

int get_optind(void)
{
  return optind;
}

void set_optind(int set)
{
  optind = set;
  argind = 1;
}

int get_opterr(void)
{
  return opterr;
}

void set_opterr(int set)
{
  opterr = set;
}

int get_optopt(void)
{
  return optopt;
}

static inline char *my_strdup(const char *str)
{
  char *copy = SAC_MALLOC(strlen(str) + 1);

  strcpy(copy, str);
  return copy;
}

char *get_optarg(void)
{
  return optarg ? my_strdup(optarg) : my_strdup("");
}

static void badopt(void)
{
  if (opterr)
  {
    char *prog = SACargv(0);

    fprintf(stderr, "%s: invalid option -- '%c'\n", prog, optopt);
    free(prog);
  }
}

static void setarg(char *arg)
{
  if (optarg)
  {
    free(optarg);
  }
  optarg = arg;
}

static void missing( void)
{
  if (opterr == 1)
  {
    char *prog = SACargv(0);

    fprintf(stderr, "%s: option requires an argument -- '%c'\n", prog, optopt);
    free(prog);
  }
}

int getopt_sac(const char *opts)
{
  const int argc = SACargc();
  int retval;

  setarg(NULL);

  if (optind < 1)
  {
    optind = 1;
    argind = 1;
  }

  if (optind == 1 && argind == 1 && optind < argc)
  {
    char *arg = SACargv(optind);
    /* SAC uses the "-mt" option to enable multi-threading. */
    if (!strcmp(arg, "-mt"))
    {
      ++optind;
    }
    free(arg);
  }

  if (optind >= argc)
  {
    retval = optEND();
  }
  else
  {
    char *arg = SACargv(optind);

    if (arg[0] != '-')
    {
      retval = optEND();
    }
    else if (arg[1] == '\0')
    {
      retval = optEND();
    }
    else if (arg[1] == '-' && arg[2] == '\0')
    {
      optind++;
      argind = 1;
      retval = optEND();
    }
    else
    {
      if ((size_t)argind >= strlen(arg))
      {
        optopt = '\0';
      }
      else
      {
        optopt = arg[argind];
      }
      char *p;

      if (optopt == ':' ||
          optopt == '\0' ||
          (p = strchr(opts, optopt)) == NULL)
      {
        badopt();
        if (arg[++argind] == '\0')
        {
          ++optind;
          argind = 1;
        }
        retval = '?';
      }
      else if (*++p == ':')
      {
        if (arg[++argind] != '\0')
        {
          setarg(my_strdup(&arg[argind]));
          ++optind;
          argind = 1;
          retval = optopt;
        }
        else if (++optind >= argc)
        {
          missing();
          argind = 1;
          retval = '?';
        }
        else
        {
          setarg(SACargv(optind));
          ++optind;
          argind = 1;
          retval = optopt;
        }
      }
      else if (arg[++argind] == '\0')
      {
        ++optind;
        argind = 1;
        retval = optopt;
      }
      else
      {
        retval = optopt;
      }
    }
    free(arg);
  }

  return retval;
}
