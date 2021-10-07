#include "headers.h"

void Pwdbuild()
{
    char *pwd = strinit;
    strinitiation(1024, pwd);
    getcwd(pwd, 1024);
    printf("%s\n", pwd);
}
