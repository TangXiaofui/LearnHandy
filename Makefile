CXX=g++
CXXFLAGS=-std=c++11 -g
CXXLDFLAGS=-pthread


main:main.o slice.o logging.o util.o net.o port.o thread.o
	$(CXX) $^ -o $@ $(CXXFLAGS) $(CXXLDFLAGS)
	ctags -R
	cscope -Rbq
.cc.o:
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY:clean
clean:
	rm -f *.o  main 
	rm cscope.*
	rm tags 
