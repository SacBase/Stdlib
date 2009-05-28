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
                yyerror("FIBRE: more sub-arrays than specified!");
                return(1);
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
                yyerror("FIBRE: more sub-arrays than specified!");
                return(1);
              }
            }
          ;

int_array: SQBR_L desc COLON
           { if( given_dim != 0) {
               yyerror("FIBRE: array of higher dimensionality expected!");
               return(1);
             }
           }
           ints SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("FIBRE: fewer array elements than specified!");
               return(1);
             }
             given_dim++;
             given_shp--;
           }
         | SQBR_L desc COLON int_arrays SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("FIBRE: fewer sub-arrays than specified!");
               return(1);
             }
             given_dim++;
             given_shp--;
           }
         ;

ints: ints NUM
      { 
        if( elems_left[given_dim]-- == 0) {
          yyerror("FIBRE: more array elements than specified!");
          return(1);
        }
        intarray[array_ptr++]= $2;
      } 
      | /* empty */
      ;


flt_arrays: flt_array
            { if( elems_left[given_dim]-- == 0) {
                yyerror("FIBRE: more sub-arrays than specified!");
                return(1);
              }
            }
            flt_arrays
          | flt_array
            { if( elems_left[given_dim]-- == 0) {
                yyerror("FIBRE: more sub-arrays than specified!");
                return(1);
              }
            }
          ;

flt_array: SQBR_L desc COLON
           { if( given_dim != 0) {
               yyerror("FIBRE: array of higher dimensionality expected!");
               return(1);
             }
           }
           flts SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("FIBRE: fewer array elements than specified!");
               return(1);
             }
             given_dim++;
             given_shp--;
           }
         | SQBR_L desc COLON flt_arrays SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("FIBRE: fewer sub-arrays than specified!");
               return(1);
             }
             given_dim++;
             given_shp--;
           }
         ;

flts: flts FLOAT
      { 
        printf("elems_left[given_dim] = %i, array_ptr = %i, num = %f\n",
        elems_left[given_dim], array_ptr, $2);
        if( elems_left[given_dim]-- == 0) {
          yyerror("FIBRE: more array elements than specified!");
          return(1);
        }
        floatarray[array_ptr++]=$2;
      } 
      | /* empty */
      ;


dbl_arrays: dbl_array 
            { if( elems_left[given_dim]-- == 0) {
                yyerror("FIBRE: more sub-arrays than specified!");
                return(1);
              }
            }
            dbl_arrays
          | dbl_array
            { if( elems_left[given_dim]-- == 0) {
                yyerror("FIBRE: more sub-arrays than specified!");
                return(1);
              }
            }
          ;

dbl_array: SQBR_L desc COLON
           { if( given_dim != 0) {
               yyerror("FIBRE: array of higher dimensionality expected!");
               return(1);
             }
           }
           dbls SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("FIBRE: fewer array elements than specified!");
               return(1);
             }
             given_dim++;
             given_shp--;
           }
         | SQBR_L desc COLON dbl_arrays SQBR_R
           { if( elems_left[given_dim] != 0) {
               yyerror("FIBRE: fewer sub-arrays than specified!");
               return(1);
             }
             given_dim++;
             given_shp--;
           }
         ;

dbls: dbls DOUBLE
      { if( elems_left[given_dim]-- == 0) {
          yyerror("FIBRE: more array elements than specified!");
          return(1);
        }
        doublearray[array_ptr++]=$2;
      } 
    | /* empty */
    ;

desc: NUM COMMA NUM
      { if (given_dim-- == 0) {
          yyerror( "FIBRE: array of lower dimensionality expected!");
          return(1);
        }
        if ($1 != 0) {
          yyerror( "FIBRE: Array indexing must start with 0!");
          return(1);
        }
        if( *given_shp != $3 + 1) {
          yyerror( "FIBRE: shape does not match specification!");
          return(1);
        }
        elems_left[given_dim]=*given_shp++;
      }
    ;


%%


void yyerror( char *errname)
{
  fprintf( stderr, "line %d: \"%s\" : %s\n", linenum, yytext, errname);
}
