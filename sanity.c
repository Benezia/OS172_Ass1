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

	printf(1, "#%d-\n",status);
	printf(1, "start time: %d\n",myPerf->ctime);
	printf(1, "end time: %d\n",myPerf->ttime);
	printf(1, "sleep time: %d\n",myPerf->stime);
    printf(1, "runnable time: %d\n",myPerf->retime);
    printf(1, "running time: %d\n",myPerf->rutime);
    printf(1, "turnaround time: %d\n",myPerf->ttime-myPerf->ctime);
    printf(1, "\n");
}

void work2(int fd){

	
	int i;
	char buff[1];
	buff[0] = 'a';


	 for (i=0;i< 1000 ;i++){
	 		
	 	write(fd, buff, 1);
	}

	

	


}

void work(){
	int i;

	char src[1000];
	for (i=0;i<100000000;i++){
		src[i % 1000]= src[1];
	}

  //   char * dest = (char *)malloc(strlen(src));
	 // for (i=0;i<strlen(src);i++){
	 // 	dest[i] = src[i];
	 // }
}


int main() {
    int status;
    struct perf  myPerf;
    int deadpool = 30;
    int fd;



	fd = open("/bin/IOtest", 1);
	if (fd == -1){
		printf(1,"fail to open file\n");
		exit(1);
	}

  //  policy(1);

    int i;
    for (i=0; i < deadpool; i++){
	    if (fork()==0){

	    	if (i%2==0){
	    		work();
	    	}
	    	else{
	    		work2(fd);
	    	}

	    	//if (i==27 || i==28 || i==29 ){priority(200);}	    	
	    	printf(2,"\n");	

	    	exit(i);
	    }
	}

	close(fd);

	for (i=0; i<deadpool; i++){
		wait_stat(&status, &myPerf);
		printStat(&myPerf, status);
	}

	return 0;
}
