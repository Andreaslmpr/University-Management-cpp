CC = g++
CFLAGS = -Wall -Werror
LDFLAGS = -lm

SRCS = person.cpp secretary.cpp professor.cpp course.cpp semester.cpp student.cpp handlecoursefile.cpp handleprofessorfile.cpp handlestudentfile.cpp main.cpp

# Adjusting flags for C++ compilation
CXXFLAGS = $(CFLAGS)

OBJS = $(SRCS:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
