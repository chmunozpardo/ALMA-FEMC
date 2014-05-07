/*! \file   cryostatTemp.c
    \brief  Cryostat temperature sensors functions

    <b> File informations: </b><br>
    Created: 2007/03/14 16:44:04 by avaccari

    <b> CVS informations: </b><br>
    \$Id: cryostatTemp.c,v 1.8 2008/02/07 16:21:24 avaccari Exp $

    This files contains all the functions necessary to handle cryostat
    temperature sensors events. */

/* Includes */
#include <stdio.h>      /* printf */

#include "debug.h"
#include "frontend.h"
#include "can.h"
#include "error.h"
#include "database.h"
#include "cryostatSerialInterface.h"
#include "globalDefinitions.h"

/* Globals */
/* Externs */
unsigned char   currentCryostatTempModule=0;
/* An extern to perform the mapping between the temperature sensor number and
   the bit address. This is not done with the usual define because of the non
   linearity of the mapping. */
unsigned int    currentCryostatTempSensorAdd[CRYOSTAT_TEMP_SENSORS_NUMBER]={0x0000, // Sensor 0 -> TVO Sensor 4K cryocooler
                                                                            0x0004, // Sensor 1 -> TVO Sensor 4K plate near link #1
                                                                            0x0005, // Sensor 2 -> TVO Sensor 4K plate near link #2
                                                                            0x0008, // Sensor 3 -> TVO Sensor 4K plate far side #1
                                                                            0x000A, // Sensor 4 -> TVO Sensor 4K plate far side #2
                                                                            0x000C, // Sensor 5 -> TVO Sensor 12K cryocooler
                                                                            0x0010, // Sensor 6 -> TVO Sensor 12K plate near link
                                                                            0x0014, // Sensor 7 -> TVO Sensor 12K plate far side
                                                                            0x0018, // Sensor 8 -> TVO Sensor 12K shield top
                                                                            0x0100, // Sensor 9 -> PRT Sensor 90K cryocooler
                                                                            0x0120, // Sensor 10 -> PRT Sensor 90K plate near link
                                                                            0x0140, // Sensor 11 -> PRT Sensor 90K plate far side
                                                                            0x0160};// Sensor 12 -> PRT Sensor 90K shield top
/* Statics */
static HANDLER cryostatTempModulesHandler[CRYOSTAT_TEMP_MODULES_NUMBER]={tempHandler};

/* Cryostat temperatures sensors handler */
/*! This function will be called by the CAN message handling subrutine when the
    received message is pertinent to the cryostat temperature sensors. */
void cryostatTempHandler(void){

    #ifdef DEBUG_CRYOSTAT
    printf("  Cryostat Temperature Sensor: %d\n",
           currentCryostatModule);
    #endif /* DEBUG_CRYOSTAT */

    /* Since the cryostat is always outfitted with all the temperature sensors,
       no hardware check is performed. */

    /* Since there is only one submodule in the cryostat temperature sensor, the
       check to see if the desired submodule is in range is not needed and we
       can directly call the correct handler. */

    /* Call the correct handler */
    (cryostatTempModulesHandler[currentCryostatTempModule])();
}

/* Temperature Value Handler */
/* This function deals with the messages directed to the cryostat temperature
   sensors. */
static void tempHandler(void){

    #ifdef DEBUG_CRYOSTAT
        printf("   Temperature Value\n");
    #endif /* DEBUG_CRYOSTAT */

    /* If control (size !=0) store error and return. No control messages are
       allowed on this RCA. */
    if(CAN_SIZE){
        storeError(ERR_CRYOSTAT_TEMP,
                   0x01); // Error 0x01 -> Control message out of range
        return;
    }

    /* If monitor on control RCA return error snce there are no control messages
       allowed on the RCA. */
    if(currentClass==CONTROL_CLASS){ // If monitor on a control RCA
        storeError(ERR_CRYOSTAT_TEMP,
                   0x02); // Error 0x02 -> Monitor message out of range
        /* Store the sate in the outgoing CAN message */
        CAN_STATUS = MON_CAN_RNG;

        return;
    }

    /* Monitor cryostat temperature */
    if(getCryostatTemp()==ERROR){
        /* If error during monitoring, the error state was stored in the
           outgoing CAN message state during the previous statement. This
           different format is used because getCryostatTemp might return
           two different error state depending on error conditions. */
        /* Store the last known value in the outgoing message */
        CAN_FLOAT=frontend.
                   cryostat.
                    cryostatTemp[currentCryostatModule].
                     temp[CURRENT_VALUE];
    } else {
        /* If no error during monitor process, gather the stored data */
        CAN_FLOAT=frontend.
                   cryostat.
                    cryostatTemp[currentCryostatModule].
                     temp[CURRENT_VALUE];

        /* Check the result agains the warning and error range. Right now this
           function is only printing out a warning/error message depending on
           the result but no actions are taken. */
        #ifdef DATABASE_RANGE
            if(checkRange(frontend.
                           cryostat.
                            cryostatTemp[currentCryostatModule].
                             temp[LOW_WARNING_RANGE],
                          CAN_FLOAT,
                          frontend.
                           cryostat.
                            cryostatTemp[currentCryostatModule].
                             temp[HI_WARNING_RANGE])){
                if(checkRange(frontend.
                               cryostat.
                                cryostatTemp[currentCryostatModule].
                                 temp[LOW_ERROR_RANGE],
                              CAN_FLOAT,
                              frontend.
                               cryostat.
                                cryostatTemp[currentCryostatModule].
                                 temp[HI_ERROR_RANGE])){
                    storeError(ERR_CRYOSTAT_TEMP,
                               0x03); // Error 0x03 -> Error: cryostat temperature in error range
                    CAN_STATUS  = MON_ERROR_RNG;
                } else {
                    storeError(ERR_CRYOSTAT_TEMP,
                               0x04); // Error 0x04 -> Warning: cryostat temperature in warning range
                    CAN_STATUS = MON_WARN_RNG;
                }
            }
        #endif /* DATABASE_RANGE */
    }

    /* Load the CAN message payload with the returned value and set the size.
       The value has to be converted from little endian (Intel) to big endian
       (CAN). */
    changeEndian(CAN_DATA_ADD,
                 convert.
                  chr);
    CAN_SIZE=CAN_FLOAT_SIZE;
}
