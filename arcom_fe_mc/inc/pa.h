/*! \file       pa.h
    \ingroup    lo
    \brief      PA header file

    <b> File information: </b><br>
    Created: 2004/08/24 16:13:43 by avaccari

    This file contains all the information necessary to define the
    characteristics and operate the PA. */

/*! \defgroup   pa  Power Amplifier (PA)
    \ingroup    lo
    \brief      PA module

    This group includes all the different \ref pa submodules. For more
    information on the \ref pa module see \ref pa.h */

#ifndef _PA_H
    #define _PA_H

    /* Extra includes */
    /* GLOBAL DEFINITIONS Defines */
    #ifndef _GLOBALDEFINITIONS_H
        #include "../inc/globalDefinitions.h"
    #endif /* _GLOBALDEFINITIONS_H */

    /* Power Amplifier Channel */
    #ifndef _PACHANNEL_H
        #include "../inc/paChannel.h"
    #endif /* _PACHANNEL_H */

    /* Submodules definitions */
    #define PA_MODULES_NUMBER      4       // See list below
    #define PA_MODULES_RCA_MASK    0x0000C /* Mask to extract the submodule number:
                                              0-1 -> paChannelHandler
                                              2   -> supplyVoltage3VHandler
                                              3   -> supplyVoltage5VHandler */
    #define PA_MODULES_MASK_SHIFT  2       // Bits right shift for the submodules mask

    /* Typedefs */
    //! Current state of the PA
    /*! This structure represent the current state of the Power Amplifier.
        \ingroup    lo
        \param      pllChannel[Po]      This contains the information about the
                                        channels available for this power
                                        amplifier. There can be up to \ref
                                        PA_CHANNELS_NUMBER for each PA. Each
                                        channel is assigned to a certain
                                        polarization Po according to the
                                        following:
                                            - Po = 0 -> Polarization 0
                                            - Po = 1 -> Polarization 1
        \param      supplyVoltage3V     This contains the most recent read-back
                                        value for the 3V supply voltage.
        \param      supplyVoltage5V     This contains the most recent read-back
                                        value for the 5V supply voltage. */
     typedef struct {
        //! A Channel current state
        /*! There is one power amplifier channel per polarization. */
        PA_CHANNEL  paChannel[PA_CHANNELS_NUMBER];
        //! PA 3V supply voltage
        /*! This is the PA 3V supply voltage (in V). */
        float   supplyVoltage3V;
        //! PA 5V supply voltage
        /*! This is the PA 5V supply voltage (in V). */
        float   supplyVoltage5V;
    } PA;

    /* Globals */
    /* Externs */
    extern unsigned char currentPaModule; //!< Current addressed PA submodule

    /* Prototypes */
    /* Statics */
    static void supplyVoltage3VHandler(void);
    static void supplyVoltage5VHandler(void);
    /* Externs */
    extern void paHandler(void); //!< This function deals with the incoming can message

#endif /* _PA_H */

