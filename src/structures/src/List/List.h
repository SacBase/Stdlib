#ifndef _SAC_LIST_H_
#define _SAC_LIST_H_

/*
 * Implementation of SAC standard module List.
 * Do not try to touch this, it will fuck with your mind.
 * If you decide to go ahead anyway, good luck.
 * Nil = NULL inside the SACarg :)
 */

#include <stdbool.h>

#include "sacinterface.h"

extern SACtypes* SACTYPE__LIST__list;

typedef struct LIST {
    sac_int elem;
    SACarg* cons;
} list;

list *SAClistcopy(list *lst);
list *SAClistfree(list *lst);

list *SAClistnil(void);
list *SAClistcons(sac_int elem, list *cons);
sac_int SAClisthead(list *lst);
SACarg* SAClisttail(list *lst);
bool SAClistempty(list *lst);
SACarg* SAClistappend(SACarg* sa, SACarg* sb);
sac_int SAClistnth(sac_int n, list *lst);
sac_int SAClistlength(list *lst);
SACarg* SAClistdrop(sac_int n, SACarg* slst_old);
list *SAClisttake(sac_int n, list *lst);

#endif /* _SAC_LIST_H_ */
