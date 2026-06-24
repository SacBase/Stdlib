#include "File.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

#include "sacinterface.h"


sac_int SACfopen(File *f, string name, string mode)
{
    *f = fopen(name, mode);

    bool is_error = *f==NULL;
    int error = is_error ? errno : -1;

    return error;
}

sac_int SACfclose(File f)
{
    return fclose(f);
}

sac_int SACmkstemp(File* f_out, string template)
{
    int filedesc = mkstemp (template);

    bool is_error = filedesc == -1;
    if (is_error) {
        return EIO;
    }

    // Actually open the file for reading
    *f_out = fdopen(filedesc, "w+");

    is_error = *f_out == NULL;
    if (is_error) {
        return errno;
    }

    return EXIT_SUCCESS;
}

sac_int SACremove(string name)
{
    int code = remove(name);

    bool is_error = code == -1;
    if (is_error)
        return errno;
    else
        return code;
}


sac_int SACfputc(unsigned char c, File f)
{
  return fputc(c, f);
}

unsigned char SACfgetc(File stream)
{
    return fgetc(stream);
}

sac_int SACungetc(unsigned char c, File f)
{
  return ungetc(c, f);
}

sac_int SACfputs(char *s, FILE *f)
{
    return fputs( s, f);
}

SAC_C_EXTERN SACtypes *SACTYPE_String__string;

sac_int SACfgets(SACarg **str, sac_int size, File f)
{
    string buf = malloc (sizeof(char) * size);

    bool malloc_fail = buf == NULL;
    if (malloc_fail) {
        free (buf);
        return ENOMEM;
    }

    char* result = fgets (buf, size, f);
    bool fgets_fail = result == NULL;
    if (fgets_fail) {
        free (buf);
        return errno;
    }

    size_t written = strlen (buf) + sizeof ('\0');
    sac_int shp[] = { (sac_int)written };
    *str = SACARGcreateFromPointer (SACTYPE_String__string, buf, 1, shp);

    return -1;
}

void SACfprintf(File f, string format, ...) {
    va_list args;

    va_start(args, format);
    vfprintf( f, format, args);
    va_end(args);
}

sac_int SACfscanf(File f, char *format, ...)
{
    va_list args;
    va_start(args, format);
    const sac_int ret = vfscanf(f, format, args);
    va_end(args);

    return ret;
}

string SACfscans(File stream, sac_int length)
{
    char format[32];

    string input = malloc(length + 1);
    snprintf(format, sizeof format, " %%%"PRIisac"s", length);

    int success = fscanf(stream, format, input);
    if (success != 1) {
        input[0] = 0;
    }

    return input;
}

string fscanl(File stream, const sac_int max)
{
    char *input, *success;

    input = malloc(max+3);
    success = fgets(input, max+1, stream);

    if (success == NULL) {
        input[0]=0;
    }

    return input;
}

bool SACfeof(const File f)
{
    return feof( f);
}

sac_int SACflush(const File f)
{
    return feof( f);
}

sac_int SACfseek(File f, const sac_int offset, const sac_int base)
{
  return fseek(f, offset, base);
}

sac_int SACftell(const File f)
{
    return ftell(f);
}
