#pragma once
#include "all.h"
#include <sys/mount.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

extern int setup_mounts();
extern int setup_PATH_env();

