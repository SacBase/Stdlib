/*
 *  Implementation of standard module Time
 */



#include "Time.h"


extern char *strptime(const char *, const char *, struct tm *);

/* 
 * Unfortunately, the function strptime() is not declared in time.h !
 * Fortunately, the standard library libc.a contains an implementation
 * of  strptime().
 */



/******************************************************************/


time_t *SACstrptime(string *result, string s, string format)
{
  struct tm tt;
  string remain;
  time_t *t;
  
  remain=strptime(s, format, &tt);
  
  *result=(string)MALLOC(strlen(remain)+1);
  strcpy(*result, remain);
  
  t=(time_t*)MALLOC(sizeof(time_t));
  *t=mktime(&tt);
  
  return(t);
}



/******************************************************************/
