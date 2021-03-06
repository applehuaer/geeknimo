/*
 * =====================================================================================
 *
 *       Filename:  suspend_java.cpp
 *
 *    Description:  Suspend the java process and jar process.
 *
 *        Version:  1.0
 *        Created:  04/15/2013 10:52:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BackGarden_Straw.Neo (BackGarden_Straw), 20549304@163.com
 *   Organization:  BackGarden_Straw
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "suspend_java.h"

#define MAX_LENGTH          256
#define SERVER_IP           "127.0.0.1"
#define SERVER_PORT         5588
#define SHARED_MEMORY_SIZE  (4*4096) 

char * create_share_memory(int key, int size){
	HANDLE config_id;
	char *mem_addr;

	config_id = OS_shmget(key,size);
	if(config_id < 0)
	{
		OS_log(LVL_ERR,0,"OS_configConnect: OS_shmget error--shared memory not exit");
		return NULL;
	}
	
	mem_addr = (char *)OS_shmat(config_id);
	if(mem_addr < 0)
	{
		OS_log(LVL_ERR,0,"OS_configConnect: bind the shared memory error");
		return NULL;
	}
    
    memset(mem_addr,0,size);
    return mem_addr;
}

int close_share_memory(char * share_memory){
	int ret;
	ret = OS_shmdt(share_memory);
	if(ret < 0)
	{
		OS_log(LVL_ERR, 0, "disconnect the shared memory failed");
		return -1;
	}
	return 0;
}


int main(int argc, const char *argv[]){

    // for share memory
	int key;
	int ret;
	char *shared_mem;
     pid_t pid = getpid();

    // for socket
    int         send_data_len;
    int         client_sockfd;
    struct      sockaddr_in server_addr;
    socklen_t   server_len;    

    // init the share memory and log
    OS_logInit(NULL,0,1);
    key = pid;
    shared_mem = create_share_memory(key, SHARED_MEMORY_SIZE);
    	if(shared_mem == NULL)
	{
		OS_log(LVL_ERR,0,"get shared memory failed");
		return -1;
	}

    // init the socket
    bzero(&server_addr,sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // build the socket and do job
    if( inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr) <= 0){
        perror("inet_pton error");
        exit(1);
    }else{
        client_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        server_len = sizeof(server_addr);
        if( connect(client_sockfd,(struct sockaddr *)&server_addr,server_len) == -1){
            perror("connect error");
            exit(1);
        }else{
            char message_send[MAX_LENGTH];

            sprintf(message_send,"%d",key);

            send_data_len = 0;
            while(1){
                send_data_len = send(client_sockfd,message_send,MAX_LENGTH,0);
                if(send_data_len < MAX_LENGTH){
                    printf("leave some data to send.");
                }else{
                    // check the status
                    sleep(2);
                }          
            }       
        }
    }


    ret = close_share_memory(shared_mem);
	if(ret < 0)
	{
		OS_log(LVL_ERR,0,"close the shared memory");
		return -1;
	}
   
    return 0;
}
