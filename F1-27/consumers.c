#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#define BUFSIZE	1024
#define MAX_CON 2000
int connectsock( char *host, char *service, char *protocol );

int checkResponce(int responce, char errorMessage[]){
	if(responce<=0){	
		return 0;
	}
	return 1;
}

/*
**      Poisson interarrival times. Adapted from various sources
**      r = desired arrival rate
*/
double poissonRandomInterarrivalDelay( double r )
{
    return (log((double) 1.0 - 
			((double) rand())/((double) RAND_MAX)))/-r;
}

void* consumerMe(void* val){
	int csock = *((int *)val);
	char* product = NULL;
	int size = 0;
	int responce = write( csock, "CONSUME\r\n", 9);//consumer client connects to the server, sends
    if ( checkResponce(responce,"problem with client writing\n") == 0 ){
		close(csock);
		pthread_exit(0);
    }
    int readNum = 0;//number of chars read
	responce = read( csock, (char*) &readNum, 4);
    if ( checkResponce(responce,"problem with server read\n") == 0 ){
		close(csock);
		pthread_exit(0);
    }
    size = ntohl(readNum);
	
    product = (char*) malloc(size * sizeof(char)); // allocating memory for product
    int cc = 0;
	int readByteNum = 0;
	do{
		readByteNum += cc;
	}while(readByteNum < size  && (cc = read(csock, product + readByteNum, BUFSIZE)) > 0);
    printf("Product size is %d\n", size);
	fflush(stdout);
	//write txt file
    char filename[32];
    sprintf(filename, "%ld.txt", pthread_self());
    int fileDescriptor = open(filename, O_WRONLY | O_CREAT, 0777);
	responce = write(fileDescriptor, product, size);
    if(checkResponce(responce,"problem with writing to file\n") == 0){
        close(fileDescriptor);
		free(product);
		close(csock);
		pthread_exit(0);
    }
    close(fileDescriptor);
	free(product);
    close(csock);
    pthread_exit(0);
}
 
int main( int argc, char *argv[] ) {
	char *service;		
	char *host = "localhost";
    int consumerId;
	double rate;
	if(argc != 5){
		fprintf( stderr, "argc != 5" );
		exit(-1);
	}
	host = argv[1];
    service = argv[2];
    consumerId = atoi(argv[3]);
	rate = atof(argv[4]);
	
	if(rate <= 0){
		printf("rate <= 0, no clue what to do\n");
		exit(-1);
	}else if(consumerId > MAX_CON){
		printf("max 2000\n");
		exit(-1);
	}

	pthread_t threads[consumerId];
	int csock[consumerId];
    //connecting to socket and creating threads
	double sleep_time;
	for(int i = 0; i < consumerId; i++){
		sleep_time = poissonRandomInterarrivalDelay(rate);
		usleep( (int)(sleep_time * 1000000) );
		if ( ( csock[i] = connectsock( host, service, "tcp" )) == 0 ){
            fprintf( stderr, "Cannot connect to server.\n" );
            exit( -1 );
        }
		int status = pthread_create(&threads[i], NULL, consumerMe, &csock[i]);
        if(status != 0){
            printf("Cannot create thread %d\n",status);
            exit(-1);
        }
	}
	for(int i = 0; i < consumerId; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_exit(0);
}
