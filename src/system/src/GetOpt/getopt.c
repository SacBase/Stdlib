/******************************************************************************
 *
 * @brief Implements the C library function getopt(3) for SAC. Use classic short
 * getopt without some of the GNU extensions. I.e., it don't support the dash
 * '-' and plus '+' as part of the optstring. When an argument is part of an
 * option, like for "-oarg", then recognize "arg" is as an argument, not as an
 * option. See the getopt(3) manual page for details.
 *
 * @param SAC_optind: specify the next argv to consider.
 * @param SAC_opterr: enable/disable error reporting.
 * @param SAC_optopt: return the most recent option.
 * @param SAC_optarg: return the option argument, if any.
 * @param SAC_argind: specify the next option as argv[SAC_optind][SAC_argind].
 *
 ******************************************************************************/
#include <string.h>
#include <stdio.h>

#include "sac.h"

/* Import the following two prototypes from SAC's commandline parser:
 *  stdlib/world/system/src/CommandLine/CommandLine.c */
int SACargc( void);
char *SACargv(int n);

static int SAC_optind = 1;
static int SAC_opterr = 1;
static int SAC_optopt;
static char *SAC_optarg;
static int SAC_argind = 1;

int optEND(void)
{
    return '\0';
}

int get_optind(void)
{
    return SAC_optind;
}

void set_optind(int set)
{
    SAC_optind = set;
    SAC_argind = 1;
}

int get_opterr(void)
{
    return SAC_opterr;
}

void set_opterr(int set)
{
    SAC_opterr = set;
}

int get_optopt(void)
{
    return SAC_optopt;
}

static inline char *my_strdup(const char *str)
{
    char *copy = SAC_MALLOC(strlen(str) + 1);
    strcpy(copy, str);
    return copy;
}

char *get_optarg(void)
{
    return SAC_optarg ? my_strdup(SAC_optarg) : my_strdup("");
}

static void badopt(void)
{
    if (SAC_opterr) {
        char *prog = SACargv(0);
        fprintf(stderr, "%s: invalid option -- '%c'\n", prog, SAC_optopt);
        free(prog);
    }
}

static void setarg(char *arg)
{
    if (SAC_optarg != NULL) {
        free(SAC_optarg);
    }

    SAC_optarg = arg;
}

static void missing( void)
{
    if (SAC_opterr == 1) {
        char *prog = SACargv(0);
        fprintf(stderr, "%s: option requires an argument -- '%c'\n", prog, SAC_optopt);
        free(prog);
    }
}

int getopt_sac(const char *opts)
{
    const int argc = SACargc();
    int retval;

    setarg(NULL);

    if (SAC_optind < 1) {
        SAC_optind = 1;
        SAC_argind = 1;
    }

    if (SAC_optind == 1 && SAC_argind == 1 && SAC_optind < argc) {
        char *arg = SACargv(SAC_optind);

        // SaC uses the "-mt" option to enable multi-threading.
        if (!strcmp(arg, "-mt")) {
            SAC_optind += 1;
        }

        free(arg);
    }

    if (SAC_optind >= argc) {
        retval = optEND();
    } else {
        char *arg = SACargv(SAC_optind);

        if (arg[0] != '-') {
            retval = optEND();
        } else if (arg[1] == '\0') {
            retval = optEND();
        } else if (arg[1] == '-' && arg[2] == '\0') {
            SAC_optind += 1;
            SAC_argind = 1;
            retval = optEND();
        } else {
            if ((size_t)SAC_argind >= strlen(arg)) {
                SAC_optopt = '\0';
            } else {
                SAC_optopt = arg[SAC_argind];
            }

            char *p;

            if (SAC_optopt == ':' ||
                SAC_optopt == '\0' ||
                (p = strchr(opts, SAC_optopt)) == NULL) {

                badopt();
                if (arg[++SAC_argind] == '\0') {
                    SAC_optind += 1;
                    SAC_argind = 1;
                }

                retval = '?';
            } else if (*++p == ':') {
                if (arg[++SAC_argind] != '\0') {
                    setarg(my_strdup(&arg[SAC_argind]));
                    SAC_optind += 1;
                    SAC_argind = 1;
                    retval = SAC_optopt;
                } else if (++SAC_optind >= argc) {
                    missing();
                    SAC_argind = 1;
                    retval = '?';
                } else {
                    setarg(SACargv(SAC_optind));
                    ++SAC_optind;
                    SAC_argind = 1;
                    retval = SAC_optopt;
                }
            } else if (arg[++SAC_argind] == '\0') {
                SAC_optind += 1;
                SAC_argind = 1;
                retval = SAC_optopt;
            } else {
                retval = SAC_optopt;
            }
        }

        free(arg);
    }

    return retval;
}
