/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:30:38 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/18 13:05:21 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>


// thread -> store the ID of the thread
// attr -> change the default attribute of new thread
// start_routine -> the function where the thread will start its execution
// arg -> a pointer towards an argument to pass to the threads start_routine function


// Creating a Thread
int	pthread_create(pthread_t *restrict thread,
				const phtread_attr_t *restrict attr,
				void *(*start_routine)(void *),
				void *restrict arg);

// Joinig or Detaching Threads
// thread -> the id of the thread that this thread should wait for
// retval -> variable that can contain the return value of the threads routine function
int	pthread_join(pthread_t thread, void **retval); // block the execution of a thread until another thread finishes

int	pthread_detach(pthread_t thread); // Detach the thread to tell the operating system that it can reclaim its resources right away when it finishes its execution
