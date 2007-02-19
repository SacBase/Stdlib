%{

#include <math.h>
#include <strings.h>

#define yylval FibreScanlval

#include "FibreScan.tab.h"

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

int linenum=1;
int start_token;

#define YY_SKIP_YYWRAP

int yywrap()
{
  return(1);
}

#define YY_NO_UNPUT

%}

%%

%{

/* the next view lines allow for smuggling in a start_token! */

     if(start_token) {
       int mem=start_token;

       start_token=0;
       return(mem);
     }
%}

"["                             		{ return(SQBR_L); }
"]"                             		{ return(SQBR_R); }
":"                             		{ return(COLON); }
","                             		{ return(COMMA); }
"true"                          		{ return(TTRUE); }
"false"                         		{ return(TFALSE); }
[+-]?[0-9]+             			{ RETURNnum(NUM); }
[+-]?[0-9]+[.]?[dD][+-]?[0-9]+			{ RETURNdbl(DOUBLE); }
[+-]?[0-9]+[.]([0-9]+)?([dD][+-]?[0-9]+)?	{ RETURNdbl(DOUBLE); }
[+-]?[0-9]+[.]?[eE][+-]?[0-9]+			{ RETURNflt(FLOAT); }
[+-]?[0-9]+[.]([0-9]+)?([eE][+-]?[0-9]+)?	{ RETURNflt(FLOAT); }

"\n"   						{linenum++;}
[ \t]   					{}
"\f"    					{}



