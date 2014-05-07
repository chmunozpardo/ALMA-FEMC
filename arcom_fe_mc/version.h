/*! \file   version.h
    \brief  Version information file

    <b> File informations: </b><br>
    Created: 2004/10/06 16:47:08 by avaccari

    <b> CVS informations: </b><br>

    \$Id: version.h,v 1.55 2012/04/13 15:36:39 avaccari Exp $

    This files contains all the informations about the current version of the
    software and its revision history.

    The revision numbering system is according to the following rules:
        - The <em>Patch level</em> is changed when bugs are fixed
        - The <em>Minor version</em> is changed when features are added
        - The <em>Major version</em> is changed when major changes are made to
          the software:
            - Affected backward compatibility
            - Changed functionality
            - Official global new releases
            - ...

    REVISION HISTORY

    2012-04-13  002.006.001     (fe_mc.exe or 02-06-01.exe or 20120413.exe)
        Official Release
        This version is tagged Ver_02_06_01(ALMA-40_00_00_00-75_35_25_00_C_ICD).
        - Allowed number to power up cartridges now depend on FE operation mode:
          troubleshooting: all, all the other modes: 3.
        - Cartrdige temperature sensors: added check to verify that the measured
          voltage is within the temperature calibration curve (for the lowest
          voltage -> highest temperature).
        - Assigned PA channel mapping for bands 5 and 10.

    2011-12-12  002.006.000     (fe_mc.exe or 02-06-00.exe or 20111212.exe)
        Official Release
        This version is tagged Ver_02_06_00(ALMA-40_00_00_00-75_35_25_00_C_ICD).
        - Fully implemented FE operation mode. When in MAINTENANCE_MODE only
          the special RCA will be available. (FE-6)
        - Added automatic monitor on control RCA when control issued using
          serial console.
        - Modified code to enable a cartridge asychronously. This modifies the
          5ms latency required by the cartridge hardware from blocking to non
          blocking (Jira ticket: FE-276).
        - Incresed size for TVO sensor name field from 7 to 31 characters.
        - Modified WCA photodetector code to return the absolute value of the
          bias current (Jira ticket: FE-273).
        - Modified behavior of initialization of parallel port communication. A
          timer was implemented while waiting for the AMBSI1 to become ready. If
          the AMBSI1 is not responsive during intialization, the timer will
          expire and the bootup continue and an error will be stored. The CAN
          communication will NOT be available but the console will still be
          responsive to allow debug.
        - Added control message and console option to read ESN available on OWB.
          This allows to search for available ESN whenever is desired without
          having to reboot the module (Jira ticket: FE-298).
        - Modified behavior of gate valve behavior due to the change in hardware
          of the gate valve driver. (Jira ticket: FE-232).
        - Added shutdown procedure to the LPR to maximize safety of personel
          (Jira ticket: FE-247).
        - Implemented software interlock to prevent usage of turbo pump outside
          allowed temperature range. (Jira ticket: FE-293).
        - Implemented software interlock to prevent starting of cooldown if
          dewar pressure > 5x10e-4. Within the async loop, this will be
          continuously tested and depending on the condition, the FE status bit
          for the FETIM will be set so SAFE or UNSAFE. (Jora ticket: FE-311).

    2010-11-04  002.005.000     (fe_mc.exe or 02-05-00.exe or 2101104.exe)
        Official Release
        This version is tagged Ver_02_05_00(ALMA-40_00_00_00-75_35_25_00_B_ICD).
        - The limits for the control message to modify the IF switch channels
          attenuation are now hardcoded and implemented. (Jira ticket: FE-270)
        - The limits for the control message to modify the YTO coarse tuning are
          now hardcoded and implemented. (Jira ticket: FE-269)
        - A direct communication test between the main board and the multiplexer
          board has been added during boot up time. This test will assure that
          the communication is established before allowing further execution of
          the code. (Jira ticket: FE-45)
        - The error counting and returning has been fixed. (Jira ticket: FE-151)
        - The limits for the control message to set the LPR optical channel are
          now hardcoded and implemented. (Jira ticket: FE-258)
        - The limits for the control message to set the IF switch cartrdige are
          now hardcoded and implemented. (Jira ticket: FE-238)
        - The monitoring of the gate valve has been modified to allow monitoring
          also when the backing pump is turned off. In this case the evaluation
          of the state is based only on 2 of the 4 sensors but an evaluation of
          the current state is still possible. (Jira ticket: FE-232)
        - Modified scaling for LPR laser photodetector current and removed the
          hardware undefined error. This point will return meaningful data only
          for LPR SN.226 and above. It is not implemented in previous serial
          number. (Jira ticket: FE-233)

    2010-08-11  002.004.000     (fe_mc.exe or 02-04-00.exe or 2100811.exe)
        Official Release
        This version is tagged Ver_02_04_00(ALMA-40_00_00_00-75_35_25_00_B_ICD).
        - Modified interface to cryostat to support both hardware revisions of
          the crysotat M&C board. The two hardware revisions require different
          scaling to be applied to the readback voltage before a conversion to
          the actual temperature can be performed. (Jira ticket: FE-220)
        - Adjusted the scaling for the PRT sensor for higher accuracy.
        - Increase to 100ms the time between the temperature channel switching
          and an the initiation of the ADC conversion in the cryostat. This
          should allow for more stable readings. This timeout doesn't affect any
          CAN interface timing since it's running in an async process.

    2010-04-28  002.003.000     (fe_mc.exe or 02-03-00.exe or 2100428.exe)
        Official Release
        This version is tagged Ver_02_03_00(ALMA-40_00_00_00-75_35_25_00_B_ICD).
        - During initialization of the OWB, the detected ESNs will be reported
          both with the family code first and with the family code last.
          (Jira ticket: HANDOVER-879)
        - Modified interface to IF switch to support both hardware revisions of
          the IF switch M&C board. (Jira ticket: FE-158)
        - Resolved issue with IF switch temperatures monitoring returning
          errors. (Jira tickets: FE-154, AIV-1675)
        - Fixed issue that will leave timer running if error during wait for
          ADC to get ready in several subsystems.
        - Changes B9 SIS heater timeout to 10s. Also created independent
          timeouts one for each polarization.
        - Added the support for different multiplier scales via the WCA
          configuration files. (Jira ticket: FE-153)

    2009-10-13  002.002.000     (fe_mc.exe or 02-02-00.exe or 2k91013.exe)
        Official Release
        This version is tagged Ver_02_02_00(ALMA-40_00_00_00-75_35_25_00_B_ICD).
        - Modified scaling factor for LPR temperature sensors
        - Added timer to prevent band 9 heater from being turned on more than
          once every 10 second.
        - Added console switch to turn on and off async processes to allow
          easier console debugging.
        - Added 'EDFA driver status' monitor point. This will return a can
          status of -15 until the hardware is implemented
        - Changed scaling factor for the SIS heater current monitor to adapt to
          new BIAS module hardware.
        - Removed the SIS Heater Enable monitor point. This because the change
          in the BIAS module that introduced the auto shutoff causes the
          software to loose synchronization with the hardware state.
        - Reading WCA photmixer current twice (~100us) to get stable reading
        - Lowered to 5ms the timeout from power on to initialization of the CC
          and WCA
        - Implemented the error CAN interface.
        - The GET_ESN_FOUND monitor point will now reset the device index to the
          first device found.
        - The analog monitor for the BIAS and WCA now have a 40us delay between
          the selection of the channel and the beginning of the conversion. This
          was needed to fix an issue with speed of the analog circuits.
        - An asynchronous framework is in place to allow asyncronous operations
          to be performed in the background.
        - The cryostat analog monitoring is now attached to the asynchronous
          frame.
          Monitored data is stored in memory where it can be gathered with the
          standard CAN access.

    2009-05-13  002.001.003     (02-01-03.exe)
        Debug Release.
        This release is equivalent to 002.001.001. The only difference is that
        it uses the cryostat interface from revision 001.000.000.
        Tis version is tagged Ver_02_01_03

    2009-05-13  002.001.002     (02-01-02.exe)
        Debug Release.
        This release is equivalent to 002.001.000. The only difference is that
        it uses the cryostat interface from revision 001.000.000.
        This version is tagged Ver_02_01_02

    2009-04-24  002.001.001     (02-01-00.exe)
        Debug Release.
        This release contains a fix to prevent the CIPT from operating the mixer
        heaters incorrectly during the control software testing.
        This version is tagged Ver_02_00_01.

    2009-04-24  002.001.000     (fe_mc.exe or 02-01-00.exe or 2k90424.exe)
        Official Release.
        This version is tagged Ver_02_01_00(ALMA-40_00_00_00-75_35_25_00_B_ICD).
        - Added simulator for ESNs number. The option can be controlled with
          the ESNS.INI configuration file.
        - Now when the software is terminated, all the cartridges will be turned
          off.
        - The storing of the PA channels information now follows the cartridge
          dependent mapping rather than just the CAN message.
        - The drain and gate voltages of the PAs are set to 0.0V every time a
          cartridge is initialized.
        - The current operation mode of the front end can be monitored. The setting
          is not implemented yet and it will not untill the safety checks are in
          place.

    2009-02-25  002.000.000     (fe_mc.exe or 02-00-00.exe or 2k90225.exe)
        Official Release.
        This version is tagged Ver_02_00_00(ALMA-40_00_00_00-75_35_25_00_B_ICD).

    2008-10-08  002.000.000b1    (2-0-00b1.exe)
        The two previous beta revisions are rolled into the new revision
        including all the previous changes. Since this new revision is not
        backwards compatible with the previous versions it will be released as
        rev 2.
        This version is tagged Ver_02_00_00b1.

    2008-10-07  001.000.002b     (1-0-02b2.exe)
        - Modified LO to provide only 1 extra clock cycle for the YTO strobe (JIRA
          FE-13)
        This version is tagged Ver_01_00_02b2.

    2008-09-26  001.000.002b     (1-0-02b1.exe)
        *** Added functionality ***
        --- Console ---
        - If the console is activated, then pressing the ' key will retype the
          last submitted console command.
        - If the console is activated, then pressing the " key will resubmit the
          last submitted console command.
        *** Patches ***
        --- Cryostat ---
        - The TVO sensor number is now a string instead of an integer.
        - Modified return error values for the 230V supply current monitoring to
          take in account of the hardware retry issue (unstable monitor points)
        --- Console ---
        - Added #define to enable/disable console debugging
        --- Error ---
        - Corrected output number of cartridge to match the band number
        --- LO ---
        - Modified size of AREG to match a fix to an hardware problem that required
          a change in the CPLD code inside the LO monitor and control.
          (JIRA issue FEIC-73)
        This version is tagged Ver_01_00_02b1.

    2008-05-15  001.000.001     (01-00-01.exe)
        Debug Release.
        This release contains a fix to prevent the CIPT from operating the mixer
        heaters incorrectly during the control software testing.
        This version is tagged Ver_01_00_01.

    2008-04-09  001.000.000
        First Official Release.
        This is the first stable working release.
        This version is tagged Ver_01_00_00(ALMA-40_00_00_00-75_35_25_00_B_ICD).

    2007-08-09  000.007.000
        Development Release.
        This release fixed bugs in the previous release and added monitor and
        control support for the LPR module.
        There is also partial support for configuration through INI files.

    2007-05-29  000.006.000
        Deveolpment Release.
        This release fixed bugs in the previous release and added monitor and
        control support for the Cryogenics. The temperature section of the cryo
        M&C still have to be debugged with hardware.

    2007-01-16  000.005.000
        Development Release.
        This release fixed bugs in the previous release and added monitor and
        control support for the IF switch module.

    2006-11-22  000.004.000
        Development Release.
        This release fixed bugs in the previous release and added monitor and
        control support for the cartridge temperature sensors.

    2006-11-14  000.003.000
        Development Release.
        This release fixed bugs in the previous release and added monitor and
        control support for the cartridge power distribution system.

    2006-10-10  000.002.001
        Development Release.
        This release fixed bugs in the previous release.

    2006-10-05  000.002.000
        Development Release.
        This release fixed bugs in the previus release and added monitor and
        control for the LO.

    2006-08-21  000.001.000
        Development Release.
        This release implement a working cartridge bias module. */

/*! \mainpage
    \section    sectionVersion  Version
    Documentation relative to Version: 002.006.001 */

#ifndef _VERSION_H
    #define _VERSION_H

    /* Defines */
    #define VERSION_MAJOR   002  //!< Major version
    #define VERSION_MINOR   006  //!< Minor version
    #define VERSION_PATCH   001  //!< Patch level

    #define VERSION_DATE    "2012-04-13" //!< Version Date
    #define VERSION_NOTES   "" //!<Version Notes
    #define PRODUCT_TREE    "FEND-40.04.03.03-011-A-FRM" //! Product Tree number
    #define AUTHOR          "Andrea Vaccari - NRAO (avaccari@nrao.edu)"
    #define BUGZILLA        "jira.alma.cl"

    /* Prototypes */
    /* Statics */
    /* Externs */
    extern void displayVersion(void); //!< This function displays the version information


#endif /* _VERSION_H */
