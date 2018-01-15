
# Application name
TARGET=multifruiti2

# Where to find user C code
USR_PATH=.

# -----------
# user C code
# -----------
USR_CFILES=\
	glue.c \
	line_ctrl.c \
	obst_ctrl.c \

# generic makefile ...
include $(MDL2LUS2OSEK)/generic.mak


# -----------
# mdl -> lustre -> c rules
# -----------

# c code is obtained by compiling Lustre code ...
# (note the "-ctx-static": it influences the way GLUE must be written)
# controller.c: controller.lus
# 	lus2c controller.lus controller -ctx-static

# # Lustre code is obtained from mdl
# controller.lus: ExRobotAndEnvironmentControllerContPI.mdl
# 	mdl2lus ExRobotAndEnvironmentControllerContPI.mdl -system controller

# clear: clean
# 	rm -f controller.xml controller.c controller.h controller.lus controller.ec controller.mws

# run:
# 	t2n -put controller.rxe

## A partir DC (commics) commence le Makefile multitâche ##

line_ctrl.c: line_ctrl.lus ExRobotAndEnvironmentControllerContPI.mdl
	lus2c line_ctrl.lus line_ctrl -ctx-static -o line_ctrl.c

obst_ctrl.c: obst_ctrl.lus ExRobotAndEnvironmentControllerContPI.mdl
	lus2c obst_ctrl.lus obst_ctrl -ctx-static -o obst_ctrl.c

# Lustre code is obtained from mdl
line_ctrl.lus: ExRobotAndEnvironmentControllerContPI.mdl
	mdl2lus ExRobotAndEnvironmentControllerContPI.mdl -system line_ctrl

obst_ctrl.lus: ExRobotAndEnvironmentControllerContPI.mdl
	mdl2lus ExRobotAndEnvironmentControllerContPI.mdl -system obst_ctrl

clear: clean
	rm -f *.lus *.ec *.mws

flash:
	t2n -put $(TARGET).rxe

.PHONY:	flash clean
