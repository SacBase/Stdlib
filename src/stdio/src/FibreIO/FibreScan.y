%{

extern int linenum;
extern char yytext[];

#include <stdio.h>
#include "FibreScan.h"
/* sac.h unfortunately exports the following symbols, causing a redefinition
 * warning when import config.h, so undefine them to silence the warnings.
 */
#undef ARCH
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#include "../../../../config/config.h"


enum READMODE {
  byte_mode,
  short_mode,
  int_mode,
  long_mode,
  longlong_mode,
  ubyte_mode,
  ushort_mode,
  uint_mode,
  ulong_mode,
  ulonglong_mode,
  float_mode,
  double_mode,
  string_mode,
};

int     boolval;
char    byteval;
short   shortval;
int     intval;
long    longval;
long long    longlongval;
unsigned char    ubyteval;
unsigned short   ushortval;
unsigned int     uintval;
unsigned long    ulongval;
unsigned long long    ulonglongval;
float   floatval;
double  doubleval;
char    *stringval;
double  *doublearray;
float   *floatarray;
char    *bytearray;
short   *shortarray;
int     *intarray;
long    *longarray;
long long    *longlongarray;
unsigned char    *ubytearray;
unsigned short   *ushortarray;
unsigned int     *uintarray;
unsigned long    *ulongarray;
unsigned long long    *ulonglongarray;
char    **stringarray;

int i;
int shape[ MAXDIM];
int dim_pos;
enum READMODE mode;

int got_scalar;
int size_fixed;
int dims;
int size;
static int array_pos;
static int elems_left[MAXDIM];

%}


%union { char            cbyte;
         short           cshort;
         int             cint;
         long            clong;
         long long       clonglong;
         unsigned char   cubyte;
         unsigned short  cushort;
         unsigned int    cuint;
         unsigned long   culong;
         unsigned long long culonglong;
         int             cbool;
         char            cchar;
         float           cfloat;
         double          cdbl;
         char*           cstr;
         double*         cdbl_ptr;
         float*          cflt_ptr;
         char*           cbyte_ptr;
         short*          cshort_ptr;
         int*            cint_ptr;
         long*           clong_ptr;
         long long*      clonglong_ptr;
         unsigned char*  cubyte_ptr;
         unsigned short* cushort_ptr;
         unsigned int*   cuint_ptr;
         unsigned long*  culong_ptr;
         unsigned long long* culonglong_ptr;
         char**          cstr_ptr;
       }


%token PARSE_BOOL PARSE_FLOAT PARSE_DOUBLE PARSE_STRING
       PARSE_BYTE PARSE_SHORT PARSE_INT PARSE_LONG PARSE_LONGLONG
       PARSE_UBYTE PARSE_USHORT PARSE_UINT PARSE_ULONG PARSE_ULONGLONG
       PARSE_DOUBLE_ARRAY PARSE_FLOAT_ARRAY PARSE_STRING_ARRAY
       PARSE_BYTE_ARRAY PARSE_SHORT_ARRAY PARSE_INT_ARRAY PARSE_LONG_ARRAY
       PARSE_LONGLONG_ARRAY PARSE_UBYTE_ARRAY PARSE_USHORT_ARRAY 
       PARSE_UINT_ARRAY PARSE_ULONG_ARRAY PARSE_ULONGLONG_ARRAY
%token SQBR_L SQBR_R COLON COMMA TTRUE TFALSE
%token <cbyte>  NUMBYTE
%token <cshort> NUMSHORT
%token <cint>   NUM
%token <cint>   NUMINT
%token <clong>  NUMLONG
%token <clonglong> NUMLONGLONG
%token <cubyte>  NUMUBYTE
%token <cushort> NUMUSHORT
%token <cuint>   NUMUINT
%token <culong>  NUMULONG
%token <culonglong> NUMULONGLONG
%token <cfloat> FLOAT
%token <cdbl>   DOUBLE
%token <cchar>  CHAR
%token <cstr>   STRING

%type <cbool> bool
%type <cint_ptr> array


%start file


%{

/*
 * Make sure, the stack of the generated parser is big enough!
 */
#define YYMAXDEPTH 1000000

%}


%%


