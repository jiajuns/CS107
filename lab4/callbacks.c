#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int int_cmpfn(const void *a, const void *b)
{
    int first  = *(const int *)a;
    int second = *(const int *)b;

    if (first < second) return -1;
    else if (first > second) return 1;
    else return 0;
}

struct city {
    char *name;
    int zipcode;
};


int city_cmpbyname(const void *a, const void *b)
{
    const struct city *first  = (const struct city *)a;
    const struct city *second = (const struct city *)b;

    return strcmp(first->name, second->name);
}

int city_cmpbyzip(const void *a, const void *b)
{
    const struct city *first  = (const struct city *)a;
    const struct city *second = (const struct city *)b;

    return first->zipcode - second->zipcode;
}

int string_cmpfn(const void *a, const void *b)
{
    const char *first  = *(const char **)a;
    const char *second = *(const char **)b;

    return strcmp(first, second);
}

int letter_cmpfn(const void *a, const void *b)
{
    unsigned char first  = *(const char *)a;
    unsigned char second = *(const char *)b;

    return first - second;
}

int main(int argc, char *argv[])
{
    int scores[] = {80, 72, 74, 85, 79, 81};
    int nscores = sizeof(scores)/sizeof(scores[0]);
    qsort(scores, nscores, sizeof(scores[0]), int_cmpfn);
    printf("\nSort integers: ");
    for (int i = 0; i < nscores; i++) printf("%d ", scores[i]);

    struct city cities[] = {{"Stanford", 94305}, {"Seattle", 98144}, {"Stevinson", 95374}, {"Seattle", 98101}};
    int ncities = sizeof(cities)/sizeof(cities[0]);
    printf("\nSort structs by name: ");
    qsort(cities, ncities, sizeof(cities[0]), city_cmpbyname);
    for (int i = 0; i < ncities; i++) printf("{%s,%d} ", cities[i].name, cities[i].zipcode);
    printf("\nSort structs by zip: ");
    qsort(cities, ncities, sizeof(cities[0]), city_cmpbyzip);
    for (int i = 0; i < ncities; i++) printf("{%s,%d} ", cities[i].name, cities[i].zipcode);

    char *words[] = {"cherry", "apple", "banana", "peach", "pear", "kiwi"};
    int nwords = sizeof(words)/sizeof(words[0]);
    printf("\nSort strings: ");
    qsort(words, nwords, sizeof(words[0]), string_cmpfn);
    for (int i = 0; i < nwords; i++) printf("%s ", words[i]);

    return 0;
}
