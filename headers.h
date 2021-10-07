#ifndef HEADER_FILE
#define HEADER_FILE
//HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdbool.h> 

//MACROS
#define rep(i,N)               \
    for (int i = 0; i < N; i++) \
        ;
#define strinit (char *)malloc(1024 * sizeof(char));
#define li long int

//FUNCTIONS

void display();
void strinitiation(int N, char *str);
void strmatching(int l, int N, char *var2, char *var);
void command(char *str);
//colors
void RED();
void BLACK();
void CYAN();
void RESET();
void PURPLE();
void WHITE();
void shellStart();
void YELLOW();
void Clear();

//time
void local_time();
int months(char *str);
//REPEAT 
void repeat_com(int x, char *str);


int Dir_stat(char *file);
char root_dir[1024];
char *starter;
//cdcom
char *cdprevpath;     //path beffore command
char *cdreqprevpath;  //required
char *cdreqprev;
char *cdprev;  

void Cdbuild(char *str);
void Pwdbuild();
void Echobuild(char *str);
//LS
int isDir(char *file);
int isFile(char *file);
void filenaming_order(char *file);
void ExecuteLs(char *var, int l, int a, int al);
//getcwd-->present root directory
//chdir--->changed present directory

//SIGNAL HANDLING
void signal_handler(int sig);
void z_signal(int sig);
void c_signal(int sig);
// void d_signal(int sig);

//bg
struct Node
{
    int pid;           //process id
    char *name;        //name
    int jobnum;        //job number
    struct Node *next; // pointer to next node
};
//MACROS
typedef struct Node node;
typedef struct Node *nodeptr;

extern struct Node *head;
extern struct Node *start;

//bg
int gjnum;
void insert(int pid, char *arg);
char *searchbyName(int pid);
int searchbyJob(int jobnum);
int delete(int pid);


//fg
int shellpid;
int shellpgid;
void fg(int jobnum);
//bg
void bg(int jobnum);

//pinfo
void pinfo(long int p);

//HISTORY

char his_path[200];
void add_history(char *cmd);
void history(int n);
void inithist();
void execute_history();


struct hist
{
    char history[20][100];
    int histfun;
    int histcry;
};
typedef struct hist hiss;
struct hist his;
//
void pip_build(char *str);
//
void redirect(char *str);
//jobs
struct iiith{
    int jjn;
    char *state;
    char *name;
    int ppd;
};
typedef struct iiith iiit;
void Jobs(int flag);
void kill_sig(int jobnum, int sig);
//merge sort
void merge(iiit arr[], int l, int m, int r);
void mergeSort(iiit arr[], int l, int r);
void printArray(iiit A[], int size,int flag);
//baywatch
void interrupt(char *time);
void newborn(char *time);
void baywatch(char *var);
void dirty(char *time);
#endif