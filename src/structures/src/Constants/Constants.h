#ifndef STDLIB__CONSTANTS__H
#define STDLIB__CONSTANTS__H

#include "sacinterface.h"

//----------
#define minmax(rtype, SACtype, typeucase)	\
rtype max##SACtype( void );		\
rtype min##SACtype( void );		

#include "Constants.mac"
#undef minmax
//----------

sac_int maxint( void);
sac_int minint( void);
float minfloat( void);
float maxfloat( void);
double mindouble( void);
double maxdouble( void);
double tinydouble( void);
double epidouble( void);
sac_int randmax( void);

#endif // STDLIB__CONSTANTS__H
