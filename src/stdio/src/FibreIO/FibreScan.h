/*
 *  Implementation of standard module FibreScan
 */


#include <stdlib.h>
#include <stdio.h>

#include "sac.h"


#define yyFlexLexer FibreScanFlexLexer
#define yy_create_buffer FibreScan_create_buffer
#define yy_delete_buffer FibreScan_delete_buffer
#define yy_flex_debug FibreScan_flex_debug
#define yy_init_buffer FibreScan_init_buffer
#define yy_load_buffer_state FibreScan_load_buffer_state
#define yy_switch_to_buffer FibreScan_switch_to_buffer
#define yyin FibreScanin
#define yy_scan_string FibreScan_scan_string
#define yyleng FibreScanleng
#define yylex FibreScanlex
#define yyout FibreScanout
#define yyrestart FibreScanrestart
#define yytext FibreScantext
#define yywrap FibreScanwrap

#define yyparse FibreScanparse
#define yyerror FibreScanerror
#define yylval FibreScanlval
#define yychar FibreScanchar
#define yydebug FibreScandebug
#define yynerrs FibreScannerrs




#define MAXDIM 10

extern int linenum;

extern int yyparse();
extern int yy_scan_string( char*);
extern void yyerror(char *);

extern char *yytext;

extern FILE *yyin;
extern int start_token;
extern int FibreScanlex();

extern int boolval;
extern int intval;
extern float floatval;
extern double doubleval;
extern char *stringval;
extern double *doublearray;
extern float *floatarray;
extern int *intarray;
extern char **stringarray;

extern int got_scaler;
extern int size;
extern int dims;
extern int shape[ MAXDIM];

