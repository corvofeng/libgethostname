/*
 *=======================================================================
 *    Filename:libgethostname.c
 *
 *     Version: 1.0
 *  Created on: September 21, 2020
 *
 *      Author: corvo
 *=======================================================================
 */

// .__  ._____.                   __  .__                    __                             
// |  | |__\_ |__    ____   _____/  |_|  |__   ____  _______/  |_  ____ _____    _____   ____
// |  | |  || __ \  / ___\_/ __ \   __\  |  \ /  _ \/  ___/\   __\/    \\__  \  /     \_/ __ \
// |  |_|  || \_\ \/ /_/  >  ___/|  | |   Y  (  <_> )___ \  |  | |   |  \/ __ \|  Y Y  \  ___/
// |____/__||___  /\___  / \___  >__| |___|  /\____/____  > |__| |___|  (____  /__|_|  /\___  >
//              \//_____/      \/          \/           \/            \/     \/      \/     \/



/**
 * Help user fake hostname, for example:
 *  > FAKEHOST=xxxx LD_PRELOAD="./libgethostname.so" hostname
 *  > xxxx
 */

#ifndef RTLD_NEXT
#  define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <errno.h>
#include <unistd.h>


int gethostname(char *__name, size_t __len);

int min(int x, int y) 
{ 
    return (x < y) ? x : y;
}

int gethostname(char *__name, size_t __len) {
    int (*libc_gethostname)(char *__name, size_t __len);

    *(void **)(&libc_gethostname) = dlsym(RTLD_NEXT, "gethostname");
    if(dlerror()) {
      errno = EACCES;
      return -1;
    }

    const char* s = getenv("FAKEHOST");
    if (s==NULL) {
        printf("Can't get fake hostname, return real host\n");
        return (*libc_gethostname)(__name, __len);
    }
    strncpy(__name, s, min(strlen(s), __len));
    return 0;
}
