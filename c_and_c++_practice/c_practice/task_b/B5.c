#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

static void
solution(void)
{
    /// WRITE HERE
    int empt_seq = 0, frst_seq = 1;
    long long x, mxp=0, minmx=0;
    while (1){
        scanf("%lld", &x);
        if (x == 0){
            empt_seq++;
            if (empt_seq == 1){
                if (mxp < 0){
                    printf("EMPTY\n");
                    break;
                }
                minmx = mxp;
            }
            else{
                if (mxp < 0){
                    printf("%lld\n", minmx);
                    break;
                }
                else{
                    if (mxp < minmx){
                        minmx = mxp;
                    }
                }
            }
            frst_seq = 1;
        }
        else{
            if (frst_seq == 1){
                mxp = x;
            }
            else{
                if (mxp < x){
                    mxp = x;
                }
            }
            frst_seq = 0;
        }
    }
    ///
}

enum { MAX_LEN = 128 };

int
main(void)
{
    typedef struct {
        unsigned len;
        int input[MAX_LEN];
        const char *answer;
    } Test;

    static const char * const empty = "EMPTY\n";
    static Test tests[] = {
        { .len = 2, .input = { -1, 0, }, .answer = empty, },
        { .len = 4, .input = { 1, 0, -1, 0, }, .answer = "1\n", }, 
        { .len = 4, .input = { -1, 0, 1, 0, }, .answer = empty, },
        { .len = 5, .input = { 1, 2, 0, -1, 0, }, .answer = "2\n", },
        { .len = 5, .input = { 3, 2, 0, -1, 0, }, .answer = "3\n", },
        { .len = 6, .input = { 1, 0, 2, 0, -1, 0, }, .answer = "1\n", },
        { .len = 6, .input = { 3, 0, 2, 0, -1, 0, }, .answer = "2\n", },
        { .len = 7, .input = { 3, -1, 0, 2, 0, -1, 0, }, .answer = "2\n", },
        { .len = 7, .input = { 3, 0, 2, 0, -3, -2, 0, }, .answer = "2\n", },
        { .len = 9, .input = { 3, 0, 2, 0, -3, -2, 0, 1, 0 }, .answer = "2\n", },
    };

    for (unsigned i = 0; i < sizeof tests / sizeof *tests; ++i) {
        int fd[2], fd_in[2];
        if (pipe(fd) == -1) {
            perror("pipe-1");
            return 1;
        }
        if (pipe(fd_in) == -1) {
            perror("pipe-2");
            return 1;
        }
        if (fork() == 0) {
            dup2(fd[1], 1);
            dup2(fd_in[0], 0);
            close(fd[0]);
            close(fd[1]);
            close(fd_in[0]);
            close(fd_in[1]);
            solution();
            return 0;
        }
        close(fd[1]);
        close(fd_in[0]);
        FILE *out = fdopen(fd_in[1], "w");
        if (!out) {
            perror("fdopen-out");
            return 1;
        }
        for (unsigned k = 0; k < tests[i].len; ++k) {
            fprintf(out, "%d\n", tests[i].input[k]);
        }
        fclose(out);
        close(fd_in[1]);

        FILE *in = fdopen(fd[0], "r");
        if (!in) {
            perror("fdopen-in");
            return 1;
        }

        char buf[MAX_LEN] = {0};
        if (!fgets(&buf[0], sizeof buf, in)) {
            printf("TEST %d FAILED: empty output\n", i);
            return 0;
        } else if (!strchr(&buf[0], '\n')) {
            printf("TEST %d FAILED: no newline\n", i);
            return 0;
        } else if (strcmp(buf, tests[i].answer) != 0) {
            printf("TEST %d FAILED: wrong text at output; "
                    "expected: %s; gotten: %s\n", i, tests[i].answer, buf);
            return 0;
        }

        fclose(in);
        close(fd[0]);
        int status;
        wait(&status);
        if (! WIFEXITED(status)) {
            perror("wait");
            return 1;
        }
    }

    printf("OK\n");
}
