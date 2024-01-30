CXX = g++

test01.o: q3_parser.cpp lex.yy.c AST.hpp
	$(CXX) -o $@ q3_parser.cpp lex.yy.c

q3_parser.cpp: q3.yy
	bison -d -o $@ $<

lex.yy.c: q3.ll
	flex $<

clean:
	rm -f test01.o q3_parser.cpp lex.yy.c q3_parser.hpp

