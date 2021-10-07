#include "headers.h"

void Jobs(int flag)
{
    // printf("\nentered search\n");
    struct Node *curr = head;

    // char *jobinfo[150];
    // int i = 0;
    int count = 0;
    iiit aalu[150];
   
    while (curr != NULL)
    {
        aalu[count].ppd = curr->pid;
     
        aalu[count].name = curr->name;
        aalu[count].jjn = curr->jobnum;

        char *filename =strinit;
        strinitiation(1024, filename);
        sprintf(filename, "/proc/%d/stat", curr->pid);

        FILE *f = fopen(filename, "r");

        if (f == NULL)
        {
            perror("Error opening stat file");
            return;
        }

        char *arr =strinit;
        strinitiation(1024, arr);

        fgets(arr, 10000, f);

        char *sptr;
        char *state =strinit;
        strinitiation(1024, state);

        for (int x = 0;; x++)
        {
            char *token =strinit;
            strinitiation(1024, token);

            token = strtok_r(arr, " \t", &sptr);
            arr = NULL;

            if (token == NULL)
                break;

            if (x == 2)
            {
                state = token;
                if (strcmp(state, "T") == 0)
                    strcpy(state, "Stopped");
                else
                    strcpy(state, "Running");

                aalu[count].state = state;
                break;
            }
        }


        curr = curr->next;
        count++;
    }

    mergeSort(aalu, 0, count - 1);
    printArray(aalu, count,flag);

    return;
}