/* A simple race - test symaddr */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

namespace hg05_race2
{

struct foo {
	struct bar {
		int plop[22];
		char biff;
	} poot[11];
};

static void *th(void *v)
{
	struct foo *f = (struct foo *)v;

	f->poot[5].plop[11]++;

	return 0;
}

int hg05_race2()
{
	struct foo foo;
	foo.poot[5].plop[11] = 0;
	pthread_t a, b;

	pthread_create(&a, NULL, th, &foo);	
	sleep(1);		/* force ordering */
	pthread_create(&b, NULL, th, &foo);

	pthread_join(a, NULL);
	pthread_join(b, NULL);

	return foo.poot[5].plop[11];
}

};
