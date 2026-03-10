#include "all.h"
#include <fcntl.h>
#include "init.h"
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/reboot.h>
#include <unistd.h>


void power_off() {
    printf("signaling all processes to terminate...\n");
    kill(-1, SIGTERM);
    sleep(2);

    printf("killing remaining processes...\n");
    kill(-1, SIGKILL);

    printf("syncing filesystems...\n");
    sync();
    printf("powering off.\n");
    reboot(RB_POWER_OFF);
}

void signal_handler(int sig) {
    if (sig == SIGINT || sig == SIGUSR1) {
        power_off();
    }
}

void sigchld_handler(int sig) {
    int saved_errno = errno;
    
    while (waitpid(-1, NULL, WNOHANG) > 0);
    
    errno = saved_errno;
}

int main(){
    int fd = open("/dev/console", O_RDWR);
    dup2(fd, 0); dup2(fd, 1); dup2(fd, 2); // stdin, stdout, stderr
    if (fd > 2) close(fd);
    printf("startled init, 2026 copyright sirruserror under the BSD 3 clause\n");
    printf("version: %d\n", STARTLED_VERSION);
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    struct sigaction sa_reboot;
    sa_reboot.sa_handler = signal_handler;
    sigemptyset(&sa_reboot.sa_mask);
    sa_reboot.sa_flags = 0;
    sigaction(SIGINT, &sa_reboot, NULL);
    sigaction(SIGUSR1, &sa_reboot, NULL);
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
       perror("sigaction");
       exit(1);
    }
    if(setup_mounts() != 0){
	fprintf(stderr, "couldnt mount inital mounts\n");
	while(1) sleep(100); 
    }
    else if(setup_PATH_env() != 0){
	fprintf(stderr, "failed to set PATH and ENV variables\n");
	while(1) sleep(100); 
    }

    // TODO: add services 

    while (1) {
    	pid_t pid = fork();
    	if (pid == 0) {
        	char *args[] = {"/bin/sh", NULL};
        	execv("/bin/sh", args);
        	_exit(1);
    	} else if (pid > 0) {
        	int status;
        	waitpid(pid, &status, 0); 
        	printf("Shell exited, respawning...\n");
    	} else {
        	perror("fork");
        	sleep(5);
	}
   } 

}
