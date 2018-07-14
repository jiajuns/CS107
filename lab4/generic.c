#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int cmp_ptr(const void *p, const void *q)
{
    return (const char *)p - (const char *)q;
}

int cmp_int(const void *p, const void *q)
{
    return *(const int *)p - *(const int *)q;
}

int cmp_char(const void *p, const void *q)
{
    return *(const unsigned char *)p - *(const unsigned char *)q;
}

int cmp_first_char(const void *p, const void *q)
{
    return **(const char **)p - **(const char **)q;
}

int cmp_asymmetric(const void *p, const void *q)
{
    return *(const char *)p - **(const char **)q;
}

void *gfind_max(void *arr, int n, size_t elemsz, int (*compar)(const void *, const void *))
{
    void *pmax = arr;
    for (int i = 1; i < n; i++) {
        void *ith = (char *)arr + i*elemsz;
        if (compar(ith, pmax) > 0)
            pmax = ith;
    }
    return pmax;
}

void test_max()
{
    int nums[] = {0x11440022, 0xff77ff, 0x9};
    int n = sizeof(nums)/sizeof(nums[0]);

    int max = *(int *)gfind_max(nums, n, sizeof(nums[0]), cmp_int);
    printf("correct call max = %#x\n", max); //0x11440022

    max = *(int *)gfind_max(nums, n, sizeof(nums[0]), cmp_char);
    printf("incorrect call #1 max = %#x\n", max); // 0xff77ff
    // memery store 4-byte int in a reverse order
    // compare {0x22004411, 0xff77ff00, 0x90000000} => {0x22, 0xff, 0x90}

    max = *(int *)gfind_max(nums, n, 1, cmp_int);
    printf("incorrect call #2 max = %#x\n", max); //0x77ff1144
    // every element move 1 byte ahead / 2 dights in hex 
    // compare {0x11440022, 0xff114400, 0x77ff1144} sign {+, -, +}

    max = *(int *)gfind_max(nums, n, sizeof(nums[0]), cmp_ptr);
    printf("incorrect call #3 max = %#x\n", max); // 0x9
    // compare memory address, later in array the bigger.
}

void test_bsearch(void)
{
    char *words[] = {"red", "blue", "green", "yellow"};
    int n = sizeof(words)/sizeof(*words);
    char *key = "g";

    // sort and search should use same comparision function, why are they not here?
    qsort(words, n, sizeof(words[0]), cmp_first_char);  // sort // words[0] is memory address, sizeof(words[0]) = 8
    printf("\nSorted by first letter: ");
    for (int i = 0; i < n; i++) printf("%s ", words[i]);
    printf("\nLooking for a word that starts with %s: ", key);
    char **found = bsearch(key, words, n, sizeof(words[0]), cmp_asymmetric); // search
    printf("found %s\n", found ? *found : "none");
}


int main(int argc, char *argv[])
{
    test_max();
    test_bsearch();
    return 0;
}
