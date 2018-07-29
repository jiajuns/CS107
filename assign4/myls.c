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

int cmp_name(const struct dirent **d1, const struct dirent **d2)
{
    return strcmp((*d1)->d_name, (*d2)->d_name);
}

int cmp_type(const struct dirent **d1, const struct dirent **d2)
{
    if (is_dir(*d1) & !is_dir(*d2))
    {
        return 1;
    } else if (!is_dir(*d1) & is_dir(*d2))
    {
        return -1;
    } else {
        return cmp_name(d1, d2);
    }
}


int sel_nodot(const struct dirent *d)
{
    if (d->d_name[0] == '.')
    {
        return 0;
    } else {
        return 1;
    }
}

void ls(const char *dirpath, int filter, int order)
{
    struct dirent ***dirnames = malloc(sizeof(char*));
    int cnt = 0;

    if (filter == EXCLUDE_DOT && order == SORT_BY_NAME)
    {
        cnt = scandir(dirpath, dirnames, sel_nodot, cmp_name);
    }
    else if (filter == INCLUDE_DOT && order == SORT_BY_NAME)
    {
        cnt = scandir(dirpath, dirnames, sel_all, cmp_name);
    }
    else if (filter == EXCLUDE_DOT && order == SORT_BY_TYPE)
    {
        cnt = scandir(dirpath, dirnames, sel_nodot, cmp_type);
    }
    else if (filter == INCLUDE_DOT && order == SORT_BY_TYPE)
    {
        cnt = scandir(dirpath, dirnames, sel_all, cmp_type);
    }

    if (!cnt) {
        printf("./myls: cannot access %s: No such file or directory", dirpath);
        return;
    }

    struct dirent *de;

    for (int i=0; i<cnt; i++){
        de = (*dirnames)[i];
        if (is_dir(de))
        {
            printf("%s/\n", de->d_name);
        } else 
        {
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
