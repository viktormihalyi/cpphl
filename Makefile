CXX = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -Werror -Wdeprecated -pedantic
OBJECTS = main.o brush.o regexwrapper.o highlighter.o stringutils.o renderer.o
EXECUTABLE = cpphl

all: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $(EXECUTABLE)

brush.o: brush.cpp brush.h stringutils.h
	$(CXX) $(CPPFLAGS) -c brush.cpp

highlighter.o: highlighter.cpp highlighter.h brush.h renderer.h regexwrapper.h stringutils.h
	$(CXX) $(CPPFLAGS) -c highlighter.cpp

main.o: main.cpp highlighter.h brush.h renderer.h regexwrapper.h
	$(CXX) $(CPPFLAGS) -c main.cpp

regexwrapper.o: regexwrapper.cpp regexwrapper.h brush.h stringutils.h
	$(CXX) $(CPPFLAGS) -c regexwrapper.cpp

renderer.o: renderer.cpp renderer.h regexwrapper.h brush.h stringutils.h
	$(CXX) $(CPPFLAGS) -c renderer.cpp

stringutils.o: stringutils.cpp stringutils.h
	$(CXX) $(CPPFLAGS) -c stringutils.cpp

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
