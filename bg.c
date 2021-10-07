#include "headers.h"

//check background process
void bg(int job_num)
{
    int pid = searchbyJob(job_num); //searching with job number

    if (pid == -1)
    {
        YELLOW();
        write(2, "Background process with given job number doesn't exist.\n", 57);
        RESET();
        return;
    }

    kill(pid, SIGCONT);//18 if it stopeed then continue that
}


//insertion at the front end of the linkedlist

void insert(int pid, char *arg)
{
    node* newNode = (nodeptr)malloc(sizeof(node));
    newNode->pid = pid;
    ++gjnum;
    newNode->name = arg;
    newNode->jobnum = gjnum;
    newNode->next = head;
    head = newNode;
}

char *searchbyName(int pid)
{
    //pointer the head node and traversing until we get the desired one
    nodeptr current = head;

    while (current != NULL)
    {
        int piddx = current->pid;
        char *com = current->name;

        if (piddx == pid)
        {
            return com;
            //here we get
        }
        else
        {
            current = current->next;
            //itarating to the next
        }
    }
    return " ";
    //else returning empty string
}

int searchbyJob(int jobnum)
{

    nodeptr current = head;

    while (current != NULL)
    {
        int piddx = current->pid;
        char *com = current->name;
        int jbnum = current->jobnum;

        if (jbnum == jobnum)
        {
            return piddx;
        }
        else
        {
            current = current->next;
        }
    }
    return -1;
}

int delete(int pid)
{
    //to deltet we have to use two pointers so that after deleting we can make a link
    nodeptr current = head;
    nodeptr previous;

    //if matches with first then point to other
    if (current != NULL && current->pid == pid)
    {
        head = current->next;
        free(current);
        // display();
        return 0;
    }

    while (current != NULL && current->pid != pid)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
      {
        //   display();
          return -2;
      }

    previous->next = current->next;

    free(current);
    // display();
    // write(2,"deletion complete\n",19);
    return 0;
}