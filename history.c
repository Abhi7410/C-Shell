#include "headers.h"

int limit = 20;

void history(int x)
{
    int n;
    if (x == 0)
        n = limit;
    else
        n = x;
    for (int i = n; i > 0; i--)
    {
        int lol = his.histfun - i;
        lol = (lol % limit + limit) % limit; //modulation to limit to 20
        if (his.history[lol] == NULL)
        {
            continue;
        }
        else
        {
             if (strlen(his.history[lol]) > 0)
                printf("%s \n", his.history[lol]);
        }
    }
}
void execute_history()
{
    FILE *hisfile;
    hisfile = fopen(his_path, "wb");
    fwrite(&his, sizeof(hiss), 1, hisfile);
    fclose(hisfile);
}

void add_history(char *cmd)
{
    if (strcmp(his.history[(his.histfun - 1) % 20], cmd) != 0)
    {
        strcpy(his.history[his.histfun % 20], cmd);
        his.histfun++;
    }
}

void inithist()
{

    char temp[50];

    strcpy(temp, root_dir);
    strcat(temp, "/histo.txt");
    strcpy(his_path, temp);
    FILE *hfile;
    hfile = fopen(his_path, "rb");
    int flag = 0;
    if(hfile==NULL)
        flag = 1;
    if (flag == 1)
    {
        his.histfun = 0; //if it is the initation then we start with 0
        his.histcry = 0;
    }
    else
    {
        fread(&his, sizeof(hiss), 1, hfile);
        fclose(hfile);
    }
}