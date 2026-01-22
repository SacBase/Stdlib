/*
 *  Implementation of SAC standard module List
 */


#include <stddef.h>
#include <stdlib.h>
#include "List.h"

list* SAClistcopy (list* lst)
{
    if (lst == NULL) return NULL;

    list* cpy = malloc(sizeof(list));
    cpy->elem = lst->elem;
    cpy->cons = SACARGduplicateSaCArray(lst->cons);
    return cpy;
}

list* SAClistfree (list* lst)
{
    if (lst == NULL) return NULL;

    // Check whether this triggers a refcount decrease
    SACARGdeleteSacArray(&(lst->cons));
    free (lst);
    return NULL;
}

// n = 0 for unlimited
// Last element will not have cons initialized!
void deepcopy(list** out_root, list** out_last, const list* lst, sac_int n)
{
    *out_root = malloc(sizeof(list));
    *out_last = *out_root;
    (*out_last)->elem = lst->elem;
    n--;
    while (n != 0)
    {
        lst = SACARGgetSharedData(SACTYPE__LIST__list, lst->cons);
        if (lst == NULL && n > 0) 
            SAC_RuntimeError("Nth element outside of list");
        if (lst == NULL) break;
        list* next = malloc(sizeof(list));
        (*out_last)->cons = SACARGcreateFromPointer(SACTYPE__LIST__list, next, 0, NULL);
        *out_last = next;
        (*out_last)->elem = lst->elem;
        n--;
    }
}



list* SAClistnil ()
{
    return NULL;
}

list* SAClistcons (sac_int elem, list* cons)
{
    list* res = malloc(sizeof(list));
    res->elem = elem;
    res->cons = SACARGduplicateSaCArray(cons->cons);
    return res;
}

sac_int SAClisthead (list* lst)
{
    if (lst == NULL)
        SAC_RuntimeError ("Tried to get head of empty list");
    return lst->elem;
}

SACarg* SAClisttail (list* lst)
{
    if (lst == NULL)
        SAC_RuntimeError ("Tried to get tail of empty list");
    return SACARGduplicateSaCArray(lst->cons);
}

bool SAClistempty (list* lst)
{
    return lst != NULL;
}

SACarg* SAClistappend (SACarg* sa, SACarg* sb)
{
    const list* a = SACARGgetSharedData(SACTYPE__LIST__list, sa);
    if (a == NULL)
    {
        SACARGdeleteSacArray(&sa);
        return sb;
    }

    list* res = NULL;
    list* taila = NULL;
    deepcopy(&res, &taila, a, 0);
    taila->cons = sb;

    SACarg* sres = SACARGcreateFromPointer(SACTYPE__LIST__list, res, 0, NULL);

    return sres;
}

sac_int SAClistnth (sac_int n, list* lstnc)
{
    const list* lst = lstnc;
    if (n < 0)
        SAC_RuntimeError("Cannot get negative nth element of list");

    while (lst != NULL)
    {
        if (n == 0)
            return lst->elem;
        n--;
        lst = SACARGgetSharedData(SACTYPE__LIST__list, lst->cons);
    }

    SAC_RuntimeError("Nth element outside of list");
    return 0;
}

sac_int SAClistlength (list* lstnc) 
{
    const list* lst = lstnc;
    sac_int length = 0;
    while (lst != NULL)
    {
        length++;
        lst = SACARGgetSharedData(SACTYPE__LIST__list, lst->cons);
    }
    return length;
}

SACarg* SAClistdrop(sac_int n, SACarg* slst_old)
{
    if (n < 0)
        SAC_RuntimeError("Cannot get negative nth element of list");

    SACarg* slst = SACARGduplicateSaCArray(slst_old);

    while (true)
    {
        if (n == 0) break;
        slst = ((list*)SACARGgetSharedData(SACTYPE__LIST__list, slst))->cons;
        n--;
    }

    if (n > 0)
        SAC_RuntimeError("Nth element outside of list");

    SACARGdeleteSacArray(&slst_old);
    return slst;
}

list* SAClisttake(sac_int n, list* lst)
{
    if (n == 0) return NULL;
    if (n < 0)
        SAC_RuntimeError("Cannot get a negative amount of elements from a list");

    list* res = NULL;
    list* taila = NULL;
    deepcopy(&res, &taila, lst, n);
    taila -> cons = SACARGcreateFromPointer(SACTYPE__LIST__list, NULL, 0, NULL);

    return res;
}