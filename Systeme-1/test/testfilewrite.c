#include <stdio.h> 
#include <unistd.h> //sleep()
#include <stdlib.h> //EXIT_SUCCESS
#include <signal.h> //sigaction()
#include <stdbool.h> //bool
#include <sys/types.h> // wait()
#include <sys/wait.h> // wait()
#include <string.h> //strlen()
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>   //for mkfifo



int main()
{
    const char * fifo_name = "myfifo";
    // printf("fifoname %s\n", fifo_name);
    int pipe_fd = -1;
    int data_fd = -1;
    int res = 0;
    const int open_mode = O_WRONLY;
    int bytes_sent = 0;
    char buffer[PIPE_BUF + 1];


    if (access(fifo_name, F_OK) == -1)
    {
        res = mkfifo(fifo_name, 0777);
        if (res != 0)
        {
            fprintf(stderr, "Could not create fifo %s\n", fifo_name);
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO O_WRONLY\n", getpid());

    pipe_fd = open(fifo_name, open_mode);
    data_fd = open("Data.txt", O_RDONLY);

    printf("Process %d result %d\n", getpid(), pipe_fd);

    //writing data
    if (pipe_fd != -1)
    {
        int bytes_read = 0;
        bytes_read = read(data_fd, buffer, PIPE_BUF);
        buffer[bytes_read] = '\0';
        // int input =  rand() % 100;
        // buffer[sizeof(input)] = '\0';
        while (bytes_read > 0)
        {
            res = write(pipe_fd, buffer, bytes_read);
            if (res == -1)
                {
                    fprintf(stderr, "Write error on pipe\n");
                    exit(EXIT_FAILURE);
                }
            bytes_sent += res;
            bytes_read = read(data_fd, buffer, PIPE_BUF);
            buffer[bytes_read] = '\0';
        }
        close(pipe_fd);
        close(data_fd);

    }
    else
    {
        exit(EXIT_FAILURE);
    }

    printf("Process %d finished\n", getpid());

    exit(EXIT_SUCCESS);

}