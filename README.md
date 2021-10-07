
# C-shell

## HOW TO COMPILE
- This assignment is compiled through a makefile. By typing "make" into the terminal, all files that are in the directory are compiled.
- To run the code, run "./a.out". Use command "q" or "exit" to exit the shell.
- Fuctioning of all .c files are defines below.
### headers.h
- contains all the function declarations and global variable declarations and
  structs and all the header files.

### basicfun.c 
- ``` Dir_stat ``` function for checking directory status
- ```isDir``` string as argument (file) to check whether it is a directory or not.
- ```isFile``` string as argument (file) to check whether it is a file or not. 
- ```strmatching``` ```strinitation``` fnctions to initate string and some manipulation
- ```RED``` ```BLACK``` ```CYAN``` ```PURPLE``` ```WHITE``` ```RESET``` funtions to set the color of display prompt and some other outputs.
- ```Clear``` function to clear the screen 
- ```ShellStart``` Differniates the normal bash from my bash some stying given
- ```months``` string as the first character of month names to manipulate the 6 months time. In ```ls -l``` command the files with status more than 6 months shows Year instead of hour and minute.

### main.c
- The main() function is ran first on executing the shell. The directory from which the shell has been run is saved here ```getcwd()``` and passed as an argument to remaining functions.
- shellstart() function is called and with the dislay it appears "WELCOME THE TO MY SHELL"
- The signal_handler function that checks the signal for child process and prints the appropriate results on the screen is called.
- Then finally loop which takes commands and runs corresponding commands if theyr are builtin then they run as according to the implementation else others behave as non builtin commands that works normally in bash till we put ```q or exit``` or it shows some error. 
- insert(), search(), and delete() are functions used to create and use a linked list data structure to save the names of the child processes called.

### bgfun.c
- ```bg``` searches the process through job number if not there then error appears else makes it contniue as bg process
- ```insert``` linked list represenation for background process , ```searchbyName``` searches the process through pid and returns the command names
  ```searchbyJob``` searches the process with its job number and returns its pid . ```delete``` command finds the process with the pid and removes from the
  linked list.

### builtincommand.c
- Basically consists of command function which takes commandline as input then tokenise the multiple commands,
  then furthur tokenise them on the basis of tab space. ```cd``` ```ls``` ```pwd``` ```echo``` ```repeat``` ```history```
  ```bg``` ```fg``` and the last section includes command using execvp .

### builtls.c
- ```local_time``` for the last updation of files we filter the time for last 6 mothns using present time as the local time so this gives year and month of the present time
- ```filenaming_order``` user,group and others modes will be chosen for the file as input to the function
- ```ExecuteLs``` flags and string as input which tokenises first and then implements them.
 * ls
    * -a -->hidden files and directories
    * -l -->long format along with total
    * -al or -la -->long formst with hidden files
    * ls . -->lists files and directories in current directory/file
    * ls ~ -->list file/direct in root directory
    * ls .. -->lists files/direct in parent of current directory
### cdcom.c
* Cdbuild function executed the cd functionality. The shell we move to the directory mentioned below.If it moves to a parent directory to where the shell was created (root directory), the absolute path of the directory will be displayed. If 
  it moves to directories within the root, they will be displayed as '/newdirectory'.
    * cd . represents changing to the same current directory.
    * cd .. changes to parent directory.
    * cd ~ changes to root directory where shell was executed first.
    * cd '/dir' changes to dir with a valid path.

### pwd.c
Pwdbuild() function executes the pwd functionality and prints the present working directory.

### echo.c
Echobuild() function will display the argument input to echo. If there were spaces and tabs, it will display the line without them.

### control.c
- ```z_signal``` On typing cntrl+Z ,foreground process exits and then it gets pushed as background process but in stopped status.
- This function matches and kills with signal SIGSTP(Interrupt causes by user) else it just shows display.
- ```c_signal``` This will stop any current running fg process , implemented using signal SIGINT( sent to a process by its controlling 
  terminal when a user wishes to interrupt the process).
- ```signal_handler``` This checks every signals which is called using execv or child process. Gives a message on screen whether the process has exited
  normallly or abnormally.

### display.c
- called in main function before starting any process whch takes hostname and username and 
  sets correpoding path on the basis of commands.

### pinfo.c
- ```pinfo()``` will display the following information of the shell if a pid is not mentioned, of the proccess info of a given pid.
   pid. It stores the ```/proc/pid/stat``` data in one file and extracts the necessary data that is given as:
   * pid
   * process status
   * virtual memory in bytes
   * executable path

### repeat.c
- Takes command and integer that is no. of iterations , for implemented commands like ```cd``` ```pwd``` ```ls``` ```echo``` ```pinfo``` the repeat is implemented
  as their correponding matches. The other non builtin commands will perform using execv as they do in normal bash.

### history.c
- It stores the recent distinct commandlines in a histo.txt file. If the command crosses the limit 20 than it starts overwriting the previous one.
- ```history()``` sets the limit and prints the limited commands on the terminal
- ```execute_history()``` writes the commands in the histo.txt files.
- ```add_history()``` to count the no. of commands ans checks whether it matches with the previous one or not.
- ```init_hist``` called in the start of shell , opens the file if it already contains data then it writes ahead of that else starts from scratch.

### mergesort.c
- It has merge sort and printing the sorted array function. The current jobs are printed in the sorted order of their names
  after command ```jobs```.
- ```printArray``` funciton has three part on the basis of the flag passed for Running , Stopped or Both jobs.

### baywatch.c 
- The input command taken in the form of ```baywatch -n x command``` where x is number of seconds in which
  to execute command periodically and command can be either interrupt ,newborn or dirty.
- ```baywatch``` will be used in calling different command functions when they are required.
  The output will be printed onto stdout for the given -n x seconds as until q is pressed on the keyboard.
- ```interrupt``` It displays the number of times CPU has/have been interrupted b the keyboard controller after x seconds.
- ```newborn``` It displays the pid of the most recelty process on the system after every x seconds.
- ```dirty``` It displays the size of the part of the memory which is disrty after x seconds. 
### redirection.c 
-  ```redirect()``` It is used for implementation of redirection of multiple files and prints error if some syntax error in redirection input is there.

### piping.c 
- ```pip_build()``` implements piping with redirection through multiple commands and files.

### fg.c 
- takes the input as fg x, if ivalid input if given it prints in the terminal, if the x number job exists as backgorund process ```fg()``` will bring
  the job to the forground and change its state to running.

### signalkill.c 
- send a specific signal(no.) given as input along with job number(inpit)
- input format is ```sig x y``` where x is job number and y is signal number that we can check by ```kill -l``` command .


### job.c 
- input is ```jobs``` or ```jobs -flag``` where flag can be either r or s where r will sort all the jobs which are runnind and print its pid,status name and jobnumber. s will do 
  same for stopped process. If no flag is given then it will print all the jobs sorted on the basis of their names.
