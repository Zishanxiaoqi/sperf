#include<bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <regex.h>
#include <time.h>

using namespace std;
map<string,double> syscalls_time;

void read_buffer(char *buffer){
    regex_t regex;
    regmatch_t match[3];
    int ret = regcomp(&regex, "(\\w+)\\([^\n]*\\)\\s+=\\s[^\n]*<([^\n]*)>" , REG_EXTENDED );
    if(ret){
        cout<<ret<<endl;
        perror("Could not compile regex\n");
    }

    char *start = buffer;
    while(1){
        ret = regexec(&regex, start, 3, match, REG_EXTENDED);
        if(ret&&ret!=REG_NOMATCH){
            perror("Could not execute regex\n");
        }
        if(ret==REG_NOMATCH){
            break;
        }
        string syscall_name = string(start+match[1].rm_so,match[1].rm_eo-match[1].rm_so);
        string time1 = string(start+match[2].rm_so,match[2].rm_eo-match[2].rm_so);
        double time = stod(time1);
        syscalls_time[syscall_name] += time;

        start = start +  match[0].rm_eo+1;
    }
    for(auto i:syscalls_time){
        cout<<i.first<<" "<<i.second<<endl;
    }
}

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
        regmatch_t match[3]; 
        int n=0;
        while(1){
            n++;
            char buffer[100000];
            sleep(0.1);
            cout<<"************************"<<n<<endl;
            int ret2 = waitpid(pid, &status,WNOHANG);
            if(ret2>0){
                if(ret2!=pid){
                    perror("Error in waitpid\n");
                }
                break;
            }
            read(fd[0],buffer,100000);
            read_buffer(buffer);
        }

        close(fd[0]);
    }
    
    
    return 0;
}