#include "samples/prototypes.h"
#include <string.h>

void *binsert(const void *key, void *base, size_t *p_nelem, size_t width, int (*compar)(const void *, const void *))
{
    if (*p_nelem == 0){
        *p_nelem += 1;
        return memmove(base, key, width);
    }
    void *found = NULL;
    void *start = base;
    for (size_t nremain = *p_nelem; nremain != 0; nremain >>= 1) {
        void *p = (char *)base + (nremain >> 1) * width;
        int sign = compar(key, p);
        if (sign == 0) {
            found = p;
            break;
        }
        if (sign > 0) {
            base = (char *)p + width;
            nremain--;
        }
    }

    if (found) {
        return found;
    } else {
        void *end = (char *)start + (*p_nelem - 1) * width;
        while (end >= base) {
            memmove((char *)end + width, end, width);
            end = (char *)end - width;
        }
        *p_nelem += 1;
        return memmove(base, key, width);
    }
    
}
