CC=*wcc
INCLUDES="C:/WATCOM/h"
FLAGS=-w4 -zq -od -d1 -5 -bt=dos -ml
TARGET=releases/fe_mc.exe

BUILDDIR = build


TEMPS = $(PREF)amc.c $(PREF)async.c $(PREF)backingPump.c $(PREF)biasSerialInterface.c $(PREF)can.c $(PREF)cartridge.c $(PREF)cartridgeTemp.c $(PREF)compressor.c $(PREF)console.c $(PREF)cryostat.c $(PREF)cryostatSerialInterface.c $(PREF)cryostatTemp.c $(PREF)dewar.c $(PREF)edfa.c $(PREF)error.c $(PREF)fetim.c $(PREF)fetimExtTemp.c $(PREF)fetimSerialInterface.c $(PREF)frontend.c $(PREF)gateValve.c $(PREF)globalDefinitions.c $(PREF)globalOperations.c $(PREF)he2Press.c $(PREF)ifChannel.c $(PREF)ifSerialInterface.c $(PREF)ifSwitch.c $(PREF)ifTempServo.c $(PREF)iniWrapper.c $(PREF)interlock.c $(PREF)interlockFlow.c $(PREF)interlockFlowSens.c $(PREF)interlockGlitch.c $(PREF)interlockSensors.c $(PREF)interlockState.c $(PREF)interlockTemp.c $(PREF)interlockTempSens.c $(PREF)laser.c $(PREF)lna.c $(PREF)lnaLed.c $(PREF)lnaStage.c $(PREF)lo.c $(PREF)loSerialInterface.c $(PREF)lpr.c $(PREF)lprSerialInterface.c $(PREF)lprTemp.c $(PREF)main.c $(PREF)miDac.c $(PREF)miSpecialMsgs.c $(PREF)modulationInput.c $(PREF)opticalSwitch.c $(PREF)owb.c $(PREF)pa.c $(PREF)paChannel.c $(PREF)pdChannel.c $(PREF)pdModule.c $(PREF)pdSerialInterface.c $(PREF)pegasus.c $(PREF)photoDetector.c $(PREF)photomixer.c $(PREF)pll.c $(PREF)polarization.c $(PREF)polDac.c $(PREF)polSpecialMsgs.c $(PREF)powerDistribution.c $(PREF)ppComm.c $(PREF)serialInterface.c $(PREF)serialMux.c $(PREF)sideband.c $(PREF)sis.c $(PREF)sisHeater.c $(PREF)sisMagnet.c $(PREF)solenoidValve.c $(PREF)timer.c $(PREF)turboPump.c $(PREF)vacuumController.c $(PREF)vacuumSensor.c $(PREF)version.c $(PREF)yto.c

PREF =
SOURCES = $+ $(TEMPS) $-
PREF = build/
OBJ_TEMP = $+ $(TEMPS) $-
OBJECTS = $(OBJ_TEMP:.c=.obj) build/ini.obj
FIL_OBJ = $(OBJECTS: =,)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	*wlink name $@ d all sys dos libf sockets/lib/wcapil5.lib op maxe=25 op q op symf op el FIL $(FIL_OBJ)

.c.obj : .AUTODEPEND
	$(CC) $< $(FLAGS) -fo=$@

build/ini.obj: 3rdParty/ini.c .AUTODEPEND
	$(CC) $< $(FLAGS) -fo=$@