#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"



int main() {
    int status;
    if (fork() >0) {
        wait(&status);
        if (status != 137) {
            printf(1, "Fail\n");
        } else {
            printf(1, "Passed\n");
        }
        exit(0);
    } else {
        exit(137);
    }
}