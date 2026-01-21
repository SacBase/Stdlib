/*
 *  Implementation of external standard class CommandLine.
 */

#include <string.h>

#include "sac.h"
#include "sacinterface.h"

typedef struct COMLINE {
    sac_int argc;
    char **argv;
} ComLine;

extern ComLine *SACo_CommandLine__TheCommandLine;

ComLine *create_TheCommandLine(void)
{
    ComLine *parameters = (ComLine *)SAC_MALLOC(sizeof(ComLine));
    parameters->argc = (sac_int)SAC_commandline_argc;
    parameters->argv = SAC_commandline_argv;
    return parameters;
}

sac_int SACargc(void)
{
    return SACo_CommandLine__TheCommandLine->argc;
}

char *SACargv(sac_int n)
{
    char *res;

    if (n < SACo_CommandLine__TheCommandLine->argc)
    {
        char *arg = (SACo_CommandLine__TheCommandLine->argv)[n];
        res = (char *)SAC_MALLOC(strlen(arg) + 1);
        strcpy(res, arg);
    }
    else
    {
        res = (char *)SAC_MALLOC(1);
        res[0] = '\0';
    }

    return res;
}

char *SACargvall(void)
{
    size_t len = 0;
    for (sac_int i = 0; i < SACo_CommandLine__TheCommandLine->argc; i++)
    {
        char *arg = (SACo_CommandLine__TheCommandLine->argv)[i];
        len += strlen(arg);
    }

    size_t spaces = (size_t)SACo_CommandLine__TheCommandLine->argc;
    char *res = (char *)SAC_MALLOC(len + spaces + 1);

    strcpy(res, (SACo_CommandLine__TheCommandLine->argv)[0]);
    for (sac_int i = 1; i < SACo_CommandLine__TheCommandLine->argc; i++)
    {
        strcat(res, " ");
        char *arg = (SACo_CommandLine__TheCommandLine->argv)[i];
        strcat(res, arg);
    }

    return res;
}
