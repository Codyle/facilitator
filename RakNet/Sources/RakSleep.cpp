#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "RakSleep.h"

void RakSleep(unsigned int ms)
{
	//Single thread sleep code thanks to Furquan Shaikh, http://somethingswhichidintknow.blogspot.com/2009/09/sleep-in-pthread.html
	//Modified slightly from the original
	pthread_mutex_t fakeMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t fakeCond = PTHREAD_COND_INITIALIZER;
	struct timespec timeToWait;
	struct timeval now;

	gettimeofday(&now,NULL);

	long seconds = ms/1000;
	long nanoseconds = (ms - seconds * 1000) * 1000000;
	timeToWait.tv_sec = now.tv_sec + seconds;
	timeToWait.tv_nsec = now.tv_usec*1000 + nanoseconds;

	if (timeToWait.tv_nsec >= 1000000000)
	{
	        timeToWait.tv_nsec -= 1000000000;
	        timeToWait.tv_sec++;
	}

	pthread_mutex_lock(&fakeMutex);
	pthread_cond_timedwait(&fakeCond, &fakeMutex, &timeToWait);
	pthread_mutex_unlock(&fakeMutex);
}
