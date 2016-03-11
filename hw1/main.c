#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <sys/time.h>

extern void random_length_task();

int main(int argc, char *argv[]){

    int n = 10;
    if( argc == 2 ){
        char* endptr = NULL;
        n = strtol(argv[1], &endptr, 0);
        if( endptr == argv[1] ){
            /* first char of argument is not a number */
            perror("argument is not a number\n");
        }
        if( n == 0 ){
            perror("argument is 0\n");
        }
    }

    int total_round = n;
    srand(time(0) ^ getpid());

    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    while( n-- > 0 ){
        // printf("Round %d\n", total_round - n);

        random_length_task();

        struct timeval task_finish, rest_of_time;
        gettimeofday(&task_finish, NULL);

        struct timeval expected_time = {start_time.tv_sec, start_time.tv_usec + 1000*100*(total_round - n)};
        expected_time.tv_sec += expected_time.tv_usec / 1000000; // 10^-6
        expected_time.tv_usec %= 1000000; // 10^-6

        timersub(&expected_time, &task_finish, &rest_of_time);

        struct timespec sleep_time;
        sleep_time.tv_sec = rest_of_time.tv_sec;
        sleep_time.tv_nsec = rest_of_time.tv_usec * 1000;
        nanosleep(&sleep_time, NULL);

        // printf("start time %ld.%06ld\n", start_time.tv_sec, start_time.tv_usec);
        // printf("task finish time %ld.%06ld\n", task_finish.tv_sec, task_finish.tv_usec);
        // printf("expected time %ld.%06ld\n", expected_time.tv_sec, expected_time.tv_usec);
        // printf("rest of time %ld.%06ld\n", rest_of_time.tv_sec, rest_of_time.tv_usec);
        // printf("\n");
    }

    return 0;
}


