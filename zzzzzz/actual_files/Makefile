# DPST1092 ... a general makefile for multiple exercises

ifneq (, $(shell which dcc))
CC  = gcc
else ifneq (, $(shell which clang) )
CC	= clang
else
CC	= dcc
endif

EXERCISES	?=
CLEAN_FILES	?=

.DEFAULT_GOAL	= all
.PHONY: all clean

-include *.mk

all:	${EXERCISES}

clean:
	-rm -f ${CLEAN_FILES}
