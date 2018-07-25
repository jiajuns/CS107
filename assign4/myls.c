#include <dirent.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum { SORT_BY_NAME, SORT_BY_TYPE };
enum { EXCLUDE_DOT, INCLUDE_DOT };

// On the myth filesystem, the only file type information that is accurate is
// directory/not-directory. Other type info in struct direct is not reliable.
bool is_dir(const struct dirent *d)
{
    return d->d_type == DT_DIR;
}

int sel_all(const struct dirent *d)
{
    return 1;
}

int sel_nodot(const struct dirent *d)
{
    if (d->d_name[0] == '.') {
        return 0;
    } else {
        return 1;
    }
}

int cmp_name(const struct dirent **d1, const struct dirent **d2)
{
    return strcmp((*d1)->d_name, (*d2)->d_name);
}

int cmp_type(const struct dirent **d1, const struct dirent **d2)
{
    if (is_dir(*d1) && !is_dir(*d2)) {
        return -1;
    } else if (!is_dir(*d1) && is_dir(*d2)) {
        return 1;
    } else {
        return strcmp((*d1)->d_name, (*d2)->d_name);
    }
    
}




void ls(const char *dirpath, int filter, int order)
{
    // allocate momory of one pointer for scandir output
    struct dirent ***res = malloc(sizeof(char*));
    int cnt;
    if (filter == INCLUDE_DOT && order == SORT_BY_NAME) {
        cnt = scandir(dirpath, res, sel_all, cmp_name);
    } else if (filter == INCLUDE_DOT && order == SORT_BY_TYPE) {
        cnt = scandir(dirpath, res, sel_all, cmp_type);
    } else if (filter == EXCLUDE_DOT && order == SORT_BY_NAME) {
        cnt = scandir(dirpath, res, sel_nodot, cmp_name);
    } else if (filter == EXCLUDE_DOT && order == SORT_BY_TYPE) {
        cnt = scandir(dirpath, res, sel_nodot, cmp_type);
    }

    if (cnt == -1) {
        printf("./myls: cannot access %s: No such file or directory", dirpath);
        return;
    }
 
    // declare a pointer to store the dir-entry name
    struct dirent *de;

    // loop through each dir-entry and store name in str_array
    for (int i = 0; i < cnt; i++) {
        de = (*res)[i];
        if (is_dir(de)) {
            printf("%s/\n", de->d_name);
        } else {
            printf("%s\n", de->d_name);
        }
    }
    
    
}

int main(int argc, char *argv[])
{
    int order = SORT_BY_NAME;
    int filter = EXCLUDE_DOT;

    int opt;
    while ((opt = getopt(argc, argv, "az")) != -1) {
        switch (opt) {
            case 'a': filter = INCLUDE_DOT; break;
            case 'z': order = SORT_BY_TYPE; break;
            default: return 1;
        }
    }
    if (optind < argc -1) {
        for (int i = optind; i < argc; i++) {
            printf("%s:\n", argv[i]);
            ls(argv[i], filter, order);
            printf("\n");
        }
    } else {
        ls(optind == argc -1? argv[optind] : ".", filter, order);
    }
    return 0;
}
