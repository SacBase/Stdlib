#ifndef _STDLIB_FILE_H_
#define _STDLIB_FILE_H_
/*
 *  implementation of class File
 */


#include <stdbool.h>
#include <stdio.h>

#include "sacinterface.h"

typedef char* string;
typedef FILE* File;

sac_int SACfopen(File* f, string name, string mode);
sac_int SACfclose(File f);
sac_int SACmkstemp(File* f_out, string template);
sac_int SACremove(string name);
sac_int SACfputc(unsigned char C, File f);
unsigned char SACfgetc(File f);
sac_int SACungetc(unsigned char c, File f);
sac_int SACfputs(string s, File f);
sac_int SACfgets(SACarg **str, sac_int size, File f);
void SACfprintf(File f, string format, ...);
sac_int SACfscanf(File f, string format, ...);
string SACfscans(File f, sac_int max);
string fscanl(File f, sac_int max);
bool SACfeof(File f);
sac_int SACflush(File f);
sac_int SACfseek(File f, sac_int offset, sac_int base);
sac_int SACftell(File f);
sac_int SACrewind(File f);

#endif /* _STDLIB_FILE_H_ */
