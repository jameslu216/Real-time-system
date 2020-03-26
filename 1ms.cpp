#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>

#include <iostream>
#include <chrono>
#include <cmath>

void setSchedulingPolicy (int policy, int priority)
{
    sched_param sched;
    sched_getparam(0, &sched);
    sched.sched_priority = priority;
    if (sched_setscheduler(0, policy, &sched)) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }
}

void workload_1ms (void)
{
        int repeat = 100000; // tune this for the right amount of workload
        double testnum=0;
        for (int i = 0; i <= repeat; i++)
        {
                if(i%2==0)
                  testnum+=10;
                else
                  testnum/=2;// add some computation here (e.g., use sqrt() in cmath)
        }
        printf("%g\n",testnum);
        int count=1;
        for(;count<100000000;count++)
        {
          if(count%2==0 && count%3==0 && count%5==0 && count%7==0 && count%9==0 && count%11==0)
          break;
          //printf("in");
        }
      printf("%d \n",count );
}

int main (void)
{
        setSchedulingPolicy (SCHED_FIFO, 99);
        std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
        workload_1ms ();
        std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
        const int delta = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        std::cout << delta << std::endl;

        return 0;
}
