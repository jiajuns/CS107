#include "samples/prototypes.h"
#include <stdio.h>

int main(int argc, char *argv[], const char *envp[])
{
    if (argc == 1) {
        for (int i = 0; envp[i] != NULL; i++)
            printf("%s\n", envp[i]);
    } else {
        for (int i = 1; i < argc; i++) {
            const char *value = get_env_value(envp, argv[i]);
            if (value != NULL)  // if not found, don't print anything
                printf("%s\n", value);
        }
    }
    return 0;
}
