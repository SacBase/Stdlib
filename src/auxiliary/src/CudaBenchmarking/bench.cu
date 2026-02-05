#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

extern "C" {

#include <stdarg.h>
#include <sacinterface.h>
#include <string.h>
#include <time.h>
#include <cuda.h>

#define SECONDS 0
#define MILLIS 1
#define MICROS 2
#define NANOS 3

static const char * unitName[] = {"s", "ms", "us", "ns"};

struct cudabench {                                                   
  sac_int                num;
  char *             name;
  sac_int                timeUnit;
  cudaEvent_t        start;
  cudaEvent_t        stop;
};

void benchStart( struct cudabench *interval)
{                                                            
  cudaEventCreate(&(interval->start));
  cudaEventRecord(interval->start);
}                                                                        
                                                                         
void benchEnd( struct cudabench* interval)
{                                                            
  cudaEventCreate(&(interval->stop));
  cudaEventRecord(interval->stop);
}                         
                                               
void benchThis( void)
{                                                                        
  /* noop*/
}                                                                        

double benchRes( struct cudabench* interval)
{
  cudaEventSynchronize(interval->stop);
  float milliseconds = 0;
  cudaEventElapsedTime(&milliseconds, interval->start, interval->stop);
  return (double)milliseconds / 1e3;
}

char* benchName( struct cudabench* interval)
{
  size_t len = strlen(interval->name) + 1;
  char* newName = (char *)malloc(len);
  memcpy(newName, interval->name, len);
  return( newName);
}

sac_int benchNum( struct cudabench* interval)
{
  return( interval->num);
}

char* benchUnitName( struct cudabench* interval)
{
  size_t len = strlen( unitName[interval->timeUnit]) + 1;
  char* unit_name = (char *)malloc(len);
  memcpy( unit_name, unitName[interval->timeUnit], len);
  return( unit_name);
}

sac_int benchUnit( struct cudabench* interval)
{
  return( interval->timeUnit);
}

void benchCreate( struct cudabench** interval)                                                
{                                                                        
  /* benchGetInterval actually creates the data structure */
}     

struct cudabench* benchGetInterval_si(const char * name, sac_int num)
{                                                                        
  struct cudabench *interval;
  char* newName;
  interval = (struct cudabench*)malloc( sizeof( struct cudabench));
  interval->num = num;                                    
  newName = (char *)malloc( strlen( name) + 1);
  memcpy( newName, name, strlen( name) + 1);
  interval->name = newName;
  interval->timeUnit = SECONDS;
  return( interval);
}                                                                        
 
struct cudabench* benchGetInterval_i( sac_int num)               
{                                                                        
  struct cudabench *interval;
  interval = benchGetInterval_si("\0", num);
  return( interval);
}                                                                        

struct cudabench* benchGetInterval_s(const char *name)
{                                                                        
  struct cudabench *interval;
  interval = benchGetInterval_si(name, -1);
  return( interval);
}                                                                        

struct cudabench* benchGetInterval_siu(const char * name, sac_int num, sac_int timeunit)
{                                                                        
  struct cudabench *interval;
  char* newName;
  interval = (struct cudabench*)malloc( sizeof( struct cudabench));
  interval->num = num;                                    
  newName = (char *)malloc( strlen( name) + 1);
  memcpy( newName, name, strlen( name) + 1);
  interval->name = newName;
  interval->timeUnit = timeunit;
  return( interval);
}                                                                        

struct cudabench* benchGetInterval_iu( sac_int num, sac_int timeunit)               
{                                                                        
  struct cudabench *interval;
  interval = benchGetInterval_siu("\0", num, timeunit);
  return( interval);
}                                                                        

struct cudabench* benchGetInterval_su(const char *name, sac_int timeunit)
{                                                                        
  struct cudabench *interval;
  interval = benchGetInterval_siu(name, -1, timeunit);
  return( interval);
}                                                                        
                                                                         
void benchDestroyInterval( struct cudabench *interval)                        
{                                                                        
  cudaEventDestroy(interval->start);
  cudaEventDestroy(interval->stop);
  free(interval->name);
  free(interval);                                                        
}                            
                                            
}
