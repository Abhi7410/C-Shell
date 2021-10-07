#include "headers.h"

void display()
{
    char *user_name = strinit;
    strinitiation(1024, user_name);
    char *host_name = strinit;
    strinitiation(1024, host_name);

    // struct utsname uname_pointer;
    // uname(&uname_pointer);
    // strcpy(host_name, uname_pointer.sysname);
    gethostname(host_name, 1024);

    getlogin_r(user_name, 1024);
    

    char *dir = strinit;
    strinitiation(1024, dir);
    getcwd(dir, 1024);
    // printf(" BOOM BOOM\n");
    int rs = strlen(root_dir);
    int ds = strlen(dir);
    if (strcmp(dir, root_dir) == 0)
    {
        CYAN();
        printf("<%s@%s:", user_name, host_name);
        RESET();

        WHITE();
        printf("~");
        RESET();

        RED();
        printf(">");
        RESET();
     
    }
    else if ((strncmp(dir, root_dir,rs) == 0) && ds > rs)
    {
        char *Str = strinit;
        strinitiation(1024,Str);

        int j = 0;
        for (int i = (rs + 1); i < ds; i++)
        {
            Str[j] = dir[i];   
            j++;
        }
        CYAN();
        printf("<%s@%s:", user_name, host_name);
        RESET();

        WHITE();
        printf("~/%s", Str);
        RESET();

        RED();
        printf(">");
        RESET();
    }

    else
    {
        CYAN();
        printf("<%s@%s:", user_name, host_name);
        RESET();

        WHITE();
        printf("~%s", dir);
        RESET();

        RED();
        printf(">");
        RESET();
    }

    free(user_name);
    free(host_name);
    free(dir);
}


