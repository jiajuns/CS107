#include "samples/prototypes.h"
#include <string.h>


void *binsert(const void *key, void *base, size_t *nel, size_t width, int (*cmp)(const void *, const void *))
{   
    if (*nel == 0)
    {
        *nel += 1;
        memmove(base, key, width);
        return base;
    }

    void *start = base;
    void *found = NULL;
    for (size_t nremain = *nel; nremain != 0; nremain >>= 1) {
        void *p = (char *)base + (nremain >> 1) * width;
        int sign = cmp(key, p);
        if (sign == 0)
        {
            found = p;
            break;
        }
        if (sign > 0) {  /* key > p: move right */
            base = (char *)p + width;
            nremain--;
        }       /* else move left */
    }

    if (found)
    {
        return found;
    } else {
        memmove((char *)base + width, base, width*(*nel)-((char *)base - (char *)start));
        *nel += 1;
        return memmove(base, key, width);
    }
}

