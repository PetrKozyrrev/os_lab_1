#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <cmath>

using namespace std;

bool isPrime(int number) {
    if (number < 2) {
        return false;
    }

    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]){
    char smb;
    int number=0,sgn = 1,ind = 0;
    char buff[7];

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
            number =  (number*10) + (smb-'0');
            read(STDIN_FILENO, &smb, 1);
        }
        number*=sgn;
        if(isPrime(number) or number<=0){
            break;
        }
        number = 0;
        sgn = 1;
        read(STDIN_FILENO, &smb, 1);
    }
    buff[ind] = '\n';
    ind++;
    for(int i=0;i<ind;i++){
        write(STDOUT_FILENO,&buff[i],1);
    }
    perror("end child\n");
    exit(1);
    return 0;
}