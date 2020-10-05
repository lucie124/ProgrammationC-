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
    const char *fifo_name = "myfifo";
    int pipe_fd = -1;
    int data_fd = -1;
    int res = 0;
    int open_mode = O_RDONLY;
    char buffer[PIPE_BUF + 1];
    int bytes_read = 0;
    int bytes_write = 0;

    memset(buffer, '\0', sizeof(buffer));

    printf("Process %d opening FIFO O_RDONLY\n", getpid());

    pipe_fd = open(fifo_name, open_mode);

    data_fd = open("DataFormFIFO.txt", O_WRONLY | O_CREAT, 0644);

    printf("Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1)
    {
        do
        {
            // 读取FIFO中的数据，并把它保存在文件DataFormFIFO.txt文件中
            res = read(pipe_fd, buffer, PIPE_BUF);
            bytes_write = write(data_fd, buffer, res);
            bytes_read += res;
        }
        while (res > 0);
        close(pipe_fd);
        close(data_fd);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    
    printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
    exit(EXIT_SUCCESS);
}