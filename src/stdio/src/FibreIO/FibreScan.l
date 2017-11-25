%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#define yylval FibreScanlval

#include "FibreScan.tab.h"
extern int FibreScanparse( void);


#define RETURNnum(token) yylval.cint=atoi(yytext); return(token)
#define RETURNflt(token) yylval.cfloat=atof(yytext); return(token)
#define RETURNdbl(token) char* m=index(yytext, 'd');\
                          if( m != NULL) \
                            *m='e';\
                          else {\
                            m=index(yytext, 'D');\
                            if( m != NULL)\
                              *m='E';\
                          }\
                         yylval.cdbl=atof(yytext); return(token)
#define RETURNstr(token)  {\
                               yytext[ strlen( yytext) - 1] = '\0';\
                               yylval.cstr = strdup( &yytext[1]);\
                               return(token);\
                           }

#define YY_USER_ACTION num_chars += yyleng;

static int num_chars; /* Stores the number of chars read for returned tokens */
extern int linenum;
int linenum=1;
extern int start_token;
int start_token;


%}

   /* Suppress compilation warning yyunput and input defined but not used */
%option nounput
%option noinput
%option noyywrap


%%

%{

/* the next view lines allow for smuggling in a start_token! */

     if(start_token) {
       int mem=start_token;

       start_token=0;
       return(mem);
     }
%}

"["                             		{ return(SQBR_L);    }
"]"                             		{ return(SQBR_R);    }
":"                             		{ return(COLON);     }
","                             		{ return(COMMA);     }
"true"                          		{ return(TTRUE);     }
"false"                         		{ return(TFALSE);    }

[+-]?[0-9]+[.]([0-9]+)?([dD]([+-]?[0-9]+)?)?	{ RETURNdbl(DOUBLE); }
[+-]?[0-9]+[.]([0-9]+)?([eE]([+-]?[0-9]+)?)?	{ RETURNdbl(DOUBLE); }
[+-]?[0-9]+[.]?[dD]([+-]?[0-9]+)?		{ RETURNdbl(DOUBLE); }
[+-]?[0-9]+[.]?[eE]([+-]?[0-9]+)?		{ RETURNdbl(DOUBLE); }
\"([^"\n]|(\\\"))*\"                            { RETURNstr(STRING); }
[+-]?[0-9]+             			{ RETURNnum(NUM);    }

[+-]?[0-9]+[bB]            {
                             yylval.cbyte=(char)strtoll(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to byte\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMBYTE);
                           }

[+-]?[0-9]+[sS]            {
                             yylval.cshort=(short)strtoll(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to short\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMSHORT);
                           }

[+-]?[0-9]+[iI]            {
                             yylval.cint=(int)strtoll(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to int\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMINT);
                           }

[+-]?[0-9]+[lL]            {
                             yylval.clong=(long)strtoll(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to long\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMLONG);
                           }

[+-]?[0-9]+(ll|LL)         {
                             yylval.clonglong=(long long)
			       strtoll(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to longlong\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMLONGLONG);
                           }

[+-]?[0-9]+(ub|UB)         {
                             yylval.cubyte=(unsigned char)
			       strtoull(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to ubyte\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMUBYTE);
                           }

[+-]?[0-9]+(us|US)         {
                             yylval.cushort=(unsigned short)
			       strtoull(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to ushort\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMUSHORT);
                           }

[+-]?[0-9]+(ui|UI)         {
                             yylval.cuint=(unsigned int)
			       strtoull(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to uint\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMUINT);
                           }

[+-]?[0-9]+(ul|UL)         {
                             yylval.culong=(unsigned long)
			       strtoull(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to ulong\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMULONG);
                           }

[+-]?[0-9]+(ull|ULL)         {
                             yylval.culonglong=(unsigned long long)
			       strtoull(yytext,(char **)NULL,10);
			     if(errno==ERANGE){ 
			       fprintf(stderr, \
			       "Overflow problems converting %s to ulonglong\n", \
			       yytext);
			       exit(-1);
			     }
                             return( NUMULONGLONG);
                           }

"\n"   						{linenum++;}
[ \t]   					{}
"\f"    					{}
"#".*$            {}

%%

void doScan( FILE *stream)
{
  int pos;
  errno = 0;
  pos = ftell( stream);
  /* Check if the stream is seekable */
  rewind( stream);
  if(errno!=0) {
    fprintf(stderr, 
      "The fibre scanner only supports seekable streams. "
      "Try reading the fibre input via a file.\n");
    exit(-1);
  }
  fseek( stream, pos, SEEK_SET);
  num_chars = 0;
  yyin = stream;
  FibreScanparse();
  fseek( stream, pos+num_chars, SEEK_SET);
  FibreScanrestart( stream);
}
