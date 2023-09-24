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
    int number=0,sgn = 1;

    if (read(STDIN_FILENO, &smb, 1) == -1){
        return -1;
    }
    while(smb!=' '){
        while (smb != '\n'){
            if(smb == '-'){
                sgn = -1;
            }
            number =  (number*10) + (smb-'0');
            read(STDIN_FILENO, &smb, 1);
        }
        number*=sgn;
        if(isPrime(number) or number<=0){
            exit(-1);
        }
        else{
            write(STDOUT_FILENO,&number,sizeof(int));
        }
        number = 0;
        sgn = 1;
        read(STDIN_FILENO, &smb, 1);
    }
    return 0;
}