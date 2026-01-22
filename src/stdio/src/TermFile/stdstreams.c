/*
 * Implementation of standard class TermFile
 */

#include "TermFile.h"

void *SAC_create_stdin(void)
{
    return stdin;
}

void *SAC_create_stdout(void)
{
    return stdout;
}

void *SAC_create_stderr(void)
{
    return stderr;
}
