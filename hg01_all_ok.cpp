/* All OK */
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

namespace hg01_all_ok
{

static pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;

static int shared = 0;
static char *ptr;
static bool malloced = false;

static void breakme(void)
{
   if (shared == 1)
      memset (ptr, 0x55, 1000);
}

static void *th(void *v)
{
	pthread_mutex_lock(&mx);
	shared++;
        if (shared == 1) {
           ptr = (char*)malloc (1008);
           malloced = true;
           breakme();
        }
        if (shared == 2) {
           free (ptr);
           malloced = false;
           breakme();
        }
	pthread_mutex_unlock(&mx);

	return 0;
}

bool hg01_all_ok(void)
{
	pthread_t a, b;

	pthread_mutex_lock(&mx);
	pthread_mutex_unlock(&mx);

	pthread_create(&a, NULL, th, NULL);	
	pthread_create(&b, NULL, th, NULL);

	pthread_join(a, NULL);
	pthread_join(b, NULL);

	return malloced;
}

};
