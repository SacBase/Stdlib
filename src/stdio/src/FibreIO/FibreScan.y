%{

extern int linenum;
extern char yytext[];

#include <stdio.h>
#include "FibreScan.h"
#include "../../../../config/config.h"


enum READMODE {
  int_mode,
  float_mode,
  double_mode,
};

int boolval;
int intval;
float floatval;
double doubleval;
double *doublearray;
float *floatarray;
int *intarray;

int i;
int shape[ MAXDIM];
int dim_pos;
enum READMODE mode;

int got_scaler;
int size_fixed;
int dims;
int size;
static int array_pos;
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
%type <cint_ptr> array


%start file


%{

/*
 * Make sure, the stack of the generated parser is big enough!
 */
#define YYMAXDEPTH 100000

%}


%%


file: PARSE_BOOL bool 
         {boolval = $2; return(0);}
    | PARSE_INT  NUM 
         {intval = $2; return(0);} 
    | PARSE_FLOAT FLOAT 
         {floatval = $2; return(0);}
    | PARSE_DOUBLE DOUBLE 
         {doubleval = $2; return(0);}
    | PARSE_DOUBLE_ARRAY 
         {got_scaler = 0; mode = double_mode;} 
         parse_array 
         {return(0);}
    | PARSE_FLOAT_ARRAY 
         {got_scaler = 0; mode = float_mode;} 
         parse_array 
         {return(0);}
    | PARSE_INT_ARRAY 
         {got_scaler = 0; mode = int_mode;} 
         parse_array 
         {return(0);}
    ;


parse_array: {dims=0; 
              dim_pos=-1;
              array_pos=0;
              size_fixed=0;
             } 
             array { return(0);}
           | parse_scalar 
           ;

parse_scalar: NUM 
                {if( ! mode == int_mode) { 
                   yyerror( "Read integer but expected a floating point number!");
                 }
                 got_scaler = 1; 
                 intarray = (int *) SAC_MALLOC( sizeof( int));
                 *intarray = $1;
                 dims = 0;
                 size = 1;
                }
            | DOUBLE
                {if( ( ! mode == float_mode) &&
                     ( ! mode == double_mode)) { 
                   yyerror( "Unexpected floating point read!\n");
                 }
                 got_scaler = 1; 
                 switch( mode) {
                   case float_mode:
                     floatarray = (float *) SAC_MALLOC( sizeof( float));
                     *floatarray = (float)$1;
                     dims = 0;
                     size = 1;
                     break;
                   case double_mode:
                     doublearray = (double *) SAC_MALLOC( sizeof( double));
                     *doublearray = $1;
                      dims = 0;
                     size = 1;
                     break;
                   case int_mode:
                     yyerror( 
                       "Incorrectly parsed integer where double was expected");
                     break;
                 }
               }

bool: TTRUE {$$ = 1;}
    | TFALSE {$$ = 0;}
    ;



arrays: array 
        { if( size_fixed) {
            if( elems_left[ dim_pos] == 0) {
              yyerror("more sub-arrays than specified!");
#ifdef MUST_REFERENCE_YYLABELS
              /*
               * The following command is a veeeeeeery ugly trick to avoid
               * warnings on the alpha: the YYBACKUP-macro contains jumps to
               * two labels yyerrlab  and  yynewstate  which are not used
               * otherwise.  Hence, the usage here, which in fact never IS (and
               * never SHOULD) be carried out, prevents the gcc from
               * complaining about the two aforementioned labels not to be
               * used!!
               */
              YYBACKUP( NUM, yylval);
#endif
            }
            elems_left[ dim_pos]--;
          }
        }
        arrays
      | array
        { if( size_fixed) {
            if ( elems_left[ dim_pos] == 0) {
              yyerror("One more sub-array than specified!");
            }
            elems_left[ dim_pos]--;
          }
        }
          ;

array: SQBR_L desc COLON
       { if( ! size_fixed) {
           size_fixed = 1;
           for( i = 0, size = 1; i < dims; i++) {
             size *= shape[ i];
           }
           switch( mode) {
             case int_mode:
               intarray = (int *) SAC_MALLOC( size * sizeof( int));
               break;
             case float_mode:
               floatarray = (float *) SAC_MALLOC( size * sizeof( float));
               break;
             case double_mode:
               doublearray = (double *) SAC_MALLOC( size * sizeof( double));
               break;
           }
         }
         else {
           if( ( dim_pos + 1) != dims) {
             yyerror("array of higher dimensionality expected!");
           }
         }
       }
       elems SQBR_R
       { if( elems_left[ dim_pos] != 0) {
           yyerror("fewer array elements than specified!");
         }
         dim_pos--;
       }
     | SQBR_L desc COLON arrays SQBR_R
       { if( elems_left[ dim_pos] != 0) {
           yyerror("fewer sub-arrays than specified!");
         }
         dim_pos--;
       }
    ;

elems: elems elem
       { if( elems_left[ dim_pos] == 0) {
           yyerror("more array elements than specified!");
         }
         elems_left[ dim_pos]--;
         array_pos++;
       } 
    | /* empty */
    ;

elem: NUM 
      { if( ! mode == int_mode) { 
          yyerror( "Unexpect integer read\n");
        }
        else {
          intarray[ array_pos]=$1;
        }
      }
    | DOUBLE  
      { if( ( ! mode == float_mode) &&
            ( ! mode == double_mode)) { 
          yyerror( "Unexpected floating point read\n");
        }
        if( mode == float_mode) {
          floatarray[ array_pos] = (float)$1;
        }
        if( mode == double_mode) { 
          doublearray[ array_pos] = $1;
        }
      }
    ;

desc: NUM COMMA NUM
      { dim_pos++;
        if( $1 > $3) {
          yyerror( "Lower bound is larger that upperbound in range!");
        }
        if( ! size_fixed) {
          dims++;
          shape[ dim_pos] = $3 - $1 + 1;
        }
        else {
          if( dim_pos >= dims) {
            yyerror( "array of lower dimensionality expected!");
          }
          if( shape[ dim_pos] != $3 - $1 + 1) {
            yyerror( "shape does not match specification!");
          }
        }
        elems_left[ dim_pos] = shape[ dim_pos];
      }
    ;


%%


void yyerror( char *msg)
{
  fprintf( stderr, "FIBRE error: line %d: \"%s\" : %s\n", linenum, yytext, msg);
  fprintf( stderr, "FIBRE error: document scan terminated!\n");
  exit(1);
}