file: PARSE_BOOL bool 
         {boolval = $2; return(0);}
    | PARSE_BYTE  NUMBYTE 
         {byteval = $2; return(0);} 
    | PARSE_SHORT  NUMSHORT 
         {shortval = $2; return(0);} 
    | PARSE_INT  NUM 
         {intval = $2; return(0);} 
    | PARSE_LONG  NUMLONG 
         {longval = $2; return(0);} 
    | PARSE_LONGLONG  NUMLONGLONG 
         {longlongval = $2; return(0);} 
    | PARSE_UBYTE  NUMUBYTE 
         {ubyteval = $2; return(0);} 
    | PARSE_USHORT  NUMUSHORT 
         {ushortval = $2; return(0);} 
    | PARSE_UINT  NUMUINT 
         {uintval = $2; return(0);} 
    | PARSE_ULONG  NUMULONG 
         {ulongval = $2; return(0);} 
    | PARSE_ULONGLONG  NUMULONGLONG 
         {ulonglongval = $2; return(0);} 
    | PARSE_FLOAT FLOAT 
         {floatval = $2; return(0);}
    | PARSE_STRING STRING 
         {stringval = $2; return(0);}
    | PARSE_DOUBLE DOUBLE 
         {doubleval = $2; return(0);}
    | PARSE_DOUBLE_ARRAY 
         {got_scalar = 0; mode = double_mode;} 
         parse_array 
         {return(0);}
    | PARSE_FLOAT_ARRAY 
         {got_scalar = 0; mode = float_mode;} 
         parse_array 
         {return(0);}
    | PARSE_BYTE_ARRAY 
         {got_scalar = 0; mode = byte_mode;} 
         parse_array 
         {return(0);}
    | PARSE_SHORT_ARRAY 
         {got_scalar = 0; mode = short_mode;} 
         parse_array 
         {return(0);}
    | PARSE_INT_ARRAY 
         {got_scalar = 0; mode = int_mode;} 
         parse_array 
         {return(0);}
    | PARSE_LONG_ARRAY 
         {got_scalar = 0; mode = long_mode;} 
         parse_array 
         {return(0);}
    | PARSE_LONGLONG_ARRAY 
         {got_scalar = 0; mode = longlong_mode;} 
         parse_array 
         {return(0);}
    | PARSE_UBYTE_ARRAY 
         {got_scalar = 0; mode = ubyte_mode;} 
         parse_array 
         {return(0);}
    | PARSE_USHORT_ARRAY 
         {got_scalar = 0; mode = ushort_mode;} 
         parse_array 
         {return(0);}
    | PARSE_UINT_ARRAY 
         {got_scalar = 0; mode = uint_mode;} 
         parse_array 
         {return(0);}
    | PARSE_ULONG_ARRAY 
         {got_scalar = 0; mode = ulong_mode;} 
         parse_array 
         {return(0);}
    | PARSE_ULONGLONG_ARRAY 
         {got_scalar = 0; mode = ulonglong_mode;} 
         parse_array 
         {return(0);}
    | PARSE_STRING_ARRAY 
         {got_scalar = 0; mode = string_mode;} 
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
                { if( mode == double_mode) {
                    doublearray = (double *) SAC_MALLOC( sizeof( double));
                    *doublearray = $1;
                  }
                  else if( ! mode == int_mode) { 
                    yyerror( "Read integer but expected a floating point number!");
                  }
                  else {
                    intarray = (int *) SAC_MALLOC( sizeof( int));
                    *intarray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMBYTE
                { if( ! mode == byte_mode) { 
                    yyerror( "byte numeric expected!");
                  }
                  else {
                    bytearray = (char *) SAC_MALLOC( sizeof( char));
                    *bytearray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMSHORT
                { if( ! mode == short_mode) { 
                    yyerror( "short numeric expected!");
                  }
                  else {
                    shortarray = (short *) SAC_MALLOC( sizeof( short));
                    *shortarray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMLONG
                { if( ! mode == long_mode) { 
                    yyerror( "long numeric expected!");
                  }
                  else {
                    longarray = (long *) SAC_MALLOC( sizeof( long));
                    *longarray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMLONGLONG
                { if( ! mode == longlong_mode) { 
                    yyerror( "longlong numeric expected!");
                  }
                  else {
                    longlongarray = 
		    (long long*) SAC_MALLOC( sizeof( long long));
                    *longlongarray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMUBYTE
                { if( ! mode == ubyte_mode) { 
                    yyerror( "ubyte numeric expected!");
                  }
                  else {
                    ubytearray = 
		    (unsigned char *) SAC_MALLOC( sizeof( unsigned char));
                    *ubytearray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMUSHORT
                { if( ! mode == ushort_mode) { 
                    yyerror( "ushort numeric expected!");
                  }
                  else {
                    ushortarray = 
		    (unsigned short *) SAC_MALLOC( sizeof( unsigned short));
                    *ushortarray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMUINT
                { if( ! mode == uint_mode) { 
                    yyerror( "uint numeric expected!");
                  }
                  else {
                    uintarray = 
		    (unsigned int *) SAC_MALLOC( sizeof( unsigned int));
                    *uintarray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMULONG
                { if( ! mode == ulong_mode) { 
                    yyerror( "ulong numeric expected!");
                  }
                  else {
                    ulongarray = 
		    (unsigned long *) SAC_MALLOC( sizeof( unsigned long));
                    *ulongarray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | NUMULONGLONG
                { if( ! mode == ulonglong_mode) { 
                    yyerror( "ulonglong numeric expected!");
                  }
                  else {
                    ulonglongarray = (unsigned long long*) 
		    SAC_MALLOC( sizeof( unsigned long long));
                    *ulonglongarray = $1;
                  }
                 got_scalar = 1; 
                 dims = 0;
                 size = 1;
                }
            | DOUBLE
                {if( ( ! mode == float_mode) &&
                     ( ! mode == double_mode)) { 
                   yyerror( "Unexpected floating point read!\n");
                 }
                 got_scalar = 1; 
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
                       "Incorrectly parsed double where int was expected");
                     break;
                   case string_mode:
                     yyerror( 
                       "Incorrectly parsed double where string was expected");
                     break;
                   default:
                     yyerror( 
                       "Incorrectly parsed double where numeric was expected");
                     break;
                 }
               }
              | STRING
                { if( ! mode == string_mode)  {
                   yyerror( "Unexpected string read!\n");
                  }
                  got_scalar = 1;
                  switch( mode) {
                    case string_mode:
                      stringarray = (char **) SAC_MALLOC( sizeof( char*));
                      stringarray[0] = (char*)$1;
                      dims = 0;
                      size = 1;
                      break;
                   case int_mode:
                     yyerror( 
                       "Incorrectly parsed string where int was expected");
                     break;
                   case double_mode:
                     yyerror( 
                       "Incorrectly parsed string where double was expected");
                     break;
                   case float_mode:
                     yyerror( 
                       "Incorrectly parsed string where float was expected");
                     break;
                   default:
                     yyerror( 
                       "Incorrectly parsed double where numeric was expected");
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
             case byte_mode:
               bytearray = (char *) SAC_MALLOC( size * sizeof( char));
               break;
             case short_mode:
               shortarray = (short *) SAC_MALLOC( size * sizeof( short));
               break;
             case int_mode:
               intarray = (int *) SAC_MALLOC( size * sizeof( int));
               break;
             case long_mode:
               longarray = (long *) SAC_MALLOC( size * sizeof( long));
               break;
             case longlong_mode:
               longlongarray = (long long *) 
	       SAC_MALLOC( size * sizeof( long long));
               break;
             case ubyte_mode:
               ubytearray = (unsigned char *) 
	       SAC_MALLOC( size * sizeof( unsigned char));
               break;
             case ushort_mode:
               ushortarray = (unsigned short *) 
	       SAC_MALLOC( size * sizeof( unsigned short));
               break;
             case uint_mode:
               uintarray = (unsigned int *) 
	       SAC_MALLOC( size * sizeof( unsigned int));
               break;
             case ulong_mode:
               ulongarray = (unsigned long *) 
	       SAC_MALLOC( size * sizeof( unsigned long));
               break;
             case ulonglong_mode:
               ulonglongarray = (unsigned long long *) 
	       SAC_MALLOC( size * sizeof( unsigned long long));
               break;
             case float_mode:
               floatarray = (float *) SAC_MALLOC( size * sizeof( float));
               break;
             case double_mode:
               doublearray = (double *) SAC_MALLOC( size * sizeof( double));
               break;
             case string_mode:
               stringarray = (char **) SAC_MALLOC( size * sizeof( char*));
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
      { if( mode == double_mode) { 
          doublearray[ array_pos]= (double)$1;
        }
        else if( mode == int_mode){
          intarray[ array_pos]=$1;
        }
        else {
          yyerror("Unexpected Integer read");
        }
      }
    | NUMBYTE
	{ if( ! mode == byte_mode) { 
	    yyerror( "byte array element expected!");
	  }
	  else {
	    bytearray[ array_pos]=$1;
	  }
	}
    | NUMSHORT
	{ if( ! mode == short_mode) { 
	    yyerror( "short array element expected!");
	  }
	  else {
	    shortarray[ array_pos]=$1;
	  }
	}
    | NUMLONG
	{ if( ! mode == long_mode) { 
	    yyerror( "long array element expected!");
	  }
	  else {
	    longarray[ array_pos]=$1;
	  }
	}
    | NUMLONGLONG
	{ if( ! mode == longlong_mode) { 
	    yyerror( "longlong array element expected!");
	  }
	  else {
	    longlongarray[ array_pos]=$1;
	  }
	}
    | NUMUBYTE
	{ if( ! mode == ubyte_mode) { 
	    yyerror( "ubyte array element expected!");
	  }
	  else {
	    ubytearray[ array_pos]=$1;
	  }
	}
    | NUMUSHORT
	{ if( ! mode == ushort_mode) { 
	    yyerror( "ushort array element expected!");
	  }
	  else {
	    ushortarray[ array_pos]=$1;
	  }
	}
    | NUMUINT
	{ if( ! mode == uint_mode) { 
	    yyerror( "uint array element expected!");
	  }
	  else {
	    uintarray[ array_pos]=$1;
	  }
	}
    | NUMULONG
	{ if( ! mode == ulong_mode) { 
	    yyerror( "ulong array element expected!");
	  }
	  else {
	    ulongarray[ array_pos]=$1;
	  }
	}
    | NUMULONGLONG
	{ if( ! mode == ulonglong_mode) { 
	    yyerror( "ulonglong array element expected!");
	  }
	  else {
	    ulonglongarray[ array_pos]=$1;
	  }
	}
    | DOUBLE  
      { if( mode == float_mode) {
          floatarray[ array_pos] = (float)$1;
        }
        else if( mode == double_mode) { 
          doublearray[ array_pos] = $1;
        }
        else {
          yyerror( "Unexpected floating point read\n");
        }
      }
    | STRING  
      { if( mode == string_mode) {
          stringarray[ array_pos] = $1;
        }
        else {
          yyerror( "Unexpected string read\n");
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

