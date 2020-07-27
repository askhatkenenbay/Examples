#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/select.h>
#include <prodcon.h>

//curr number
int ITEM_SIZE = 0;
int num_prod = 0;
int num_con = 0;
//mutexs
pthread_mutex_t mutex_temp;
pthread_mutex_t mutex_prod;
pthread_mutex_t mutex_con;
//semaphores
sem_t sem_emp;
sem_t sem_full;

int passivesock( char *service, char *protocol, int qlen, int *port );
//item produced


ITEM **buffer_item;
int buffer_size;
//write-read-...-read-write
void* producer_helper(void* val){
        printf("prod thread start\n");
        int *pointer_to_ssock = (int *)val;
        int ssock = *pointer_to_ssock;
        
        //send command GO to producer, if cannot quit
        if(write(ssock, "GO\r\n", 4) < 0){
                close(ssock);
                pthread_exit(0);
                exit(-1);
        }
        //create space for new item
        ITEM* item = (ITEM* )malloc(sizeof(ITEM));
        //get size of item and allocate enough space for it
        //if cannot quit
        int item_size_received;
        if(read(ssock, (char *) &item_size_received, 4) <=0 ){
                free(item);
                close(ssock);
                pthread_exit(0);
                exit(-1);
        }
        int item_size = ntohl(item_size_received);
        (*item).size = item_size;
        (*item).letters = (char* ) calloc(item_size, sizeof(char));
        //now read letters from producer
        int read_byte_num = 0;
        int cc = 0;
        while(read_byte_num < item_size && (cc = read(ssock, (*item).letters + read_byte_num, BUFSIZE)) > 0){
                read_byte_num += cc;
        }
        //wait untill there is free space
        sem_wait(&sem_emp);
        //insert new item to buffer in server
        pthread_mutex_lock(&mutex_temp);
        buffer_item[buffer_size] = item;
        buffer_size++;
        printf("curr count: %d\n", buffer_size);
        fflush(stdout);
        pthread_mutex_unlock(&mutex_temp);
        //increase sem_full since new item was added
        sem_post(&sem_full);
        //send final command to producer
        write(ssock, "DONE\r\n", 6);
        printf("Producer produced item:: %d\n",item_size);
        num_prod--;
        fflush(stdout);
        close(ssock);
        pthread_exit(0);
}
//two writes
void* consumer_helper(void* val){
        int *pointer_to_ssock = (int *)val;
        int ssock = *pointer_to_ssock;
        //wait untill there is something to consumer
        sem_wait(&sem_full);
        //mutex_temp locked to change buffer, remove item from it
        pthread_mutex_lock(&mutex_temp);
        ITEM* item = buffer_item[buffer_size - 1];
        buffer_size --;
        printf("curr count: %d\n", buffer_size);
        pthread_mutex_unlock(&mutex_temp);
        //update sem_emp since now there is +1 free space
        sem_post(&sem_emp);
        //now send size of item to consumer
        int conv = htonl( (*item).size );
        write(ssock, (char*) &conv, 4);
        //here send letters of item to consumer
        write(ssock, (*item).letters, (*item).size );
        printf("Consumer consumed item: %d\n", (*item).size);
        fflush(stdout);
        //free
        free( (*item).letters );
        free(item);
        close(ssock);
        num_con--;
        pthread_exit(0);
}

