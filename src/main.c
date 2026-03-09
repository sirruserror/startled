#include "all.h"
#include <fcntl.h>
#include "init.h"

int main(){
    int fd = open("/dev/console", O_RDWR);
    dup2(fd, 0); dup2(fd, 1); dup2(fd, 2);
    if (fd > 2) close(fd);
    printf("startled init, 2026 copyright sirruserror under the BSD 3 clause");
    printf("version: %d", STARTLED_VERSION);
    if(setup_mounts() != 0){
	fprintf(stderr, "couldnt mount inital mounts\n");
	while(1) sleep(100); 
    }
    else if(setup_PATH_env() != 0){
	fprintf(stderr, "failed to set PATH and ENV variables\n");
	while(1) sleep(100); 
    }
    else if(setup_drivers() != 0){
	fprintf(stderr, "failed to start drivers\n");
	;
    }
    // TODO: add services 

    printf("main init done\n");
    char *args[] = {"/bin/sh", NULL};
    execv("/bin/sh", args);

    while(1) sleep(100); 
    return 0;
}
