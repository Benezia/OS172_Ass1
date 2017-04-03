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
	int fd;
	char buff[1];
	buff[0] = 'a';
	fd = open("/bin/IOtest", 1);
	if (fd == -1){
		printf(1,"fail to open file\n");
		exit(1);
	}

	for (i=0;i< 120 ;i++)
	 	write(fd, buff, 1);
	close(fd);
}

void workCPU(){
	fib(40);
}


int main() {
    int status;
    struct perf  myPerf;
    int deadpool = 6;

    //policy(1);

    int i;
    for (i=0; i < deadpool; i++){
	    if (fork()==0){

	    	if (i%2==0){
	    		workIO();
	    	}
	    	else{
	    		workCPU();
	    	}

	    	//if (i==27 || i==28 || i==29 ){priority(200);}	    	
	    	exit(i);
	    }
	}


	for (i=0; i<deadpool; i++){
		wait_stat(&status, &myPerf);
		printStat(&myPerf, status);
	}

	return 0;
}
