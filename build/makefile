############################################################################
#
#  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
#
#  This file is part of the Coin library.
#
#  This file may be distributed under the terms of the Q Public License
#  as defined by Troll Tech AS of Norway and appearing in the file
#  LICENSE.QPL included in the packaging of this file.
#
#  If you want to use Coin in applications not covered by licenses
#  compatible with the QPL, you can contact SIM to aquire a
#  Professional Edition license for Coin.
#
#  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
#  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
#
############################################################################

#****************************************************************
#
# Makefile for Qt component classes of Coin
#
# Usage:
#       make                    defaults to `make coinqt'
#       make coinqt             make Qt component library for Coin
#	make coinqt_release     make libCoinQt.a release
#       make oivqt              make Qt component library for Open Inventor 2.5
#
#****************************************************************

TIME_START := $(shell date +"%k*3600+%M*60+%S")
TIME_NOW    = $(shell date +"%k*3600+%M*60+%S")

all: coinqt

header:
	@echo -e "\033[34m\n" \
	"\t****************************************************************\n" \
	"\t*                 COMPILING \"Qt component classes\"             *\n" \
	"\t****************************************************************\n" \
	"\033[0m";

footer:
	@( now=`echo "$(TIME_NOW)" | sed -e 's/\([^0-9]\)0/\1/g'`; \
	   start=`echo "$(TIME_START)" | sed -e 's/\([^0-9]\)0/\1/g'`; \
	   now=`echo $$[now]`; \
	   start=`echo $$[start]`; \
	   time=$$[$$now-$$start]; \
	   mins=$$[$$time/60]; \
	   secs=$$[$$time%60]; \
	   if [ $$mins -lt 10 ]; then mins="0"$$mins; fi; \
	   if [ $$secs -lt 10 ]; then secs="0"$$secs; fi; \
	echo -e "\033[34m\n" \
	"\t****************************************************************\n" \
	"\t*         COMPILATION TIME: $$mins minutes and $$secs seconds.         *\n" \
	"\t****************************************************************\n" \
	"\033[0m"; )


coinqt: header makefile.coinqt .coinqt footer

coinqt_release: header makefile.coinqtrel .coinqtrel footer

oivqt: header makefile.oivqt .oivqt footer

###

.coinqt:
	@mkdir -p coinqtobjects
	@$(MAKE) -f makefile.coinqt

makefile.coinqt: coinqt.pro common.pro
	tmake -p common.pro coinqt.pro -o makefile.coinqt

.coinqtrel:
	@mkdir -p coinqtobjectsrel
	@$(MAKE) -f makefile.coinqtrel

makefile.coinqtrel: coinqtrelease.pro common.pro
	tmake -p common.pro coinqtrelease.pro -o makefile.coinqtrel

.oivqt:
	@mkdir -p oivqtobjects
	@$(MAKE) -f makefile.oivqt

makefile.oivqt: oivqt.pro common.pro
	tmake -p common.pro oivqt.pro -o makefile.oivqt

### Documentation ###

docs: .docs

.docs:
	doxygen ../docs/qtcomponents.doxygen
