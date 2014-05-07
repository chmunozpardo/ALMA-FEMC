/*! \file   vacuumSensor.c
    \brief  Cryostat vacuum sensors functions

    <b> File informations: </b><br>
    Created: 2007/04/06 14:41:08 by avaccari

    <b> CVS informations: </b><br>
    \$Id: vacuumSensor.c,v 1.6 2008/02/28 22:15:05 avaccari Exp $

    This files contains all the functions necessary to handle cryostat
    vacuum sensors events. */

/* Includes */
#include <stdio.h>      /* printf */

#include "debug.h"
#include "frontend.h"
#include "globalDefinitions.h"
#include "error.h"
#include "database.h"
#include "cryostatSerialInterface.h"

/* Globals */
/* Externs */
unsigned char   currentVacuumSensorModule=0;
/* Statics */
static HANDLER vacuumSensorModulesHandler[VACUUM_SENSOR_MODULES_NUMBER]={pressureHandler};

/* Cryostat vacuum sensors handler */
/*! This function will be called by the CAN message handling subrutine when the
    receivd message is pertinent to the cryostat vacuum sensors. */
void vacuumSensorHandler(void){

    #ifdef DEBUG_CRYOSTAT
    printf("   Vacuum Sensor: %d\n",
           currentVacuumControllerModule);
    #endif /* DEBUG_CRYOSTAT */

    /* Since the cryostat is always outfitted with all the vacuum sensors, no
       hardware check is performed. */

    /* Since there is only one submodulein the cryostat temperature sensor, the
       check to see if the desired submodule is in range is not needed and we
       can directly call the correct handler. */
    /* Call the correct handler */
    (vacuumSensorModulesHandler[currentVacuumSensorModule])();
}

/* Pressure Handler */
static void pressureHandler(void){

    #ifdef DEBUG_CRYOSTAT
        printf("    Pressure Value\n");
    #endif /* DEBUG_CRYOSTAT */

    /* If control (size !=0) store error and return. No control messages are
       allowed on this RCA. */
    if(CAN_SIZE){
        storeError(ERR_VACUUM_SENSOR,
                   0x01); // Error 0x01 -> Control message out of range
        return;
    }

    /* If monitor on control RCA return error since there are no control
       messages allowed on the RCA. */
    if(currentClass==CONTROL_CLASS){ // If monitor on a control RCA
        storeError(ERR_VACUUM_SENSOR,
                   0x02); // Error 0x02 -> Monitor message out of range
        /* Store the state in the outgoing CAN message */
        CAN_STATUS = MON_CAN_RNG;

        return;
    }

    /* Monitor the vacum sensor pressure */
    if(getVacuumSensor()==ERROR){
        /* If error during monitoring, the error state was stored in the
           outgoing CAN message state during the previous statement. This
           different format is used because getVacuumSensor might return
           two different error state depending on error conditions. */
        /* Store the last known value in the outgoing message */
        CAN_FLOAT=frontend.
                   cryostat.
                    vacuumController.
                     vacuumSensor[currentVacuumControllerModule].
                      pressure[CURRENT_VALUE];
    } else {
        /* if no error during monitor process, gather the stored data */
        CAN_FLOAT=frontend.
                   cryostat.
                    vacuumController.
                     vacuumSensor[currentVacuumControllerModule].
                      pressure[CURRENT_VALUE];

        /* Check the result against the warning and error range. Right now this
           function is only printing out a warining/error message depending on
           the result but no actions are taken. */
        #ifdef DATABASE_RANGE
            if(checkRange(frontend.
                           cryostat.
                            vacuumController.
                             vacuumSensor[currentVacuumControllerModule].
                              pressure[LOW_WARNING_RANGE],
                          CAN_FLOAT,
                          frontend.
                           cryostat.
                            vacuumController.
                             vacuumSensor[currentVacuumControllerModule].
                              pressure[HI_WARNING_RANGE])){
                if(checkRange(frontend.
                               cryostat.
                                vacuumController.
                                 vacuumSensor[currentVacuumControllerModule].
                                  pressure[LOW_ERROR_RANGE],
                              CAN_FLOAT,
                              frontend.
                               cryostat.
                                vacuumController.
                                 vacuumSensor[currentVacuumControllerModule].
                                  pressure[HI_ERROR_RANGE])){
                    storeError(ERR_VACUUM_SENSOR,
                               0x03); // Error 0x03 -> Error: vacuum sensor pressure in error range
                    CAN_STATUS = MON_ERROR_RNG;
                } else {
                    storeError(ERR_VACUUM_SENSOR,
                               0x04); // Error 0x04 -> Warning: vacuum sensor pressure in warning range
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
