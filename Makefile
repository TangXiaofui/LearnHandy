CXX=g++
CXXFLAGS=-std=c++11 -g
CXXLDFLAGS=-pthread

SRCS=$(shell find ./ -name '*.cc')
OBJS=$(SRCS:.cc=.o)

test:$(OBJS)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(CXXLDFLAGS)
	ctags -R
	cscope -Rbq
.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(OBJS) test
	rm cscope.*
	rm tags 
