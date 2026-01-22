/*
 *  Implementation of SAC standard module List
 */


#include <stddef.h>
#include "List.h"

list* SAClistcopy (list* lst)
{
    if (lst == NULL) return NULL;

    list* cpy = malloc(sizeof(list));
    cpy->elem = lst->elem;
    cpy->cons = SACARGduplicateSaCArray(lst->cons);
}

void SAClistfree (list* lst)
{
    if (lst == NULL) return;

    // Check whether this triggers a refcount decrease
    SACARGdeleteSacArray(lst->cons);
    free (lst);
}



list* SAClistnil ()
{
    return NULL;
}

list* SAClistcons (sac_int elem, list* cons)
{
    list* res = malloc(sizeof(list));
    res->elem = elem;
    res->cons = SACARGduplicateSaCArray(cons);
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
    list* a = SACARGgetSharedData(SACTYPE__LIST_list, sa);
    if (a == NULL)
    {
        SACARGdeleteSacArray(sa);
        return sb;
    }

    list* child;
    while (true)
    {
        child = SACARGgetSharedData(SACTYPE__LIST__list, a->cons);
        if (child == NULL) break;
        a = child;
    }

    SACARGdeleteSacArray(a->cons);
    a->cons = sb;
    return sa;
}

sac_int SAClistnth (sac_int n, list* lst)
{
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
}

sac_int SAClistlength (list* lst) {
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
        slst = ((list*)SACARGgetSharedData(SACTYPE_LIST_list, slst))->cons;
        n--;
    }

    if (n > 0)
        SAC_RuntimeError("Nth element outside of list");

    SACARGdeleteSacArray(slst_old);
    return slst;
}

list* SAClisttake(sac_int n, list* lst)
{
    if (n == 0) return NULL;
    if (n < 0)
        SAC_RuntimeError("Cannot get a negative amount of elements from a list");

    list* result = malloc(sizeof(list));
    list* builder = result;

    while (true)
    {
        builder-> elem = lst->elem;
        lst = SACARGgetSharedData(SACTYPE__LIST__list, lst->cons);
        n --;
        if (n == 0) break;
        if (lst == NULL) 
            SAC_RuntimeError("Nth element outside of list");
        list* next = malloc(sizeof(list));
        builder->cons = SACARGcreateFromPointer(SACTYPE__LIST__list, next, 0);
        builder = next;
    }
    builder->cons = SACARGcreateFromPointer(SACTYPE__LIST__list, NULL, 0);
    return result;
}