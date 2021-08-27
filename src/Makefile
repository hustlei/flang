all: initdir compiler jit
.PHONY: clean

CXX = clang++
CPPFLAGS = `llvm-config --cppflags` -g
LINKFLAGS = `llvm-config --ldflags --libs` 

BUILDDIR = ../build/
OBJDIR = $(BUILDDIR)objs/
OBJS =  $(OBJDIR)irgen.o $(OBJDIR)parser.o $(OBJDIR)lexer.o
SRCS = IRGen/irgen.cpp Parse/parser.cpp Lex/lexer.cpp

initdir:
	@mkdir -p ../build
	@mkdir -p ../build/objs

Parse/parser.cpp: Parse/parser.y
	bison -d -o $@ $<
    
Lex/lexer.cpp: Lex/lexer.l
	reflex --flex --bison -o $@ $<
# --flex --bison or --yy
	
$(OBJDIR)%.o: IRGen/%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<
$(OBJDIR)%.o: Parse/%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<
$(OBJDIR)%.o: Lex/%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<
$(OBJDIR)%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

compiler:  $(SRCS) $(OBJS) $(OBJDIR)compiler.o
	$(CXX) $(LINKFLAGS) -o $@ $(OBJS) $(OBJDIR)compiler.o  -lreflex
    
jit:  $(SRCS) $(OBJS) $(OBJDIR)jit.o
	$(CXX) $(LINKFLAGS) -o $@ $(OBJS) $(OBJDIR)jit.o  -lreflex

clean:
	rm -rf ../build/*
	rm -f Lex/lexer.cpp
	rm -f Parse/parser.hpp Parse/parser.cpp
	rm -f compiler jit interpreter
	rm -f *.o
	rm -f program a.out
