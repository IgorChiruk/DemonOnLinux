#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <ctime>
#include <time.h>
#include <sys/stat.h>
#include <signal.h>

using namespace std;

void StartProc();
void QUIT_SIGNAL(int i);
void HUP_SIGNAL(int i);
void USR1_SIGNAL(int i);
void USR2_SIGNAL(int i);
void INT_SIGNAL(int i);

bool IsActive = true;

int main()
{
	int pid = fork();
	switch (pid)
	{

	case 0:
		setsid();
		chdir("/");

		//close(STDIN_FILENO);
		//close(STDOUT_FILENO);
		//close(STDERR_FILENO);
		printf("loop1\n");

		StartProc();
		printf("loop2\n");
		exit(0);

	case (-1):
		printf("Fail: unable to fork\n");
		break;

	default:
		printf("OK: demon with pid %d is created\n", pid);
		break;
	}
	return 0;
}


void StartProc()
{
	while (IsActive)
	{
		chdir("/home/");

		//int fd;
		//fd = open("/home/mer13/LogDemon.txt", O_WRONLY|O_CREAT|O_APPEND,S_IREAD|S_IWRITE);
		//char buff[] = "sdkjgnskjdfhgjkfdsfgjfgjfjfgjfgjfgjfgj\n";
		//write(fd, buff, strlen(buff));
		//close(fd);


		struct sigaction sa; /* спец. структура используемая в качестве параметра системного вызова sigaction() */
		sigset_t newset; // набор сигналов
		sigfillset(&newset);
		sigdelset(&newset, SIGQUIT);
		sigdelset(&newset, SIGHUP);
		sigdelset(&newset, SIGUSR1);
		sigdelset(&newset, SIGUSR2);
		sigdelset(&newset, SIGINT);
		sigdelset(&newset, SIGTERM);
		
		//sigemptyset(&newset); // инициализирует набор сигналов, указанный в newset, и "очищает" его от всех сигналов
		//sigaddset(&newset, SIGHUP); // добавляем сигнал SIGHUP в наш набор  

		
		sigprocmask(SIG_BLOCK, &newset, 0); // добавляем набор newset в группу заблокированных

		//SIGQUIT
		sa.sa_handler = QUIT_SIGNAL; // добавляем в структуру типа  sigaction указатель на функцию обработчик сигнала
		sigaction(SIGQUIT, &sa, 0); /* этим вызовом с учётом всех предыдущих действий
						мы назначили нашему процессу обработчик term_handler на случай получения сигнала SIGTERM
						- т.е. сигнала "предложения завершиться"*/

		//SIGTERM
		sigaction(SIGTERM, &sa, 0); 

		//SIGHUP
		sa.sa_handler = HUP_SIGNAL;
		sigaction(SIGHUP, &sa, 0);

		//SIGUSR1
		sa.sa_handler = USR1_SIGNAL;
		sigaction(SIGUSR1, &sa, 0);

		//SIGUSR2
		sa.sa_handler = USR2_SIGNAL;
		sigaction(SIGUSR2, &sa, 0);

		//SIGINT
		sa.sa_handler = INT_SIGNAL;
		sigaction(SIGINT, &sa, 0);
	}
}



void QUIT_SIGNAL(int i) 
{
	//Параметр -3;-15
	//Время
	time_t time(NULL);
	tm *local;
	local = localtime(&time);

	//Файл
	int fd;
	fd = open("/home/mer13/LogDemon.txt", O_WRONLY|O_CREAT|O_APPEND,S_IREAD|S_IWRITE);
	char *T = asctime(local);
	char buff[] = " receive signal: QUIT\n";
	write(fd, T, strlen(T));
	write(fd, buff, strlen(buff));
	close(fd);

	IsActive = false;
	printf("OK: demon with pid %d is destroyed\n", getpid());
	exit(1);
}

void HUP_SIGNAL(int i)
{
	//Параметр -1
	//Время
	time_t time(NULL);
	struct tm *local;
	local = localtime(&time);

	//Файл
	int fd;
	fd = open("/home/mer13/LogDemon.txt", O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	char *T = asctime(local);
	char buff[] = " receive signal: QUIT\n";
	write(fd, T, strlen(T));
	write(fd, buff, strlen(buff));
	close(fd);
}

void USR1_SIGNAL(int i)
{
	//Параметр -10
	//Время
	time_t time(NULL);
	struct tm *local;
	local = localtime(&time);

	//Файл
	int fd;
	fd = open("/home/mer13/LogDemon.txt", O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	char *T = asctime(local);
	char buff[] = " receive signal: QUIT\n";
	write(fd, T, strlen(T));
	write(fd, buff, strlen(buff));
	close(fd);
}

void USR2_SIGNAL(int i)
{
	//Параметр -12
	//Время
	time_t time(NULL);
	struct tm *local;
	local = localtime(&time);

	//Файл
	int fd;
	fd = open("/home/mer13/LogDemon.txt", O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	char *T = asctime(local);
	char buff[] = " receive signal: QUIT\n";
	write(fd, T, strlen(T));
	write(fd, buff, strlen(buff));
	close(fd);
}

void INT_SIGNAL(int i)
{
	//Параметр -2
	//Время
	time_t time(NULL);
	struct tm *local;
	local = localtime(&time);

	//Файл
	int fd;
	fd = open("/home/mer13/LogDemon.txt", O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	char *T = asctime(local);
	char buff[] = " receive signal: QUIT\n";
	write(fd, T, strlen(T));
	write(fd, buff, strlen(buff));
	close(fd);
}