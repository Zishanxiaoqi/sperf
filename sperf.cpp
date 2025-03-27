#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <regex.h>

using namespace std;

int main(int argc,char *argv[]){
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid==0){
        close(fd[0]);//close read end
        char **value = new char*[argc+3];
        value[0] = new char[strlen("/user/bin/strace")+1];
        value[0] = "/bin/strace";
        value[1] = new char[strlen("-T")+1];
        value[1] = "-T";

        for(int i=1;i<argc;i++){
            value[i+1] = new char[strlen(argv[i])+1];

            strcpy(value[i+1],argv[i]);
        }
        value[argc+1] = NULL;
        dup2(fd[1],STDERR_FILENO);
        close(fd[1]);
        int a = execve("/bin/strace", value, NULL);
        
        
    }else{
        close(fd[1]);//close write end
        int status;
        int ret = waitpid(pid, &status,0);
        char buffer[100000];
        read(fd[0],buffer,100000);
        cout<<buffer<<endl;
        close(fd[0]);
    }
    
    
    return 0;
}