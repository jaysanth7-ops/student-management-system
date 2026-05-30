CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET   = student_app
SRCS     = main.cpp Student.cpp StudentManager.cpp
OBJS     = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) students.txt

.PHONY: all clean