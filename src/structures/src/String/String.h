#ifndef STDLIB__STR__H
#define STDLIB__STR__H

#include "sacinterface.h"
#include <stdbool.h>

typedef char* string;

string SACtostring (unsigned char* arr, sac_int length);
string SACautotostring (SACarg *sarr);
void SACstrmod (string str, sac_int pos, unsigned char c);
string SACstrins (string outer, sac_int pos, string inner);
void SACstrovwt (string outer, sac_int pos, string inner);
unsigned char SACstrsel (string str, sac_int pos);
string SACstrcat (string fst, string snd);
string SACstrncat (string fst, string snd, sac_int n);
sac_int SACstrcmp (string fst, string snd);
sac_int SACstrncmp (string fst, string snd, sac_int n);
sac_int SACstrcasecmp (string fst, string snd);
sac_int SACstrncasecmp (string fst, string snd, sac_int n);
sac_int SACstrlen (string fst);
void SACstrtake(string str, sac_int pos);
string SACstrdrop (string str, sac_int pos);
string SACstrext (string str, sac_int pos, sac_int len);
string SACsprintf (string format, ...);
sac_int SACsscanf( string s, string format, ...);
string SACsscanf_str (string s, string format);
sac_int SACstrchr (string str, unsigned char c);
sac_int SACstrrchr (string str, unsigned char c);
sac_int SACstrcspn(string str, string reject);
sac_int SACstrspn(string str, string accept);
sac_int SACstrstr (string haystack, string needle);
bool chr_in_delims (unsigned char c, string delimiters);
string next_in_delims (string str, string delimiters, bool is_delimiter);
void SACstrtok (string* out_token, string* out_rest, string str, string delimiters);
void SACchomp (string str) ;
void SACrtrim (string str) ;
string SACltrim (string str) ;
string SACtrim (string str);
sac_int SACstrtoi (string* remain, string input, sac_int base);
float SACstrtof (string* remain, string input);
double SACstrtod (string* remain, string input);
sac_int SACtoi (string input);
float SACtof (string input);
double SACtod (string input);
string SACitos (sac_int n);
string SACftos (float n);
string SACdtos (double n);
string SACbtos (bool n);

#endif // STDLIB__TOSTRING__H