/*
 *  Implementation of SAC standard module List
 */


#include <stdio.h>
#include <stdlib.h>

#include "icm2c.h"
#include "libsac.h"



#define TRACE 0


typedef struct LIST {
  int         elem;
  struct LIST *rest;
  int         rc;
} list;


