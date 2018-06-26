#include "samples/prototypes.h"
#include <stdio.h>
#include <string.h>

// What cases does this test? Trace the code and find out!
static int fixed_test(void)
{
    const char *input = "hip-po-pot-a-mus gir-affe e-le-phant kang-a-roo rhi-no-ce-ros";
    char word[100], sub[10];

    while (scan_token(&input, " ", word, sizeof(word))) { //the delimiter takes pointer char, why it can still pass a string
        int nsyll = 0;
        const char *next = word;
        while (scan_token(&next, "-", sub, sizeof(sub))) {
            printf("%s", sub);
            nsyll++;
        }
        int nlett = 0;
        next = word;
        while (scan_token(&next, "-", sub, 2)) nlett++;
        printf(" (%d syllables, %d letters)\n", nsyll, nlett);
    }
    return 0;
}


int main(int argc, char *argv[])
{
    if (argc < 3) return fixed_test();

    const char *delim = argv[1];
    const char *input = argv[2];

    char buf[strlen(input)+1];
    const char *remaining = input;
    printf("Tokenized: { ");
    while (scan_token(&remaining, delim, buf, sizeof(buf)))
        printf("\"%s\" ", buf);
    printf("}\n");

    return 0;
}
