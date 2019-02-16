/*
The problem is as follows:
Five philosophers are seated around a circular table.
Each philosopher has a plate of spaghetti.
The spaghetti is so slippery that a philosopher needs two forks to eat it.
Between each pair of plates is one fork.

The life of a philosopher consists of alternating periods of eating and thinking.
When a philosopher gets sufficiently hungry, she tries to aquire her left
and right forks, one at a time, in either order.
If successful in acquiring two forks, she eat for a while, then puts down the
forks, and continues to think.

Key question:
Can you write a program for each philosopher that does what it
is supposed to do and never get stuck?

Pseudocode from figure 2-47, "Modern Operating Systems (4th ed.)", Tanenbaum
*/

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <semaphore.h>

#define SHARED		0		/* 0 = thread-, !0 = process-sharing */
#define RUNS		10		/* In total how often they can eat */
#define N		5		/* number of philosophers */
#define LEFT		(i+N-1)%N	/* number of i's left neighbor */
#define RIGHT		(i+1)%N		/* number of i's right neighbor */
#define THINKING	0		/* philosopher is thinking */
#define HUNGRY		1		/* philosopher is trying to get forks */
#define EATING		2		/* philosopher is eating */

void *philosopher(void*);				
void take_forks(int);				
void put_forks(int);
void test(int);
	
int state[N];			/* array to keep track of everyone's state */
sem_t mutex;			/* mutual exclusion for critical regions */
sem_t s[N];			/* one semaphore per philosopher */
int runs = 0;			/* how often a philosopher has eaten til now */

int main()
{
	pthread_t threads[N];	// Threads 
	int num[N];		// Numbers with each their own address

	/* Fill number array */
	for(int i = 0; i < N; i++)
		num[i] = i;

	/* Initialize semaphores */
	sem_init(&mutex, SHARED, 1);
	for(int i = 0; i < N; i++)
		sem_init(&s[i], SHARED, 0);

	printf("Threads started\n");

	/* Create threads */
	for(int i = 0; i < N; i++)
		pthread_create(&threads[i], NULL, philosopher, (void*) &num[i]);
	
	/* Wait for threads to finish */
	for(int i = 0; i < N; i++)
		pthread_join(threads[i], NULL);

	return 0;
}

void *philosopher(void *args)		/* i: philosopher from 0 to N-1 */
{
	while (runs < RUNS)
	{
		sleep(random() % 1 + 2);/* philosopher is thinking */		
		take_forks(*(int*)args);/* aquire two forks or block */
		sleep(random() % 1 + 1);/* yum-yum, spaghetti */
		put_forks(*(int*)args);	/* put both forks back on table */
	}
	return 0;
}

void take_forks(int i)
{
	sem_wait(&mutex);		/* enter critical region */
	state[i] = HUNGRY;		/* record that philosopher i = hungry */
	printf("Philosopher %d is now hungry\n", i);
	test(i);			/* try to acquire 2 forks */
	sem_post(&mutex);		/* exit critical region */
	sem_wait(&s[i]);		/* block if forks were not acquired */
}

void put_forks(int i)
{
	sem_wait(&mutex);		/* enter critical region */
	state[i] = THINKING;		/* philosopher has finished eating */
	printf("Philosopher %d is now thinking\n", i);
	runs++;				/* increase runs */
	test(LEFT);			/* see if left neighbor can now eat */
	test(RIGHT);			/* see if right neighbor can now eat */
	sem_post(&mutex);		/* exit critical region */
}

void test(int i)
{
	if (state[i] == HUNGRY && state[LEFT] != EATING 
	    	&& state[RIGHT] != EATING) {
		state[i] = EATING;
		printf("Philosopher %d is now eating\n", i);
		sem_post(&s[i]);
	}
}



