TARGET=$(PREFIX)maya_obj

SCANNER=obj_scanner.l
PARSER=obj_parser.y
SCANNER_SRC=obj_scanner.cpp
PARSER_SRC=obj_parser.cpp
SRC_FILES=main.cpp\
		  obj_reader.cpp\
		  $(SCANNER_SRC)\
		  $(PARSER_SRC)

CXX=g++
LEX=flex
YACC=bison

DEBUG_FLAGS=-ggdb -O0
RELEASE_FLAGS=-static -O3 -g0 
CXX_FLAGS=$(CXXFLAGS) -std=gnu++11 -mtune=core2
LIBS=
INCS=-I./

.PHONY:all clean

all:src
	@echo CXX "$(TARGET)"
	@$(CXX) $(INCS) $(LIBS) $(CXX_FLAGS) -o $(TARGET) $(SRC_FILES)

src:scanner parser
	@echo GEN SCANNER PARSER

scanner:$(SCANNER)
	@echo LEX "$<"
	@$(LEX) -o $(SCANNER_SRC) $<

parser:$(PARSER)
	@echo YACC "$<" 
	@$(YACC) -o $(PARSER_SRC) $<

clean:
	@rm -rf $(TARGET)
	@rm -rf $(SCANNER_SRC)
	@rm -rf $(PARSER_SRC)
	@echo Clean Done.



