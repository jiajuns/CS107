#include "samples/prototypes.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


// int main(int argc, char *argv[], const char *envp[])
// {
//     // envp is array of key-value pairs of environmet vairiables
//     // get the value of MYPATH vairable. if doesn't exist, search for PATH
//     const char *searchpath = get_env_value(envp, "MYPATH");
//     if (searchpath == NULL) searchpath = get_env_value(envp, "PATH");
    
//     // PATH_MAX: Maximum number of bytes in a pathname, including the terminating null character.
//     char dir[PATH_MAX];
    
//     if (argc == 1) {        
//         const char *remaining = searchpath;
//         printf("Directories in search path:\n");
//         // tokenize the searchpath by ":"
//         while (scan_token(&remaining, ":", dir, sizeof(dir))) {
//             printf("%s\n", dir);
//         } 
//     } else {
//         for (int i = 1; i < argc; i++) {
//             const char *remain = searchpath;
//             const char *program = argv[i];
//             // search through all paths in MYPATH/PATH
//             while (scan_token(&remain, ":", dir, sizeof(dir))) {
//                 // concat dir and program to make full path
//                 // sprintf(dir, "%s/%s", program);
//                 strcat(dir, "/");
//                 strcat(dir, program);
//                 // if the fullpath can be read and executed, print that path
//                 if (access(dir, R_OK) == 0 && access(dir, X_OK) == 0) {
//                     printf("%s\n", dir);
//                     break;
//                 }
//             }    
//         }
//     }
//     return 0;
// }


int main(int argc, char *argv[], const char *envp[])
{
    const char *searchpath = get_env_value(envp, "MYPATH");
    if (searchpath == NULL) searchpath = get_env_value(envp, "PATH");

    char dir[PATH_MAX];

    // print out the path
    if (argc == 1)
    {   
        printf(" Directories in search path: \n");
        while (scan_token(&searchpath, ":", dir, sizeof(dir))) 
        {
            printf("%s\n", dir);
        }
    } else {
        for (int i = 1; i < argc; i++)
        {
            while (scan_token(&searchpath, ":", dir, sizeof(dir)))
            {
                strcat(dir, "/");
                strcat(dir, argv[i]);
                if ((access(dir, R_OK) == 0) && (access(dir, X_OK) == 0))
                {
                    printf("%s\n", dir);
                    break;
                }
            }
        }
    }
    return 0;
}