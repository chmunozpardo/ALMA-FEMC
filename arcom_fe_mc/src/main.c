/*! \file   main.c
    \brief  Main module functions
    \note   Just a testing version while developping the other modules!

    <b> File information: </b><br>
    Created: 2004/08/24 16:46:19 by avaccari

    This is \ref main.c */

/* Includes */
#include <stdio.h>      /* printf */

#include "debug.h"
#include "version.h"
#include "globalOperations.h"
#include "globalDefinitions.h"
#include "main.h"
#include "error.h"
#include "can.h"
#include "pegasus.h"
#include "console.h"
#include "async.h"
#include "timer.h"
#include "ppComm.h"

/* Globals */
/* Externs */
unsigned char stop = 0; /*!< This global can be set by any module and will gently
                             stop the program if necessary. */
unsigned char restart = 0; /*!< This global can be set by any module and will
                                cause the system to reboot after a stop is
                                received. */

int main(void){
    /* Print version information */
    displayVersion();

    /* Initialize the frontend */
    if(initialization()==ERROR){
        return ERROR;
    }

    /* Enable connection with AMBSI1 */
    if(PPStart()==ERROR){
        return ERROR;
    }

    /* Main loop */
    while(!stop){

        #ifdef DEBUG_MSG_LOOP
            printf("Waiting for messages...\n\n");
        #endif /* DEBUG_MSG_LOOP */

        /* Do whatever is that you do when you don't have anything to do */
        while(!newCANMsg&&!stop){
            /* Call the console handling. Make sure this doesn't affect
               performances. */
            if(consoleEnable){
                console();
            }

            /* Perform the required asynchronous operations */
            async();

            /* Query the RSS update timer. */
//            if(queryAsyncTimer(TIMER_RSS)){
//                #ifdef DEBUG
//                    printf("Updating RSS...");
//                #endif /* DEBUG */
                // UPDATE RSS
//                #ifdef DEBUG
//                    printf("...done!\n");
//                #endif /* DEBUG */
/*
                startAsyncTimer(TIMER_RSS,
                                TIMER_TO_RSS,
                                FALSE); // Restart the timer

            }
*/      }

        /* If the software was stopped via console, don't handle the message */

        if(stop==TRUE){
            break;
        }

        #ifdef DEBUG_MSG_LOOP
            printf("Message received!\n\n");
        #endif /* DEBUG_MSG_LOOP */
        CANMessageHandler();

    }

    /* Shut down the frontend */
    if(shutDown()==ERROR){
    }

    /* If it was a restart request: restart the software. */
    if(restart==TRUE){
        printf("Rebooting system!\n");
        reboot();
    }

    return NO_ERROR;
}


