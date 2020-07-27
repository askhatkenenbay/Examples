#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

#define MAX_SIZE 10000
#define ALPHABET_START 97
#define ALPHABET_SIZE 26
#define MAX_PROD 2000
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

//producer's thread
void* produceMe(void* val){
	int csock = *((int *)val);
	int productSize = ( random() % MAX_SIZE ) + 1; //size of product
	char* product = malloc(productSize * sizeof(char)); //allocating memory for product
	for(int i = 0; i < productSize; i++){
        product[i] = (random() % ALPHABET_SIZE) + ALPHABET_START; //putting printable chars into product
    }
	printf("Product with size %d is send\n", productSize);
	int responce = write( csock, "PRODUCE\r\n", 9);// Producer client connects to server, sends, 
	if(checkResponce(responce,"Producer client cannot connect to server\n") == 0){
		free(product);
		close(csock);
		pthread_exit(0);
	}
	//Getting responce from the server, especially GO\r\n
	char responceBuffer[32];
	responce = read( csock, responceBuffer, 4);
	if(checkResponce(responce,"There is problem with server\n") == 0){
		responce =  -1;
	}
	responceBuffer[4] = '\0';
	if(strcmp(responceBuffer, "GO\r\n") != 0){
        fprintf(stderr, "not allowed from server:GO\n");
        responce =  -1;
    }else if(responce != -1){
		responce = 0;
	}
	//if there was problem with getting responce, stop
    if(responce == -1){
        free(product);
		close(csock);
		pthread_exit(0);
    }
	
    int conv = htonl(productSize);
	responce = write(csock, (char*) &conv, 4);
	if( checkResponce(responce,"There is problem with writing\n") == 0){
        free(product);
		close(csock);
		pthread_exit(0);
    }
	//sending product to server
	responce = write(csock, product, productSize);
    if(checkResponce(responce,"There is problem with writing product\n") == 0){
        free(product);
		close(csock);
		pthread_exit(0);
    }
	//Getting responce from the server, especially DONE\r\n
	char responceBufferDone[32];
	responce = read( csock, responceBufferDone, 6);
	if(checkResponce(responce,"There is problem with server\n") == 0){
		responce =  -1;
	}
	responceBuffer[6] = '\0';
	if(strcmp(responceBufferDone, "DONE\r\n") != 0){
        fprintf(stderr, "not allowed from server:DONE\n");
        responce =  -1;
    }else if(responce != -1){
		responce = 0;
	}
	//if there was problem with getting responce, stop
    if(responce == -1){
        free(product);
		close(csock);
		pthread_exit(0);
    }
	
    free(product);
    close(csock);
    pthread_exit(0);
	
}

int main( int argc, char *argv[] ){
	char		*service;		
	char		*host = "localhost";
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
		printf("rate <= 0");
		exit(-1);
	}else if(consumerId > MAX_PROD){
		printf(" more than 2000");
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
		int status = pthread_create(&threads[i], NULL, produceMe, &csock[i]);
        if(status != 0){
            printf("Cannot create thread %d",status);
            exit(-1);
        }
	}

	//wait before quiting
	for(int i = 0; i < consumerId; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_exit(0);
}
