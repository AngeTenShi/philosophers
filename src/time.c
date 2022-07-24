#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

void	my_sleep(int time_to_sleep)
{
	struct timeval start;
	struct timeval end;
	int	time;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	time = 0;
	while (time < time_to_sleep)
	{
		gettimeofday(&end, NULL);
		time = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000);
	}
}

int	get_time(int start, int end)
{
	return (end - start);
}


