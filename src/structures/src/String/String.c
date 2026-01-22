/*
 *  C implementation of standard module StringC
 */


#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "String.h"

string copy_string (string s)
{
    string s2 = malloc ((strlen(s) + 1) * sizeof (char));
    strcpy (s2, s);
    return s2;
}

string free_string (string s)
{
    free (s);
    return NULL;
}




string SACtostring (unsigned char* arr, sac_int length)
{
    string res = malloc ((size_t) length + 1);

    memcpy (res, arr, (size_t)length);
    res[length] = '\0';

    return res;
}

string SACautotostring (SACarg *sarr)
{
    const string *parr = SACARGgetSharedData(SACTYPE__MAIN__char, sarr);
    string arr = parr[0];
    sac_int length = SACARGgetShape(sarr, 0);

    string res = malloc ((size_t) length + 1);

    strncpy (res, arr, (size_t)length);
    res[length] = '\0';

    SACARGdeleteSacArray(&sarr);
    return res;
}

void SACstrmod (string str, sac_int pos, unsigned char c)
{
    size_t strlength = strlen (str);

    if (strlength <= (size_t)pos)
        SAC_RuntimeError("strmod: pos ("PRIisac") outside of string (length %zu)", pos, strlength);

    str[pos] = c;
}

string SACstrins (string outer, sac_int pos, string inner)
{
    size_t outer_length = strlen (outer);
    size_t inner_length = strlen (inner);

    string res = malloc(outer_length + inner_length + 1);

    strncpy(res, outer, (size_t)pos);
    strcpy(res+(size_t)pos, inner);
    strcpy(res+(size_t)pos+inner_length, outer+(size_t)pos);

    return res;
}

void SACstrovwt (string outer, sac_int pos, string inner)
{
    size_t outer_length = strlen (outer);
    size_t inner_length = strlen (inner);

    if ((size_t)pos+inner_length > outer_length)
        SAC_RuntimeError("strovwt: Overwriting string ends at position "PRIisac" while string is of length %zu", pos+inner_length, outer_length);

    memcpy(outer+(size_t)pos, inner, inner_length * sizeof (char));
}

unsigned char SACstrsel (string str, sac_int pos)
{
    size_t strlength = strlen(str);
    if ((size_t)pos >= strlength)
        SAC_RuntimeError("strsel: pos ("PRIisac") outside of string (length %zu)", pos, strlength);

    return str[pos];
}

string SACstrcat (string fst, string snd)
{
    size_t fstlength = strlen (fst);
    size_t sndlength = strlen (snd);

    string res = malloc (fstlength + sndlength + 1);

    strcpy(res, fst);
    strcpy(res+fstlength, snd);

    return res;
}

string SACstrncat (string fst, string snd, sac_int n)
{
    size_t fstlength = strlen (fst);

    string res = malloc (fstlength + (size_t)n + 1);

    strcpy(res, fst);
    strncpy(res+fstlength, snd, (size_t)n);
    res[fstlength+(size_t)n] = '\n';

    return res;
}

sac_int SACstrcmp (string fst, string snd)
{
    return (sac_int) strcmp (fst, snd);
}

sac_int SACstrncmp (string fst, string snd, sac_int n)
{
    return (sac_int) strncmp (fst, snd, (size_t) n);
}

sac_int SACstrcasecmp (string fst, string snd)
{
    return (sac_int) strcasecmp (fst, snd);
}

sac_int SACstrncasecmp (string fst, string snd, sac_int n)
{
    return (sac_int) strncasecmp (fst, snd, (size_t) n);
}

sac_int SACstrlen (string fst)
{
    return (sac_int) strlen (fst);
}

void SACstrtake(string str, sac_int pos)
{
    size_t strlength = strlen (str);

    if ((size_t)pos >= strlength)
        SAC_RuntimeError("strtake: pos ("PRIisac") outside of string (length %zu)", pos, strlength);

    str[pos] = '\0';
}

