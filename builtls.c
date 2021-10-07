#include "headers.h"
int m1 = 0, ye1 = 0;

void local_time()
{
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);
    time_str[strlen(time_str) - 1] = '\0';
    // printf("Current Time : %s\n", time_str);
    char mon1[4];
    char year1[5];
    int j = 0;
    for (int i = 4; i <= 6; i++)
    {
        mon1[j] = time_str[i];
        j++;
    }
    // printf("%s\n", mon1);
    j = 0;
    for (int i = 20; i <= 23; i++)
    {
        year1[j] = time_str[i];
        j++;
    }
    ye1 = atoi(year1);

    m1 = months(mon1);

    //  printf("%d %d\n",m1,ye1);
}

// Fri Sep 17 08:59:52 2021

void filenaming_order(char *file)
{
    struct stat st;

    if (stat(file, &st) < 0)
    {
        // printf("NHI hua\n");
        return;
    }

    char *temp = strinit;
    strinitiation(1024, temp);
    getcwd(temp, 1024);

    char *check = strinit;
    strinitiation(1024, check);

    //provifing status to the user ,group and others
    check[0] = (S_ISDIR(st.st_mode)) ? 'd' : '-';
    check[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    check[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    check[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
    check[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    check[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    check[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
    check[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    check[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    check[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';

    //local time
    local_time();

    //hardlinks
    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);

    sprintf(check, "%s %ld  %s %s %8ld  ", check, st.st_nlink, pw->pw_name, gr->gr_name, st.st_size);

    char *t = strinit;

    strftime(t, 1024, "%b %d %H:%M %Y", localtime(&st.st_mtime));

    char mon2[3];
    char year2[5];
    int j = 0;
    for (int i = 0; i <= 2; i++)
    {
        mon2[j] = t[i];
        j++;
    }
    // printf("%s\n", mon1);
    j = 0;
    for (int i = 13; i <= 16; i++)
    {
        year2[j] = t[i];
        j++;
    }
    int ye2 = atoi(year2);
    int m2 = months(mon2);
    // printf("%d  %d\n", m2, ye2);

    strftime(t, 1024, "%b %d %H:%M %Y ", localtime(&st.st_mtime));
    if (ye1 == ye2)
    {
        if (m1 - m2 < 6)
            strftime(t, 1024, "%b %d %H:%M ", localtime(&st.st_mtime));
        else
            strftime(t, 1024, "%b %d %Y ", localtime(&st.st_mtime));
    }
    else
        strftime(t, 1024, "%b %d %Y ", localtime(&st.st_mtime));

    sprintf(check, "%s %s ", check, t);

    
    char *ppl = strinit;
    strinitiation(100, ppl);
    int ind = 0;
    for (int i = 0; i < strlen(file); i++)
    {
       if(file[i] == '/')
           ind = i;
    }
    int k = 0;
    for (int i = ind + 1; i < strlen(file); i++)
    {
        ppl[k] = file[i];
        k++;
    }
    // printf("%s\n", ppl);
    sprintf(check, "%s %s", check, ppl);
    printf("%s\n", check);

    free(check);
    free(temp);
}

struct stat filestat;
//executing th els command
void ExecuteLs(char *var, int l, int a, int al)
{
    char *var2 = strinit;
    strinitiation(1024, var2);

    strmatching(3, strlen(var) - 1, var2, var);

    char *sptr;

    for (int i = 0;; i++)
    {
        char *token = strinit;
        strinitiation(1024, token);

        token = strtok_r(var2, " \t", &sptr);

        var2 = NULL;
        if (token == NULL)
            break;

        //modify for ~
        char *str = strinit;
        strinitiation(1024, str);

        int tilda = 0; //root directory

        if (token[0] == '~')
        {
            tilda = 1;
            char *var3 = strinit;
            strinitiation(1024, var3);

            strmatching(1, strlen(token), var3, token);

            sprintf(str, "%s%s", root_dir, var3);

            free(var3);
        }
        else
            str = token;

        if (isFile(str) == 1)
        {
            //it is a file so all user group and others checks printed if l = 1 and al = 1
            if (l == 1 || al == 1)
                filenaming_order(str);
            else
                printf("%s\n", str); //jyst print the name of file
        }

        if (isDir(str) == 1)
        {
            int parent = 0;
            // printf("%s:\n", str);
            struct dirent *de; // a structure type used to return information about directory entries
            struct dirent *re;
            if (strcmp(str, "..") == 0) //parent directory
                parent = 1;
            if (strcmp(str, "~") == 0)
                tilda = 1; //root dir

            DIR *dr = opendir(str); //open directory to list out files and directoriies
            DIR *rr = opendir(str);
            if (dr == NULL) // checkendir returns NULL if couldn't check directory
            {
                perror(":(");
            }

            if (al == 1 || ((a == 1) && (l == 1)))
            {
                char *temp = strinit;
                strinitiation(1024, temp);
                getcwd(temp, 1024);

                int err = 0;
                int total = 0;
                if (parent == 1)
                    err = chdir(".."); //changes to the parent
                if (tilda == 1)
                    err = chdir(root_dir); //if tilda ~ so root dir

                if (err != 0)
                {
                    YELLOW();
                    printf("chdir error\n");
                    RESET();
                }
                while ((re = readdir(rr)) != NULL)
                {
                    if (parent != 1 && tilda != 1)
                    {
                        char *filepath = strinit;
                        strcpy(filepath, str);
                        strcat(filepath, "/");
                        strcat(filepath, re->d_name);
                        stat(filepath, &filestat);
                        total += filestat.st_blocks;
                    }

                    else
                    {
                        stat(re->d_name, &filestat);
                        total += filestat.st_blocks;
                    }
                }
                printf("total %d\n", total / 2);
                while ((de = readdir(dr)) != NULL)
                {
                    if (parent != 1 && tilda != 1)
                    {
                        char *filepat = strinit;
                        strcpy(filepat, str);
                        strcat(filepat, "/");
                        strcat(filepat, de->d_name);
                        filenaming_order(filepat);
                    }

                    else
                        filenaming_order(de->d_name);
                }

                if (parent == 1 || tilda == 1)
                {
                    err = chdir(temp);

                    if (err != 0)
                    {
                        YELLOW();
                        printf("chdir error\n");
                        RESET();
                    }
                }

                fflush(NULL);

                closedir(dr);
                free(temp);
                continue;
            }

            else if (l == 1)
            {
                char *temp = strinit;
                strinitiation(1024, temp);
                getcwd(temp, 1024);
                int err = 0;

                if (parent == 1)
                    err = chdir("..");
                if (tilda == 1)
                    err = chdir(root_dir);
                int total = 0;
                if (err != 0)
                {
                    YELLOW();
                    printf("chdir error\n");
                    RESET();
                }
                while ((re = readdir(rr)) != NULL)
                {
                    //     printf("aha\n");
                    if (re->d_name[0] != '.') //hidden
                    {
                        if (parent != 1 && tilda != 1)
                        {
                            char *filepath = strinit;
                            strcpy(filepath, str);
                            strcat(filepath, "/");
                            strcat(filepath, re->d_name);
                            stat(filepath, &filestat);
                            total += filestat.st_blocks;
                        }

                        else
                        {
                            stat(re->d_name, &filestat);
                            total += filestat.st_blocks;
                        }
                    }
                }
                printf("total %d\n", total / 2);
                // struct dirent *de;
                while ((de = readdir(dr)) != NULL)
                {
                    if (de->d_name[0] != '.')
                    {

                        if (parent != 1 && tilda != 1)
                        {
                            char *filepath = strinit;
                            strcpy(filepath, str);
                            strcat(filepath, "/");
                            strcat(filepath, de->d_name);
                            filenaming_order(filepath);
                        }

                        else
                            filenaming_order(de->d_name);
                    }
                }

                if (parent == 1 || tilda == 1)
                {
                    err = chdir(temp);

                    if (err != 0)
                    {
                        YELLOW();
                        printf("chdir error\n");
                        RESET();
                    }
                }

                fflush(NULL);

                closedir(dr);
                free(temp);
                continue;
            }

            else if (a == 1)
            {
                char *temp = strinit;
                strinitiation(1024, temp);
                getcwd(temp, 1024);
                int err = 0;

                if (parent == 1)
                    err = chdir("..");
                if (tilda == 1)
                    err = chdir(root_dir);

                if (err != 0)
                {
                    YELLOW();
                    printf("chdir error\n");
                    RESET();
                }

                while ((de = readdir(dr)) != NULL)
                    printf("%s\n", de->d_name);

                if (parent == 1 || tilda == 1)
                {
                    err = chdir(temp);

                    if (err != 0)
                    {
                        YELLOW();
                        printf("chdir error\n");
                        RESET();
                    }
                }

                fflush(NULL);

                free(temp);
                closedir(dr);
                continue;
            }

            else
            {
                char *temp = strinit;
                strinitiation(1024, temp);
                getcwd(temp, 1024);
                int err = 0;
                int total = 0;
                if (parent == 1)
                    err = chdir("..");
                if (tilda == 1)
                    err = chdir(root_dir);

                if (err != 0)
                {
                    YELLOW();
                    printf("chdir error\n");
                    RESET();
                }

                while (de = readdir(dr))
                {
                    if (de->d_name[0] != '.') //hidden file
                        printf("%s\n", de->d_name);
                }

                fflush(NULL);

                if (parent == 1 || tilda == 1)
                {
                    err = chdir(temp);

                    if (err != 0)
                    {
                        YELLOW();
                        printf("chdir error\n");
                        RESET();
                    }
                }

                free(temp);
                closedir(dr);
            }
        }
    }

    free(var2);
}