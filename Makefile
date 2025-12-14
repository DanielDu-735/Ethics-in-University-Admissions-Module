CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

all: admissions

print: admissions
	./admissions

admissions: StudentApplicant.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@
main.o: main.cpp StudentApplicant.h Comparators.h
	$(CXX) $(CXXFLAGS) $< -c -o $@
StudentApplicant.o: StudentApplicant.cpp StudentApplicant.h
	$(CXX) $(CXXFLAGS) $< -c -o $@
clean:
	rm -f *.o admissions


