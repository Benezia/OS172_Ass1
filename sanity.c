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


void printStat(struct perf * myPerf, int status, int iteration){
/*
	printf(1, "%d\tstart\t\t%d\n",status, myPerf->ctime);
	printf(1, "%d\tend\t\t%d\n",status, myPerf->ttime);
	printf(1, "%d\tsleep\t\t%d\n",status, myPerf->stime);
    printf(1, "%d\trunnable\t%d\n",status, myPerf->retime);
    printf(1, "%d\trunning\t\t%d\n",status, myPerf->rutime);
    printf(1, "%d\tturnaround\t%d\n",status, myPerf->ttime-myPerf->ctime);
    printf(1, "%d\tSpent %d\% as runnable\n",status, (myPerf->retime*100/(myPerf->ttime-myPerf->ctime)));
    printf(1, "%d\tSpent %d\% in sleep\n",status, (myPerf->stime*100/(myPerf->ttime-myPerf->ctime)));
    printf(1, "\n");
*/
	printf(1, "%d\t%d\t%d\t%d\t%d\t%d\n",iteration, status, myPerf->stime, myPerf->retime, myPerf->rutime, myPerf->ttime-myPerf->ctime);

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
	fib(41);
}


int main() {
    int status;
    struct perf  myPerf;

    //policy(1);
    int deadpool = 1;	//Total procedures to run
    int i; 				//# of procedure
    int j;				//# of test

    for (j=0; j < 10; j++) {
	    for (i=0; i < deadpool; i++){
		    if (fork()==0){
		    	//if (i%9 == 0)
		    	//	priority(200);    	

		    	if (i%2 == 0){
		    		//priority(100);
		    		workCPU();
		    	}
		    	else{
		    		workCPU();
		    	}

		    	exit(i);
		    }
		}

		for (i=0; i<deadpool; i++){
			wait_stat(&status, &myPerf);
			printStat(&myPerf, status, j+1);
		}
	}

	return 0;
}