string SACstrdrop (string str, sac_int pos)
{
    size_t strlength = strlen (str);

    string res = malloc(strlength - (size_t)pos + 1);

    strcpy(res, str+(size_t)pos);

    return res;
}

string SACstrext (string str, sac_int pos, sac_int len)
{
    size_t strlength = strlen(str);

    string res = malloc(strlength - (size_t)len + 1);

    if ((size_t)(pos + len) >= strlength)
        SAC_RuntimeError("strext: Selecting substring ends at position "PRIisac" while string is of length %zu", pos+len, strlength);

    strncpy(res, str+(size_t)pos, (size_t)len);

    return res;
}

bool chr_in_delims (char c, string delimiters)
{
    while (true)
    {
        if (delimiters[0] == '\0')
            return false;
        if (delimiters[0] == c)
            return true;
        delimiters ++;
    }
}

string next_in_delims (string str, string delimiters, bool is_delimiter)
{
    while (true)
    {
        if (str[0] == '\0')
            return NULL;
        if (chr_in_delims(str[0], delimiters) == is_delimiter)
            return str;
        str ++;
    }
}

static char fmtstart = '%';
static char fmtspecifiers[] = "di";
static char fmtmodifiers[] = "+- #.*0123456789";

string find_fmtstr_spec_loc(string format)
{
    do
    {
        // Find %
        format = strchr(format, fmtstart);
        // Skip modifiers
        format = next_in_delims(format, fmtmodifiers, false);
    }
    // Check if at end, or delimiter has been found
    while (format != NULL && !chr_in_delims(*format, fmtspecifiers));
    return format;
}

string fix_fmtstr_sac_int (string format)
{
    // Count the number of replaces that need to occur, to comput the format string new size
    size_t replaces = 0;
    string fmt = find_fmtstr_spec_loc(format);
    while (fmt != NULL)
    {
        replaces ++;
        fmt = find_fmtstr_spec_loc(fmt);
    }

    // Compute the size of the new string, and allocat enough memory
    // For each replace, we remove 1 character and add the length of PRIisac
    size_t priisaclength = strlen(PRIisac);
    size_t formatlength = strlen(format);
    string res = malloc ((formatlength + replaces * (formatlength-1) + 1) * sizeof (char));

    // Copy parts of strings into the result
    string start = format;
    string respos = res;
    while (format != NULL)
    {
        // Find the next occurence of a format string specifier to be found
        format = find_fmtstr_spec_loc(start);
        if (format == NULL)
        {
            // If at end, simply copy over the rest of the string
            strcpy(respos, start);
        }
        else
        {
            // If found, copy the part of the string until the specifier, including the % and modifiers
            strncpy(respos, start, format-start);
            respos += format-start;
            // Set new start to just after the i or d character
            start = format+1;
            // Add the format string specifier for our SaC ints
            strcpy(respos, PRIisac);
            respos += priisaclength;
        }
    }

    return res;
}

string SACsprintf (string format_raw, ...)
{
    string format = fix_fmtstr_sac_int(format_raw);

    va_list args;

    // Compute the length of the string
    va_start (args, format_raw);
    int lengthwo0 = vsnprintf (NULL, 0, format, args);
    va_end (args);

    if (lengthwo0 < 0)
        SAC_RuntimeError("printf error %d", lengthwo0);

    size_t length = lengthwo0 + 1;

    // Allocate result string
    string res = malloc(length);

    // Printf string
    va_start (args, format_raw);
    vsnprintf (res, length, format, args);
    va_end (args);

    return res;
}

sac_int SACsscanf (string s, string format_raw, ...)
{
    string format = fix_fmtstr_sac_int(format_raw);
    
    va_list arg_p;

    va_start( arg_p, format_raw);
    sac_int res = (sac_int)vsscanf( s, format, arg_p);
    va_end( arg_p);

    return res;
}

