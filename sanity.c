#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


struct perf {
  int ctime;
  int ttime;
  int stime;
  int retime;
  int rutime;
};

void printStat(struct perf * myPerf, int status){
	printf(1, "%d\tstart\t\t%d\n",status, myPerf->ctime);
	printf(1, "%d\tend\t\t%d\n",status, myPerf->ttime);
	printf(1, "%d\tsleep\t\t%d\n",status, myPerf->stime);
    printf(1, "%d\trunnable\t%d\n",status, myPerf->retime);
    printf(1, "%d\trunning\t\t%d\n",status, myPerf->rutime);
    printf(1, "%d\tturnaround\t%d\n",status, myPerf->ttime-myPerf->ctime);
    printf(1, "%d\tSpent %d\% as runnable\n",status, (myPerf->retime*100/(myPerf->ttime-myPerf->ctime)));
    printf(1, "%d\tSpent %d\% in sleep\n",status, (myPerf->stime*100/(myPerf->ttime-myPerf->ctime)));
    printf(1, "\n");
}


void fib(int n) {
	if (n <= 1)
		return;
	fib(n-1);
	fib(n-2);
}


void workIO(){
	int i;
	for (i=0; i<1750 ;i++)
	 	sleep(1);
}

void workCPU(){
	fib(38);
}


void insanity(int deadpool, int testNum, void evenFunc(), void oddFunc()) {
    int status;
    struct perf myPerf;
    int i; 				//# of procedure
    int j;				//# of test
    for (j=0; j < testNum; j++) {
	    for (i=0; i < deadpool; i++){
		    if (fork()==0){
		    	/*
		    	if (i%9 == 2 || i == 28) // 2, 11, 20, 28, 29
		    		priority(100);
		    	if (i%11 == 1) // 1, 12, 23
		    		priority(1);
				*/
		    	if (i%2 == 0){
		    		evenFunc();
		    	}
		    	else{
		    		oddFunc();
		    	}

		    	exit(i);
		    }
		}
		for (i=0; i<deadpool; i++){
			wait_stat(&status, &myPerf);
			printStat(&myPerf, status);
		}
	}
}

int main() {
	//policy(1);
    insanity(30,1, &workIO, &workCPU);
    printf(1, "\n");
    return 0;
}

