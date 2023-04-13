#Makefile
LIB_DIR=-L/home/piontsai/systemc-2.3.4/lib-linux64
INC_DIR=-I/home/piontsai/systemc-2.3.4/include
LIB=-lsystemc

export SYSTEMC_HOME=/home/piontsai/systemc-2.3.4
export LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64

SRC=main reduce
APP=main

all:
		g++ -o $(APP) $(addsuffix .cpp, $(SRC)) $(LIB_DIR) $(INC_DIR) $(LIB)

clean:
		rm -rf $(APP)

run:
		./$(APP)