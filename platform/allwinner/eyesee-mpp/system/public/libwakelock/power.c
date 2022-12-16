/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "power.h"
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

#define LOG_TAG "power"
#include <cutils/log.h>

/**/
struct wake_lock_p
{
	char         *lock_name;
	unsigned int pid;
	unsigned int index;
};
#define MAX_INDEX 32
static unsigned int wake_lock_count = 0;
static struct wake_lock_p wake_lock_m[MAX_INDEX] = {0};



/**/


enum {
    ACQUIRE_PARTIAL_WAKE_LOCK = 0,
    RELEASE_WAKE_LOCK,
    OUR_FD_COUNT
};

const char * const OLD_PATHS[] = {
    "/sys/android_power/acquire_partial_wake_lock",
    "/sys/android_power/release_wake_lock",
};

const char * const NEW_PATHS[] = {
    "/sys/power/wake_lock",
    "/sys/power/wake_unlock",
};

//XXX static pthread_once_t g_initialized = THREAD_ONCE_INIT;
static int g_initialized = 0;
static int g_fds[OUR_FD_COUNT];
static int g_error = 1;

static int64_t systemTime()
{
    struct timespec t;
    t.tv_sec = t.tv_nsec = 0;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec*1000000000LL + t.tv_nsec;
}

static int
open_file_descriptors(const char * const paths[])
{
    int i;
    for (i=0; i<OUR_FD_COUNT; i++) {
        int fd = open(paths[i], O_RDWR);
        if (fd < 0) {
            fprintf(stderr, "fatal error opening \"%s\"\n", paths[i]);
            g_error = errno;
            return -1;
        }
        g_fds[i] = fd;
    }

    g_error = 0;
    return 0;
}

static inline void
initialize_fds(void)
{
    // XXX: should be this:
    //pthread_once(&g_initialized, open_file_descriptors);
    // XXX: not this:
    if (g_initialized == 0) {
        if(open_file_descriptors(NEW_PATHS) < 0)
            open_file_descriptors(OLD_PATHS);
        g_initialized = 1;
    }
}

int
acquire_wake_lock(int lock, const char* id)
{
    initialize_fds();
	if (g_error) return g_error;
/*check  lock */
	int i = 0;
	for(i = 0; i < wake_lock_count; i++)
	{		
		if (strcmp(id, wake_lock_m[i].lock_name) == 0)
			{
				db_msg("already accquired!");
				return 0;
			}						
	}

	if(i == MAX_INDEX){
		msg_dbg("error, wake lock accquire failed. ");
		return -1;
	}
/**/
//    ALOGI("acquire_wake_lock lock=%d id='%s'\n", lock, id);

    int fd;
    if (lock == PARTIAL_WAKE_LOCK) {
        fd = g_fds[ACQUIRE_PARTIAL_WAKE_LOCK];
    }
    else {
        return EINVAL;
    }

	wake_lock_m[i].lock_name = (char *)id;
	wake_lock_m[i].pid       = getppid();
	wake_lock_m[i].index     = i;
	wake_lock_count ++;

    return write(fd, id, strlen(id));
}

int
release_wake_lock(const char* id)
{
    initialize_fds();
    if (g_error) return g_error;

//    ALOGI("release_wake_lock id='%s'\n", id);
	int i = 0, j = 0;
	for(i = 0; i < wake_lock_count; i++)
	{		
		if (strcmp(id, wake_lock_m[i].lock_name) == 0)
			break;
	}
	if(i == wake_lock_count){
		msg_dbg("error wake lock names !");
		return -1;
	}

	//update wake lock table
	wake_lock_count--;
	for(j = i; j< wake_lock_count; j++){
		wake_lock_m[j] = wake_lock_m[j+1];
	}

    ssize_t len = write(g_fds[RELEASE_WAKE_LOCK], id, strlen(id));
    return len >= 0;
}
