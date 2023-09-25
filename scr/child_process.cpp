#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <fcntl.h>
#include "prime.cpp"

using namespace std;

int main(int argc, char* argv[]){
    char smb;
    int number=0,sgn = 1,ind = 0,len_lst_number = 0;
    char buff[256];

    if (read(STDIN_FILENO, &smb, 1) == -1){
        return -1;
    }
    while (smb != '\n'){
        buff[ind] = smb;
        ++ind;
        if(smb != ' '){ 
            if(smb == '-'){
                sgn = -1;
            }
            len_lst_number++;
            number =  (number*10) + (smb-'0');
            read(STDIN_FILENO, &smb, 1);
        }
        else{
            number*=sgn;
            if(isPrime(number) or number<=0){
                break;
            }
            number = 0;
            sgn = 1;
            len_lst_number = 0;
            read(STDIN_FILENO, &smb, 1);
        }
    }
    buff[ind] = '\n';
    for(int i=0;i<ind-len_lst_number-1;i++){
        write(STDOUT_FILENO,&buff[i],1);
    }
    return 0;
}