int main( int argc, char *argv[] ){
        //init of variables
        int msock;
        int ssock;
        int port = 0;
        char *service;
        struct sockaddr_in fsin;
        socklen_t alen;
        buffer_size = 0;
        pthread_mutex_init( &mutex_temp, NULL );
        pthread_mutex_init( &mutex_prod, NULL);
        pthread_mutex_init( &mutex_con, NULL);
        switch (argc) 
	{
		case	2:
			// No args? let the OS choose a port and tell the user
			port = 1;
			ITEM_SIZE = atoi(argv[1]);
                        break;
		case	3:
			// User provides a port? then use it
			service = argv[1];
                        ITEM_SIZE = atoi(argv[2]);
			break;
		default:
			fprintf( stderr, "wrong number of arguments\n" );
			exit(-1);
	}
        sem_init( &sem_full, 0, 0 );
	sem_init( &sem_emp, 0, ITEM_SIZE);
        buffer_item = (ITEM**) malloc(ITEM_SIZE * sizeof(ITEM*));
        msock = passivesock( service, "tcp", QLEN, &port );
	if (port){
		printf( "port used: %d\n", port );
                fflush(stdout);	
	}
        //init staff for multiplexing
        int fd;
        int cc;
        fd_set	rfds;
	fd_set	afds;
        int     nfds;
        nfds = msock+1;
        FD_ZERO(&afds);
        FD_SET( msock, &afds );
        // -------------
        // fd_set fds, readfds;
        // FD_ZERO (&fds);
        // FD_SET (msock, &fds);
        while(1){//infinite lloop
                // readfds = fds;
                memcpy((char *)&rfds, (char *)&afds, sizeof(rfds));
                // monitor readfds for readiness for reading
                // if (select (MAX_CLIENTS + 1, &readfds, NULL, NULL, NULL) == -1){
                //         error ("error with select");
                // }
                if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
				(struct timeval *)0) < 0)
		{
			fprintf( stderr, "server select: %s\n", strerror(errno) );
			exit(-1);
		}
                // Some sockets are ready. Examine readfds
                if (FD_ISSET( msock, &rfds)) 
		{
			int	ssock;
			// we can call accept with no fear of blocking
			alen = sizeof(fsin);
			ssock = accept( msock, (struct sockaddr *)&fsin, &alen );
                        
			if (ssock < 0)
			{
				fprintf( stderr, "accept: %s\n", strerror(errno) );
				exit(-1);
			}

			// If a new client arrives, we must add it to our afds set
			FD_SET( ssock, &afds );

			// and increase the maximum, if necessary
			if ( ssock+1 > nfds )
				nfds = ssock+1;
		}

                // Now check all the regular sockets
		for ( fd = 0; fd < nfds; fd++ )
		{
			// check every socket to see if it's in the ready set
			// But don't recheck the main socket
			if (fd != msock && FD_ISSET(fd, &rfds))
			{
				// you can read without blocking because data is there
				// the OS has confirmed this
                                char buffer[BUFSIZE];
				if ( (cc = read( fd, buffer, BUFSIZE )) <= 0 )
				{
					printf( "The client has gone.\n" );
                                        fflush(stdout);
					(void) close(fd);
					// If the client has closed the connection, we need to
					// stop monitoring the socket (remove from afds)
					FD_CLR( fd, &afds );
					// lower the max socket number if needed
					if ( nfds == fd+1 )
						nfds--;

				}
				else
				{
					pthread_mutex_lock(&mutex_prod);
                                        pthread_mutex_lock(&mutex_con);
                                        if(num_prod + num_con <= MAX_CLIENTS){
                                                pthread_mutex_unlock(&mutex_prod);
                                                pthread_mutex_unlock(&mutex_con);
                                                buffer[cc] = '\0';
                                                //differ is it consumer or producer
                                                //change number of curr consumers/producers
                                                //send to their functions
                                                if(strcmp(buffer, "CONSUME\r\n") == 0){
                                                        printf( "new CONSUMER\n" );
                                                        fflush(stdout);
                                                        //locked to get consistent number of number of curr consumers and
                                                        //change it
                                                        pthread_mutex_lock(&mutex_con);
                                                        if(num_con < MAX_CON){
                                                                num_con++;
                                                                pthread_mutex_unlock(&mutex_con);
                                                                pthread_t thread;
                                                                int* con_ssock = (int*) malloc(sizeof(int));
                                                                *con_ssock = fd;
                                                                int status = pthread_create(&thread, NULL, consumer_helper, (void *)con_ssock);
                                                                if(status != 0){
                                                                        printf("Fatal error, cannot create thread");
                                                                        fflush(stdout);
                                                                        free(buffer_item);
                                                                        free(con_ssock);
                                                                        exit(-1);
                                                                }
                                                                // consumer_helper(ssock);
                                                                pthread_mutex_lock(&mutex_con);
                                                                
                                                        }
                                                        pthread_mutex_unlock(&mutex_con);
                                                }else if(strcmp(buffer, "PRODUCE\r\n") == 0){
                                                        //locked to get consistent number of number of curr producers and
                                                        //change it
                                                        printf( "new Producer\n" );
                                                        fflush(stdout);
                                                        pthread_mutex_lock(&mutex_prod);
                                                        if(num_prod < MAX_PROD){
                                                                num_prod++;
                                                                pthread_mutex_unlock(&mutex_prod);
                                                                pthread_t thread;
                                                                int* my_ssock = (int*) malloc(sizeof(int));
                                                                *my_ssock = fd;
                                                                int status = pthread_create(&thread, NULL, producer_helper, (void *)my_ssock);
                                                                if(status != 0){
                                                                        printf("Fatal error, cannot create thread");
                                                                        fflush(stdout);
                                                                        free(buffer_item);
                                                                        free(my_ssock);
                                                                        exit(-1);
                                                                }
                                                                // producer_helper(ssock);
                                                                pthread_mutex_lock(&mutex_prod);
                                                                
                                                        }
                                                        pthread_mutex_unlock(&mutex_prod);
                                                }
                                                FD_CLR( fd, &afds );
                                                // lower the max socket number if needed
                                                if ( nfds == fd+1 )
                                                        nfds--;
                                        }else{
                                                FD_CLR( fd, &afds );
                                                // lower the max socket number if needed
                                                if ( nfds == fd+1 )
                                                        nfds--;
                                                pthread_mutex_unlock(&mutex_prod);
                                                pthread_mutex_unlock(&mutex_con); 
                                                close(fd);  
                                        }
				}
			}

		}
        }
        free(buffer_item);
        pthread_exit(0);
}
