#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <fcntl.h>

using namespace std;

int main() {

    const char* CHILD_PATH = "/home/petrkozyrev/osi/os_lab_1/build/child";
    string name ="/home/petrkozyrev/osi/os_lab_1/test/";
    char smb;
    int ind = 0;

    if(read(STDIN_FILENO, &smb, 1) == -1){
        return -1;
    }

    while(smb != '\n'){
        name += smb;
        if (read(STDIN_FILENO, &smb, 1) == -1){
            return -1;
        }
    }
    const char* file_name = name.c_str();
    int input_file = open(file_name,O_RDONLY);

    if(input_file == -1){
        exit(-1);
    }

    int pipe_fd[2];
    int err = pipe(pipe_fd);

    if( err == -1){
        return -1;
    }
    
    pid_t pid = fork();

    if( pid == -1){
        return -1;
    }
    if( pid == 0){ 

        dup2(input_file,STDIN_FILENO);
        
        if(dup2(pipe_fd[1], STDOUT_FILENO) == -1){
            exit(-1);
        }

        close(pipe_fd[0]);

        execlp(CHILD_PATH, CHILD_PATH, NULL);
    }
    else{
        close(pipe_fd[1]);

        int res = 0;
        string ans = "";
        if (read(pipe_fd[0], &res, sizeof(int)) == -1)
        {
            return 7;
        }
        ans = to_string(res);

        write(STDOUT_FILENO, &ans, ans.size());
        
        close(pipe_fd[0]);
        close(input_file);
    }
    
    return 0;
}