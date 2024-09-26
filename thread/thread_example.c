/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:05:43 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/18 14:03:04 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

// Each thread will count TIMES_TO_COUNT times
# define TIMES_TO_COUNT 21000

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

// This structure contains the count as well as the mutex
// that will protect the access to the variable
typedef struct	s_counter
{
	pthread_mutex_t count_mutex;
	unsigned int count;
}	t_counter;


// thread routine is the function that the thread invokes rigth after its 
// creation. The thread ends at the end of this function.

void	*thread_routine(void *data)
{
	// Each thread starts here
	pthread_t tid;
	t_counter *counter;	// pointer to the structure in main
	unsigned int i;

	// The pthread_self() function provides this threads own ID
	tid = pthread_self();
	counter = (t_counter *)data;
	// Print the count before this thread starts iterating
	// In order to read the value of count, we lock the mutex
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Count at thread start = %u.%s\n",
			YELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		// Iterates TIME_TO_COUNT times
		// Increment the counter at each iteration
		// Lock the mutex for the duration of the incrementation
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
		i++;
	}
	// Print the final count when this thread finishes its
	// own count, without forgetting to lock the mutex
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Final count = %u.%s\n", 
			BYELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	return (NULL); // The thread ends here
}

int	main(void)
{
	pthread_t tid1;	// First threads ID
	pthread_t tid2; // Second threads ID
	
	// Structure contaning the threads total count
	t_counter counter;
	
	// There is only ine thread here (main thread), so we can safely
	// initialize count without using the mutex
	counter.count = 0;
	
	// Initialize the mutex
	pthread_mutex_init(&counter.count_mutex, NULL);
	// Since each thread count TIMES_TO_COUNT times and that
	// we have 2 threads, we expect the final count to be
	// 2 * TIMES_TO_COUNT
	printf("Main: Expected count is %s%u%s\n", GREEN,
			2 * TIMES_TO_COUNT, NC);
	
	// Creating the first thread that will go
	// execute its thread_routine function.
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("Main: Created first thread [%ld]\n", tid1);
	// Creating the second thread that will also execute thread_routine
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("Main: Created second thread [%ld]\n", tid2);
	// the main thread waits for the new threads to end
	// with pthread_join
	pthread_join(tid1, NULL);
	printf("Main: JOining first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joining second thread [%ld]\n", tid2);

	// Final count evaluation:
	if (counter.count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERROR ! Total count is %u%s\n", RED, counter.count, NC);
	else
		printf("%sMain: OK. Total count is %u%s\n", GREEN, counter.count, NC);
	pthread_mutex_destroy(&counter.count_mutex);
	return (0);
}
