# makefile for miscellaneous items in directory .
#
# Changelog:
#
# 10-24-2018
#
# added targets for pattern, bsp, daqh, fct, cir, dummy, clean
# removed cir target; interest rate stuff moved to ./rate_models
#

# c and python flags
CC = gcc
CFLAGS = -Wall -g
PYC = python
PYFLAGS = 

# target dependencies
BSP_C = bsp.c
FCT_C = fct.c
DAQH_C = daqh.c
PATTERN_C = pattern.c

# dummy target
dummy:

# bsp (bot saves princess)
bsp: $(BSP_C)
	$(CC) $(CFLAGS) -o bsp $(BSP_C)

# fct (file counting utility)
fct: $(FCT_C)
	$(CC) $(CFLAGS) -o fct $(FCT_C)

# daqh (dynamic array query handler)
daqh: $(DAQH_C)
	$(CC) $(CFLAGS) -o daqh $(DAQH_C)

# pattern (prints a pattern; please use n < 10)
pattern: $(PATTERN_C)
	$(CC) $(CFLAGS) -o pattern $(PATTERN_C)

# clean
clean:
	$(RM) -vf *~

