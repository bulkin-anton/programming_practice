#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

void
process_a(int fd_in[2], int fd_out[2]){
    int arr[4];
    close(fd_in[1]);
    close(fd_out[0]);
    while (read(fd_in[0], arr, 2 * sizeof(int)) == (2 * sizeof(int))){
        arr[2] = arr[0] + arr[1];
        arr[3] = arr[0] - arr[1];
        write(fd_out[1], arr, 4 * sizeof(int));
    }
    close(fd_out[1]);
    close(fd_in[0]);
    exit(0);
}

void
process_son(int num1, int num2, int fd_in[2],
int fd_out[2], int fd_proc[2]){
    int num[2], ans[4];
    char lit;
    num[0] = num1;
    num[1] = num2;
    close(fd_in[0]);
    close(fd_out[1]);
    read(fd_proc[0], &lit, sizeof(char));
    write(fd_in[1], num, 2 * sizeof(int));
    read(fd_out[0], ans, 4 * sizeof(int));
    printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]);
    write(fd_proc[1], &lit, sizeof(char));
    close(fd_in[1]);
    close(fd_out[0]);
    close(fd_proc[0]);
    close(fd_proc[1]);
    exit(0);
}

int
main(void){
    pid_t pid;
    int fd_a_in[2], fd_a_out[2], fd_proc[2], nums[2];
    char chr = '1';
    setbuf(stdin, 0);
    pipe(fd_a_out);
    pipe(fd_a_in);
    if (fork() == 0){
        process_a(fd_a_in, fd_a_out);
    }
    pipe(fd_proc);
    write(fd_proc[1], &chr, sizeof(char));
    while (scanf("%d%d", &nums[0], &nums[1]) == 2){
        while ((pid = fork()) == -1){
            wait(NULL);
        }
        if (pid == 0){
            process_son(nums[0], nums[1], fd_a_in, fd_a_out, fd_proc);
        }
    }
    close(fd_a_in[0]);
    close(fd_a_in[1]);
    close(fd_a_out[0]);
    close(fd_a_out[1]);
    close(fd_proc[0]);
    close(fd_proc[1]);
    while (wait(NULL) != -1){
    }
    return 0;
}
