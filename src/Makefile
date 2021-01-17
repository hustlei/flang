all: initdir compiler jit
.PHONY: clean

CXX = clang++
CPPFLAGS = `llvm-config --cppflags` -g
LINKFLAGS = `llvm-config --ldflags --libs`

BUILDDIR = ../build/
OBJDIR = $(BUILDDIR)objs/
OBJS =  $(OBJDIR)irgen.o $(OBJDIR)parser.o $(OBJDIR)lexer.o
SRCS = CodeGen/irgen.cpp Parse/cpp/parser.cpp Lex/cpp/lexer.cpp

initdir:
	@mkdir -p ../build
	@mkdir -p ../build/objs

Parse/cpp/parser.cpp: Parse/bison/parser.y
	bison -d -o $@ $<
    
Lex/cpp/lexer.cpp: Lex/flex/lexer.l
	flex -o $@ $<
	
$(OBJDIR)%.o: CodeGen/%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<
$(OBJDIR)%.o: Parse/cpp/%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<
$(OBJDIR)%.o: Lex/cpp/%.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<
$(OBJDIR)%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

compiler:  $(SRCS) $(OBJS) $(OBJDIR)compiler.o
	$(CXX) $(LINKFLAGS) -o $@ $(OBJS) $(OBJDIR)compiler.o
    
jit:  $(SRCS) $(OBJS) $(OBJDIR)jit.o
	$(CXX) $(LINKFLAGS) -o $@ $(OBJS) $(OBJDIR)jit.o

clean:
	rm -rf ../build/*
	rm -rf Lex/cpp/*
	rm -rf Parse/cpp/*
	rm -f compiler jit interpreter
	rm -f *.o
	rm -f program a.out
