#include "init.h"

int setup_mounts(){
    const char *dirs[] = {"/proc", "/sys", "/dev", "/run", "/dev/pts"};
    for (int i = 0; i < 5; i++) {
        mkdir(dirs[i], 0755); 
    }

    printf("mounting mounts\n");
    if (mount("proc", "/proc", "proc", 0, NULL) != 0) {
        fprintf(stderr, "Error mounting /proc: %s\n", strerror(errno));
        return 1;
    }
    printf("/proc mounted successfully.\n");
    if (mount("sysfs", "/sys", "sysfs", 0, NULL) != 0) {
	fprintf(stderr, "Error mounting /sys: %s\n", strerror(errno));
	return 1;
    }
    printf("/sys mounted succesfully \n");
    if (mount("devtmpfs", "/dev", "devtmpfs", 0, NULL) != 0) {
	fprintf(stderr, "Error mounting /dev: %s\n", strerror(errno));
	return 1;
    }
    printf("/dev mounted successfully \n");
    if (mount("tmpfs", "/run", "tmpfs", 0, NULL) != 0) {
	fprintf(stderr, "Error mounting /run: %s\n", strerror(errno));
	return 1;
    }
    printf("/run mounted successfully\n");
    if(mount("devpts", "/dev/pts", "devpts", 0, NULL) != 0){
	fprintf(stderr, "Error mounting /dev/pts: %s\n", strerror(errno));
	return 1;
    }
    printf("/dev/pts mounted successfully\n");
    printf("all mounted successfully \n");
    return 0;
}

int setup_PATH_env(){
    clearenv();
    printf("setting PATH and basic ENV variables\n");
    if(putenv("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin") != 0){
	fprintf(stderr, "couldnt set PATH: %s\n", strerror(errno));
	return 1;
    }
    else if(putenv("HOME=/root") != 0){
	fprintf(stderr, "couldnt set ENV: %s\n", strerror(errno));
	return 1;
    }
    else if(putenv("TERM=linux") != 0){
	fprintf(stderr, "couldnt set ENV: %s\n", strerror(errno));
	return 1;
    }
    printf("PATH and ENV set set\n");
    return 0;
}


