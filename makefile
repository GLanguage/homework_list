INC_DIR = ./include
BIN_DIR = ./bin
SRC_DIR = ./src
OBJ_DIR = ./obj

SRC = ${wildcard ${SRC_DIR}/*.cpp}
OBJ = ${patsubst %.cpp, ${OBJ_DIR}/%.o, ${notdir ${SRC}}}

TARGET = homework
BIN_TARGET = ${BIN_DIR}/${TARGET}

CXX := g++
CXXFLAGS := -I${INC_DIR}

${BIN_TARGET} : ${OBJ}
	${CXX} -o $@ ${OBJ}

${OBJ_DIR}/%.o : ${SRC_DIR}/%.cpp
	${CXX} -o $@ ${CXXFLAGS} -c $<

.PHONY : clean uninstall

clean :
	@find ${OBJ_DIR} -name *.o -exec rm -rf {} \;
	@echo "Cleaned."

uninstall :
	@find ${OBJ_DIR} -name *.o -exec rm -rf {} \;
	@rm -rf ${BIN_TARGET}
	@echo "Uninstalled."