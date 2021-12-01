CXXFLAGS = -Wall -Wextra -g -std=c++17

.PHONY: all
all:
	for src in `find . -name "*.cpp"`; do \
		echo "compiling $$src"; \
		$(CXX) $(CXXFLAGS) -o $${src%.cpp} $$src; \
	done
