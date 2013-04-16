
#ifndef _ACM_CODE_H_
#define _ACM_CODE_H_
    
    #include "header.h"

    //OS_LIB Header Files
    #include <os_sem.h>
    #include <os_cli.h>
    #include <os_log.h>
    #include <os_msgq.h>
    #include <os_mutex.h>
    #include <os_thread.h>
    #include <os_global.h>
    
    //mobilephone include 
    #include <sys/select.h>

    /*
    #include <queue.h>
    #include <os_cli.h>
    #include <os_log.h>
    #include <os_sem.h>
    #include <os_shm.h>
    #include <os_msgq.h>
    #include <os_rbuf.h>
    #include <os_mutex.h>
    #include <os_utils.h>
    #include <os_vmsgq.h>
    #include <os_global.h>
    #include <os_thread.h>
    */

    
    /******************/
    //Struct Define   
    typedef struct
    {

    }GLOBAL_VAR;

    /******************/
    //Function Prototype
    #ifdef __cplusplus
        extern "C" 
        {
    #endif

    GLOBAL_VAR * initialization();

    void * pthread_func(void *p_arg);
    
    void deinitialization(GLOBAL_VAR * pVar);

    #ifdef __cplusplus
        }
    #endif

#endif // _ACM_CODE_H_