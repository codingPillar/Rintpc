SRC_DIR:=src
INCLUDE_DIR:=include
OUT_DIR:=out
TEST_DIR:=test
COMMON_DIR:=../common

COMMON_SRC:=$(wildcard $(COMMON_DIR)/$(SRC_DIR)/*.cpp)
COMMON_SRC_OBJ:=$(COMMON_SRC:$(COMMON_DIR)/$(SRC_DIR)/%=$(COMMON_DIR)/$(OUT_DIR)/%.o)

SRC_FILES:=$(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJ:=$(filter-out $(SRC_DIR)/listener.cpp $(SRC_DIR)/publisher.cpp,$(SRC_FILES))
SRC_OBJ:=$(SRC_OBJ:$(SRC_DIR)/%=$(OUT_DIR)/%.o)
SRC_OBJ+=$(COMMON_SRC_OBJ)
SRC_OBJ_CMP:=$(SRC_FILES:$(SRC_DIR)/%=$(OUT_DIR)/%.cmp.o)

TEST_SRC:=$(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ:=$(TEST_SRC:$(TEST_DIR)/%=$(OUT_DIR)/%.test.o)
TEST_OBJ+=$(SRC_OBJ)

CURRENT_DIR:=$(shell pwd)

CXX:=g++
CXX_FLAGS:=-Wall -Werror
CXX_INC:=-I../common/include -I./include
## SHOULD NOT HAVE MANY EXTERNAL DEPENDECIES, WE WANT TO STAY LIGHTWEIGHT
CXX_LIB_PATH:=
CXX_LIBS:=

LISTENER_OUT_NAME:=listener
PUBLISHER_OUT_NAME:=publisher
OUT_TESTS:=tests

CMP_DATABASE_BUILDER:=comp_database_gen
CMP_DATABASE_FILE:=compile_commands.json

## FILE TYPE RULES
define COMPILE =
$(CXX) $(CXX_FLAGS) $(CXX_INC) -c $< -o $@
endef
$(OUT_DIR)/%.o:$(SRC_DIR)/%
	$(COMPILE)
$(OUT_DIR)/%.test.o:$(TEST_DIR)/%
	$(COMPILE)

build: $(SRC_OBJ) $(OUT_DIR)/listener.cpp.o $(OUT_DIR)/publisher.cpp.o
	echo $(SRC_OBJ)
	$(CXX) $(CXX_FLAGS) $(SRC_OBJ) $(OUT_DIR)/listener.cpp.o -o $(OUT_DIR)/$(LISTENER_OUT_NAME) $(CXX_LIB_PATH) $(CXX_LIBS)
	$(CXX) $(CXX_FLAGS) $(SRC_OBJ) $(OUT_DIR)/publisher.cpp.o -o $(OUT_DIR)/$(PUBLISHER_OUT_NAME) $(CXX_LIB_PATH) $(CXX_LIBS)

test: $(TEST_OBJ)
	$(CXX) $(CXX_FLAGS) $^ -o $(OUT_DIR)/$(OUT_TESTS) $(CXX_LIB_PATH) $(CXX_LIBS) -lgtest
	./$(OUT_DIR)/$(OUT_TESTS)

## COMPILE COMMANDS
$(OUT_DIR)/%.cmp.o:$(SRC_DIR)/%
	$(CMP_DATABASE_BUILDER) $(CMP_DATABASE_FILE) $(CURRENT_DIR) "$(COMPILE)" $<
compileCommands: $(SRC_OBJ_CMP)
	$(CMP_DATABASE_BUILDER) $(CMP_DATABASE_FILE) --end

clean:
	rm -rf $(OUT_DIR)/*