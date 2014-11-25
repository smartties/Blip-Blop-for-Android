#include "log.h"

char buff_path[2048];

char *create_path(const char * a, const char *b)
{
    if(a == NULL || b == NULL)
    return NULL;

    int i;

    sprintf(&buff_path[0], "%s/%s", a, b);

    for(i = 0; i < strlen(buff_path); i++)
    {
        if(buff_path[i] == 92)
        buff_path[i] = 47;
    }

    return &buff_path[0];
}

char *create_pathSDL(const char * a)
{
    return create_path(SDL_AndroidGetInternalStoragePath(), a);
}

