#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Lista.o \
	${OBJECTDIR}/SqlParserTraductor.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/socketServer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread `pkg-config --libs pthread-stubs` -lsqlparser `pkg-config --libs json` `pkg-config --libs jsoncpp`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/server1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Lista.o: Lista.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags pthread-stubs` `pkg-config --cflags json` `pkg-config --cflags jsoncpp`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Lista.o Lista.cpp

${OBJECTDIR}/SqlParserTraductor.o: SqlParserTraductor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags pthread-stubs` `pkg-config --cflags json` `pkg-config --cflags jsoncpp`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SqlParserTraductor.o SqlParserTraductor.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags pthread-stubs` `pkg-config --cflags json` `pkg-config --cflags jsoncpp`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/socketServer.o: socketServer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `pkg-config --cflags pthread-stubs` `pkg-config --cflags json` `pkg-config --cflags jsoncpp`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/socketServer.o socketServer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
