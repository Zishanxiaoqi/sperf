#include<bits/stdc++.h>
#include <unistd.h>

using namespace std;

int main(int argc,char *argv[]){
    pid_t pid = fork();
    if(pid==0){
        char **value = new char*[argc+2];
        value[0] = new char[strlen("/user/bin/strace")+1];
        value[0] = "/user/bin/strace";
        cout<<value[0]<<endl;
        for(int i=1;i<argc;i++){
            value[i] = new char[strlen(argv[i])+1];

            strcpy(value[i],argv[i]);
            cout<<value[i]<<endl;
        }
        value[argc+1] = NULL;
        int a = execve("/user/bin/strace", value, NULL);
        cout<<a<<endl;
    }
    
    
    return 0;
}