#include <stdio.h>
#include <sched.h>
#include <unistd.h>

int main(){
    int max, min, policy;

    policy = sched_getscheduler(0);

    switch (policy)
    {
        case SCHED_OTHER:
            printf("Política: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Política: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Política: SCHED_RR\n");
            break;
    
        case -1:
            perror("getscheduler error");
            break;
    }

    if(max = sched_get_priority_max(policy) == -1){
        perror("get_priority_max error");
    }
    if(min = sched_get_priority_min(policy) == -1){
        perror("get_priority_min error");
    }

    printf("Max: %d, Min: %d\n", max, min);

    return 0;
}