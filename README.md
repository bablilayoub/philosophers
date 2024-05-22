# Philosophers: I Never Thought Philosophy Would Be So Deadly

## Summary
This project introduces the basics of threading in process management, demonstrating how to create threads and utilize mutexes to handle concurrent operations safely.

## Version: 11

## Contents
1. [Introduction](#introduction)
2. [Common Instructions](#common-instructions)
3. [Overview](#overview)
4. [Global Rules](#global-rules)
5. [Mandatory Part](#mandatory-part)
6. [Bonus Part](#bonus-part)
7. [Submission and Peer-Evaluation](#submission-and-peer-evaluation)

## Introduction
Philosophy, derived from the Greek word "philosophia" (love of wisdom), involves studying fundamental questions about existence, knowledge, values, reason, mind, and language. This project metaphorically uses the classic "Dining Philosophers" problem to teach threading and concurrency.

## Common Instructions
- Code must be written in C and follow the specified Norm.
- Handle memory allocation properly, avoiding leaks.
- Submit a Makefile for compilation.
- Include rules for compiling bonuses separately if applicable.
- Create and use test programs for easier evaluation.

## Overview
In this assignment, philosophers sit at a round table with a bowl of spaghetti and forks. Each philosopher alternates between eating, thinking, and sleeping. Philosophers must pick up two forks to eat and put them down after finishing. The simulation ends if a philosopher dies of starvation.

## Global Rules
- Programs must not use global variables.
- Arguments: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, and optionally number_of_times_each_philosopher_must_eat.
- Log state changes with precise timestamps.
- Avoid data races.

## Mandatory Part
### Program Name
`philo`

### Files
- Turn in: Makefile, *.h, *.c in `philo/`
- Makefile rules: `NAME`, `all`, `clean`, `fclean`, `re`

### External Functions Allowed
`memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

### Description
Implement philosophers using threads and mutexes. Each philosopher is a thread and uses mutexes to manage forks.

## Bonus Part
### Program Name
`philo_bonus`

### Files
- Turn in: Makefile, *.h, *.c in `philo_bonus/`
- Makefile rules: `NAME`, `all`, `clean`, `fclean`, `re`

### External Functions Allowed
`memset`, `printf`, `malloc`, `free`, `write`, `fork`, `kill`, `exit`, `pthread_create`, `pthread_detach`, `pthread_join`, `usleep`, `gettimeofday`, `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`

### Description
Implement philosophers using processes and semaphores. Forks are managed by semaphores, and each philosopher is a separate process.

## Submission and Peer-Evaluation
Submit the project to the assigned Git repository. Ensure correct file names and directory structures:
- Mandatory part: `philo/`
- Bonus part: `philo_bonus/`

Ensure that the mandatory part is complete and functional to have the bonus part evaluated.
