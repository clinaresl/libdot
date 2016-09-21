bin_PROGRAMS=parser
parser_SOURCES=parser.cc parser.1 xmalloc.c system.h aclocal.m4 getopt.c getopt1.c getopt.h
parser_LDADD=$(DOT_LIBS)

#  uncomment the following if parser requires the math library
#parser_LDADD=-lm

EXTRA_DIST=parser.lsm.in #NAME.texinfo parser.spec.in

#  if you write a self-test script named `chk', uncomment the
#  following and add `chk' to the EXTRA_DIST list
#TESTS=chk

#  build and install the .info pages
info_TEXINFOS = parser.texi
parser_TEXINFOS = gpl.texi

#  install the man pages
man_MANS=parser.1

# disable the following lines for enabling extra gdb debugging
# information
# AM_CFLAGS=-Wall -ggdb -std=c++11
# AM_CXXFLAGS=-Wall -ggdb $(DOT_CFLAGS) -std=c++11

# disable the following lines for compiling the optimized version
AM_CFLAGS=-Wall -O3 -std=c++11
AM_CXXFLAGS=-Wall -O3 $(DOT_CFLAGS) -std=c++11

# suffixes rules for creating .ps/.pdf code outputs
A2PS=a2ps
PS2PDF=ps2pdf

SUFFIXES = .ps .pdf

.h.ps:
	$(A2PS) -C -g $< -o $@

.cc.ps:
	$(A2PS) -C -g $< -o $@

.ps.pdf: .ps
	$(PS2PDF) $< $@
