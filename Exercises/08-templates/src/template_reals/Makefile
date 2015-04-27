
CXX  ?= g++
CC   = $(CXX)
BASE = $(PWD)

CXXFLAGS ?= -O
# -g       generate code suitable for the debugger
# -p       generate code suitable for the profiler
# -O       attemp code optimizations

LDFLAGS = -Wall

SRCDIR  = src

BUILD   = $(wildcard *.cpp)
SRCS	= $(BUILD) $(wildcard $(SRCDIR)/*.cpp)
HDRS 	= $(wildcard *.hpp) $(wildcard $(SRCDIR)/*.hpp)
OBJS 	= $(BUILD:.cpp=.o)
EXEC	= $(OBJS:.o=)


.PHONY : all clean clan-all depend 

DEPEND= makedepend

all: $(EXEC)
	@echo Compilation completed. Enjoy!

doc: Doxyfile $(SRCS) $(HDRS)
	doxygen Doxyfile && touch doc

clean:
	for dustfile in $(OBJS) $(EXEC); do \
	!( test -e $$dustfile ) || rm $$dustfile; \
	done

clean-all: clean
	-rm doc/ -rf

depend: $(SRCS)
	$(DEPEND) -Y. $(SRCS)
	cd $(SRCDIR) &&	$(MAKE) depend

# DO NOT DELETE THIS LINE -- make depend depends on it.
