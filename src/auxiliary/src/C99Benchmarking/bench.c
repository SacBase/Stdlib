#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "sac.h"


struct bench {                                                   
  int                num; 
  char *             name;
  double             startSec;
  double             stopSec;
};
                                                             

void benchStart( struct bench *interval, double time) 
{                                                            
  interval->startSec = time;
}                                                                        
                                                                         
void benchEnd( struct bench* interval, double time)                                   
{                                                            
  interval->stopSec = time;
}                         
                                               
void benchThis( )                                                        
{                                                                        
  /* noop*/
}                                                                        

double benchRes( struct bench* interval)
{
  return( interval->stopSec - interval->startSec);
}

char* benchName( struct bench* interval)
{
  char* newName = SAC_MALLOC( strlen( interval->name) + 1);
  strncpy( newName, interval->name, strlen( interval->name) + 1);
  return( newName);
}

int benchNum( struct bench* interval)
{
  return( interval->num);
}

void benchCreate( struct bench** interval)                                                
{                                                                        
  /* benchGetInterval actually creates the data structure */
}     
 
struct bench* benchGetInterval_i( int num)               
{                                                                        
  struct bench *interval;
  interval = (struct bench*)SAC_MALLOC( sizeof( struct bench));
  interval->num = num;
  interval->name = (char*)SAC_MALLOC( sizeof( char));
  *(interval->name) = '\0';
  return( interval);
}                                                                        

struct bench* benchGetInterval_s( char *name) 
{                                                                        
  struct bench *interval;
  char* newName;
  interval = (struct bench*)SAC_MALLOC( sizeof( struct bench));
  interval->num = -1;
  newName = SAC_MALLOC( strlen( name) + 1);
  strncpy( newName, name, strlen( name) + 1);
  interval->name = newName;
  return( interval);
}                                                                        

struct bench* benchGetInterval_si(char * name, int num)
{                                                                        
  struct bench *interval;
  char* newName;
  interval = (struct bench*)SAC_MALLOC( sizeof( struct bench));
  interval->num = num;                                    
  newName = SAC_MALLOC( strlen( name) + 1);
  strncpy( newName, name, strlen( name) + 1);
  interval->name = newName;
  return( interval);
}                                                                        
                                                                         
void benchDestroyInterval( struct bench *interval)                        
{                                                                        
  free(interval->name);
  free(interval);                                                        
}                            
                                            
