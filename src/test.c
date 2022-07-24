#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex;
struct s_all {
	 int i;
};
void *routine(void *arg)
{
	int *i = (int *)arg;
	printf("Starting threads %d\n", *i);
	usleep(100);
	printf("Stopping threads %d\n", *i);
	free(i);
}

int	main(void)
{
	pthread_t	threads[2];
	pthread_mutex_init(&mutex, NULL);
	int *arg;
	for (int i = 0; i < 30; i++)
	{
		arg = malloc(sizeof(int));
		*arg = i;
		pthread_create(&threads[i], NULL, routine, (void *)arg);
	}
	for (int i = 0; i < 30; i++)
	{
		pthread_join(threads[i],NULL);
		free(arg);
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}