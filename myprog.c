#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main() {
    int status;
    //char* r = "r";
    if (fork() > 0) {
        wait(&status);
        if (status != 15) {
            printf(2, "Status: %d\n", status);
            printf(1, "Fail\n");
        } else {
            printf(1, "Passed\n");
        }
        exit(0);
    } else {
    return 15;
    }
}