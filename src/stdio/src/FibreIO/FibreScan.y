%{

extern int linenum;
extern char yytext[];

#include <stdio.h>
#include "FibreScan.h"
#include "../../../../config/config.h"

int boolval;
int intval;
float floatval;
double doubleval;
double *doublearray;
float *floatarray;
int *intarray;

int given_dim;
int *given_shp;

static int array_ptr;
static int elems_left[MAXDIM];

static void yywarn( char *msg);
 

%}


%union { int             cint;
         int             cbool;
         char            cchar;
         float           cfloat;
         double          cdbl;
         double*         cdbl_ptr;
         float*          cflt_ptr;
         int*            cint_ptr;
       }


%token PARSE_BOOL PARSE_INT PARSE_FLOAT PARSE_DOUBLE
       PARSE_DOUBLE_ARRAY PARSE_INT_ARRAY PARSE_FLOAT_ARRAY
%token SQBR_L SQBR_R COLON COMMA TTRUE TFALSE
%token <cint> NUM
%token <cfloat> FLOAT
%token <cdbl> DOUBLE
%token <cchar> CHAR


%type <cbool> bool
%type <cdbl_ptr> dbl_array
%type <cflt_ptr> flt_array
%type <cint_ptr> int_array


%start file


%{

/*
 * Make sure, the stack of the generated parser is big enough!
 */
#define YYMAXDEPTH 100000

%}


%%


file: PARSE_BOOL bool {boolval = $2; return(0);}
    | PARSE_INT  NUM {intval = $2; return(0);} 
    | PARSE_FLOAT FLOAT {floatval = $2; return(0);}
    | PARSE_DOUBLE DOUBLE {doubleval = $2; return(0);}
    | PARSE_DOUBLE_ARRAY { array_ptr=0;} dbl_array { return(0);}
    | PARSE_FLOAT_ARRAY { array_ptr=0;} flt_array { return(0);}
    | PARSE_INT_ARRAY { array_ptr=0;} int_array { return(0);}
    ;


bool: TTRUE {$$ = 1;}
    | TFALSE {$$ = 0;}
    ;


int_arrays: int_array
            { if( elems_left[given_dim]-- == 0) {
                yyerror("more sub-arrays than specified!");
#ifdef MUST_REFERENCE_YYLABELS
                /*
                 * The follwing command is a veeeeeeery ugly trick to avoid warnings
                 * on the alpha: the YYBACKUP-macro contains jumps to two labels
                 * yyerrlab  and  yynewstate  which are not used otherwise.
                 * Hence, the usage here, which in fact never IS (and never SHOULD)
                 * be carried out, prevents the gcc from complaining about the two
                 * aforementioned labels not to be used!!
                 */
                YYBACKUP( NUM, yylval);
#endif
              }
            }
            int_arrays
          | int_array
            { if( elems_left[given_dim]-- == 0) {
                yyerror("more sub-arrays than specified!");
              }
            }
          ;

int_array: SQBR_L desc COLON
           { if( given_dim != 0) {
               yyerror("array of higher dimensionality expected!");
             }
           }
           ints SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("fewer array elements than specified!");
             }
             given_dim++;
             given_shp--;
           }
         | SQBR_L desc COLON int_arrays SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("fewer sub-arrays than specified!");
             }
             given_dim++;
             given_shp--;
           }
         ;

ints: ints NUM
      { 
        if( elems_left[given_dim]-- == 0) {
          yyerror("more array elements than specified!");
        }
        intarray[array_ptr++]= $2;
      } 
      | /* empty */
      ;


flt_arrays: flt_array
            { if( elems_left[given_dim]-- == 0) {
                yyerror("more sub-arrays than specified!");
              }
            }
            flt_arrays
          | flt_array
            { if( elems_left[given_dim]-- == 0) {
                yyerror("more sub-arrays than specified!");
              }
            }
          ;

flt_array: SQBR_L desc COLON
           { if( given_dim != 0) {
               yyerror("array of higher dimensionality expected!");
             }
           }
           flts SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("fewer array elements than specified!");
             }
             given_dim++;
             given_shp--;
           }
         | SQBR_L desc COLON flt_arrays SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("fewer sub-arrays than specified!");
             }
             given_dim++;
             given_shp--;
           }
         ;

flts: flts FLOAT
      { 
        if( elems_left[given_dim]-- == 0) {
          yyerror("more array elements than specified!");
        }
        floatarray[array_ptr++]=$2;
      } 
      | /* empty */
      ;


dbl_arrays: dbl_array 
            { if( elems_left[given_dim]-- == 0) {
                yyerror("more sub-arrays than specified!");
              }
            }
            dbl_arrays
          | dbl_array
            { if( elems_left[given_dim]-- == 0) {
                yyerror("more sub-arrays than specified!");
                return(1);
              }
            }
          ;

dbl_array: SQBR_L desc COLON
           { if( given_dim != 0) {
               yyerror("array of higher dimensionality expected!");
             }
           }
           dbls SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("fewer array elements than specified!");
             }
             given_dim++;
             given_shp--;
           }
         | SQBR_L desc COLON dbl_arrays SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("fewer sub-arrays than specified!");
             }
             given_dim++;
             given_shp--;
           }
         ;

dbls: dbls DOUBLE
      { if( elems_left[given_dim]-- == 0) {
          yyerror("more array elements than specified!");
        }
        doublearray[array_ptr++]=$2;
      } 
    | /* empty */
    ;

desc: NUM COMMA NUM
      { if (given_dim-- == 0) {
          yyerror( "array of lower dimensionality expected!");
        }
        if ($1 != 0) {
          yywarn( "automatic index range conversion!");
          yywarn( "expected start index: 0.");
        }
        if( *given_shp != $3 - $1 + 1) {
          yyerror( "shape does not match specification!");
        }
        elems_left[given_dim]=*given_shp++;
      }
    ;


%%


void yyerror( char *msg)
{
  fprintf( stderr, "FIBRE error: line %d: \"%s\" : %s\n", linenum, yytext, msg);
  fprintf( stderr, "FIBRE error: document scan terminated!\n");
  exit(1);
}

static
void yywarn( char *msg)
{
  fprintf( stderr, "FIBRE warning: line %d: \"%s\" : %s\n", linenum, yytext, msg);
}
