#include<bits/stdc++.h>
#include<regex.h>

using namespace std; 

int main(){
    char  a[] = "hhh   <awda>\nawdawdaw <awdawda>\nawdawdaw    <awdawwad>";
    regex_t regex;
    regmatch_t match[1];
    int ret = regcomp(&regex, "(\\w+).{0,1}<(.+)>" , REG_EXTENDED );
     ret = regexec(&regex, a ,1,match,REG_EXTENDED);
    cout<<string(a+match[0].rm_so,match[0].rm_eo-match[0].rm_so)<<endl;
}