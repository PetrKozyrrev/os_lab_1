#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {

    const char* CHILD_PATH = "/home/petrkozyrev/osi/os_lab_1/build/child";
    string name ="/home/petrkozyrev/osi/os_lab_1/test/";
    char smb;
    int ind = 0;

    if(read(STDIN_FILENO, &smb, 1) == -1){
        perror("Reading error\n");
        exit(1);
    }

    while(smb != '\n'){
        name += smb;
        if (read(STDIN_FILENO, &smb, 1) == -1){
            perror("Reading error\n");
            exit(1);
        }
    }
    const char* file_name = name.c_str();
    
    int pipe_fd[2];
    int err = pipe(pipe_fd);

    if( err == -1){
        perror("Pipe error\n");
        exit(1);
    }
    
    pid_t pid = fork();

    if( pid == -1){
        perror("Pid errror\n");
        exit(1);
    }
    if( pid == 0){ 
        close(pipe_fd[0]);
        int input_file = open(file_name,O_RDONLY);

        if(input_file == -1){
            perror("Cant open file\n");
            exit(1);
        }

        dup2(input_file,STDIN_FILENO);
        
        if(dup2(pipe_fd[1],STDOUT_FILENO) == -1){
            perror("Cant dup2\n");
            exit(1);
        }
        execlp(CHILD_PATH, CHILD_PATH, NULL);
        close(input_file);
        perror("execlp\n");
        exit(EXIT_SUCCESS);
    }
    else{
        close(pipe_fd[1]);

        char buff;
        while( (read(pipe_fd[0], &buff, 1) > 0)){
            write(STDOUT_FILENO,&buff,1);
        }   
        close(pipe_fd[0]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}