#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>

void printData();

int j = 3;
struct timeval start, end;
struct rusage usage;
char *cmd[32];
char *argv[32];

int main() {

    char *option;
    option=(char*)malloc(500);

    do{
        printf("G'day, commander! What command would you like to run?\n\t0. whoami\t: Prints out the result of the whoami command\n\t1. last\t: Prints out the result of the last command\n\t2. ls\t: Prints out the result of a listing on a user-specified path\n");
        
        for(int i = 3; i < j; i++){
            printf("\t%d. %s\t: User added command\n", i, cmd[i]);
        }
        
        printf("\ta. add command\t: Adds a new command to the menu\n\tc. change directory\t: Changes process working directory\n\te. exit\t: Leave Mid-Day Commander\n\tp. pwd\t: Prints working directory\n");
        printf("Option?:");
        //option = getchar();
        fgets(option, 6, stdin);
        option[strcspn(option, "\n")]=0;
        gettimeofday(&start, NULL);

        if (strcmp(option, "0")==0){
            printf("-- Who Am I? --\n");
            system("whoami");
            printData();
        }
        else if (strcmp(option, "1")==0){
            printf("-- Last Logins --\n");
            system("last | head -1");
            printData();
        }
        else if (strcmp(option, "2")==0){
            argv[0] = (char*)malloc(500);
            argv[0] = "ls";
            argv[1] = (char*)malloc(500);
            argv[2] = (char*)malloc(500);
            printf("-- Directory Listing --\nArguments?: ");
            fgets(argv[1], 9, stdin);
            argv[1][strcspn(argv[1], "\n")] = 0;

            printf("Path?: ");
            fgets(argv[2], 9, stdin);
            argv[2][strcspn(argv[2], "\n")] = 0;

            argv[3] = NULL;
            execvp(argv[0],argv);
            printData();
        }
        else if (strcmp(option,"a")==0){        
            printf("-- Add a command --\nCommand to add?:");
            cmd[j] = (char*)malloc(1);
            fgets(cmd[j], 10, stdin);
            cmd[j][strcspn(cmd[j], "\n")] = 0;
            printf("\nOkay, added with ID %d\n",j);
            j++;
        }
        else if (strcmp(option, "c")==0){
            printf("-- Change Directory --\nNew Directory?");
            fgets(argv[4], 10, stdin);
            argv[4][strcspn(argv[4], "\n")] = 0;
            chdir(argv[4]);

        }
        else if (strcmp(option, "p")==0){
            printf("-- Current Directory --\nDirectory: ");
            system("pwd");
        }
        else if((int)(option[0] - '0') >= 3){
            printf("-- Command: %s--\n", cmd[(int)(option - "0")]);
            system(cmd[(int)(option-"0")]);
            printData();
        }
    }while(1);//strcmp(option, "e")!=0);

    return 0;
}


void printData(){
    gettimeofday(&end, NULL);
    getrusage(RUSAGE_SELF, &usage);
    printf("\n-- Statistics --\nElapsed time: %lf  milliseconds\n",(double)(end.tv_sec*1000.0 + end.tv_usec/1000.0 - start.tv_sec*1000.0 - start.tv_usec/1000.0));
    printf("Page Faults: %ld\nPage Faults (reclaimed): %ld\n\n",usage.ru_majflt,usage.ru_minflt);
}