string SACsscanf_str (string source, string format_raw)
{
    string format = fix_fmtstr_sac_int(format_raw);

    string res = malloc (strlen (source) + 1);
    res[0] = '\0';

    sscanf (source, format, res);

    return res;
}

sac_int SACstrchr (string str, unsigned char c)
{
    string occurrence = strchr (str, c);

    if (occurrence == NULL)
        return -1;
    return (sac_int)(occurrence - str);
}

sac_int SACstrrchr (string str, unsigned char c)
{
    string occurrence = strrchr (str, c);

    if (occurrence == NULL)
        return -1;
    return (sac_int)(occurrence - str);
}

sac_int SACstrcspn(string str, string reject)
{
    return (sac_int) strcspn(str, reject);
}

sac_int SACstrspn(string str, string accept)
{
    return (sac_int) strspn(str, accept);
}

sac_int SACstrstr (string haystack, string needle)
{
    return (sac_int) strstr (haystack, needle);
}

void SACstrtok (string* out_token, string* out_rest, string str, string delimiters)
{
    string start = next_in_delims(str, delimiters, false);
    string end = next_in_delims(start, delimiters, true);

    size_t tokenlength = end - start;
    *out_token = malloc((tokenlength + 1) * sizeof (char));
    strncpy(*out_token, start, tokenlength);
    *out_token[tokenlength] = '\0';

    *out_rest = malloc((strlen(end) + 1) * sizeof (char));
    strcpy(*out_rest, end);
}

void SACchomp (string str) 
{
    string end = str + strlen(str);

    while (end > str)
    {
        end --;
        if (*end == '\n' || *end == '\r')
            *end = '\0';
        else
            break;
    }
}

void SACrtrim (string str) 
{
    string end = str + strlen(str);

    while (end > str)
    {
        end --;
        if (isspace(*end))
            *end = '\0';
        else
            break;
    }
}

string SACltrim (string str) 
{
    string end = str + strlen(str);

    while (str < end)
    {
        if (!isspace(*end))
            *end = '\0';
        else
            break;
        str ++;
    }

    string res = malloc ((strlen(str) + 1) * sizeof (char));
    strcpy(res, str);
    
    return res;
}

string SACtrim (string str)
{
    string res = SACltrim(str);
    SACrtrim (res);
    return res;
}

sac_int SACstrtoi (string* remain, string input, sac_int base)
{
    string rem;
    sac_int res = (sac_int) strtol (input, &rem, (size_t)base);

    *remain = malloc ((strlen(rem) + 1) * sizeof (char));
    strcpy (*remain, rem);

    return res;
}


float SACstrtof (string* remain, string input)
{
    string rem;
    float res = (float) strtod (input, &rem);

    *remain = malloc ((strlen(rem) + 1) * sizeof (char));
    strcpy (*remain, rem);

    return res;
}

double SACstrtod (string* remain, string input)
{
    string rem;
    double res = strtod (input, &rem);

    *remain = malloc ((strlen(rem) + 1) * sizeof (char));
    strcpy (*remain, rem);

    return res;
}

sac_int SACtoi (string input)
{
    return (sac_int) strtol (input, NULL, 0);
}

float SACtof (string input)
{
    return (float) strtod (input, NULL);
}

double SACtod (string input)
{
    return strtod (input, NULL);
}

string SACitos (sac_int n)
{
    string res = malloc(40);

    sprintf (res, "%"PRIisac, n);

    return res;
}

string SACftos (float n)
{
    string res = malloc(40);

    sprintf (res, "%g", n);

    return res;
}

string SACdtos (double n)
{
    string res = malloc(40);

    sprintf (res, "%g", n);

    return res;
}

string SACbtos (bool n)
{
    string res = malloc(6 * sizeof(char));

    if (n)
        strcpy (res, "true");
    else
        strcpy (res, "false");

    return res;
}