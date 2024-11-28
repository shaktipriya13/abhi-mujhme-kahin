#include<stdio.h>
#include<unistd.h>

int main(){
    int pid;
    pid=fork();

    if(pid==0){
        execve("/bin/date\n",NULL,NULL);
        execve("/bin/date\n",NULL,NULL);
        exit(0);
    }
    else{
        printf("From parent pid:",pid);
    }
}
