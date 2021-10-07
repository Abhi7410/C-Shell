
#include "headers.h"


void Cdbuild(char *str)
{
    char *token = strinit;
    strinitiation(1024,token);

    int flag = 1;
    for (int i = 0; i < strlen(str) - 1; i++)
    {    token[i] = str[i];
      
    }


    strinitiation(1024, cdreqprev);
    strinitiation(1024, cdreqprevpath);

    strcat(cdreqprev, cdprev);
    strcat(cdreqprevpath, cdprevpath);

    strinitiation(1024, cdprevpath);
    strinitiation(1024, cdprev);
    //root directory print

    char *temp = strinit;
    strinitiation(1024, temp);
    getcwd(temp, 1024); //current directory

    // if(str == NULL)
    //     return;

    if (strcmp(token, "~") == 0)
    {
        strcat(cdprevpath, temp);
        //change the directory if error then it shows
        int error = chdir(root_dir);

        if (error != 0)
        {
            YELLOW();
            printf("chdir error\n");
            RESET();
        }
        return;
    }
 
    if (strcmp(token, "-") == 0)
    {
        //cdprevpath is path of previous directory
        strcat(cdprevpath, temp); 
        //printing the path of present
        printf("%s\n", cdreqprevpath);
        //chainging to the required one
        int error = chdir(cdreqprevpath);
        //then changed the path
        if (error != 0)
        {
            YELLOW();
            printf("cd - error\n");
            RESET();
        }
        return;
    }
  //~/directory 
    if (token[0] == '~')
    {
        char *temp1 = strinit;
        strinitiation(1024, temp);

        char *temp2 = strinit;
        strinitiation(1024,temp2);

       //stroing in tem1 the directory name
        for (int i = 1; i < (strlen(token)); i++)
            temp1[i - 1] = token[i];

        sprintf(temp2, "%s%s", root_dir, temp1);
       

        char *temp3 = strinit;
        strinitiation(1024,temp3);
        getcwd(temp3, 1023);
        strcat(cdprevpath, temp3);

        int error = chdir(temp2);

        if (error != 0)
        {
            YELLOW();
            printf("chdir error\n");
            RESET();
        }
        free(temp1);
        free(temp2);
        free(token);
        return;
    }


    //if there is specigic directory name 
    //token is directory's name
    sprintf(token, "%s", token);

   
    char *temp4 = strinit;
    strinitiation(1024, temp4);
    //current directory
    getcwd(temp4, 1024);
    strcat(cdprevpath, temp4);

    int error = chdir(token);
    if (error != 0)
    {
        YELLOW();
        printf("chdir error\n");
        RESET();
    }
    // free(temp);
    free(token);

    return;
}

