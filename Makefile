
# Application name
TARGET=controller

# Where to find user C code
USR_PATH=.

# -----------
# user C code
# -----------
USR_CFILES=\
	controller.c \
	glue.c \

# generic makefile ...
include $(MDL2LUS2OSEK)/generic.mak


# -----------
# mdl -> lustre -> c rules
# -----------

# c code is obtained by compiling Lustre code ...
# (note the "-ctx-static": it influences the way GLUE must be written)
controller.c: controller.lus
	lus2c controller.lus controller -ctx-static

# Lustre code is obtained from mdl
controller.lus: ExRobotAndEnvironmentControllerContPI.mdl
	mdl2lus ExRobotAndEnvironmentControllerContPI.mdl -system controller

clear: clean
	rm -f controller.xml controller.c controller.h controller.lus controller.ec controller.mws

flash:
	t2n -put controller.rxe
