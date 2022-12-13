CXX		 = g++
CXXFLAGS = -Wall -std=c++17 -I.
TARGET	 = bank
SRC		 = bank.cpp account.cpp accountList.cpp transferInfo.cpp utest.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)