#最后形成的Makefile
INCL=-I./include
LIB=-ljsoncpp -lmysqlclient -pthread
# BIN=./bin
OBJ1=tcp_server.o
OBJ2=mysql_helper.o

.SUFFIXES: .cpp
.cpp.o:
	g++ ${INCL} -c $<


all: tcp_server

#C++编译
tcp_server:${OBJ1} ${OBJ2} 
	@echo "============开始编译============"
	g++ -o  $@ $? ${LIB}
	@rm -f $?
	# @cp $@ ${BIN}
	@echo "============编译结束============"
	@echo ""
