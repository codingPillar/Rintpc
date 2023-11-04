SRC_DIR:=src
INCLUDE_DIR:=include
OUT_DIR:=out
TEST_DIR:=test

SRC_FILES:=$(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJ:=$(SRC_FILES:$(SRC_DIR)/%=$(OUT_DIR)/%.o)
SRC_OBJ_CMP:=$(SRC_FILES:$(SRC_DIR)/%=$(OUT_DIR)/%.cmp.o)
TEST_SRC:=$(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ:=$(TEST_SRC:$(TEST_DIR)/%=$(OUT_DIR)/%.test.o)
TEST_OBJ+=$(SRC_OBJ)
TEST_OBJ:=$(filter-out %/main.cpp.o,$(TEST_OBJ)) 

CURRENT_DIR:=$(shell pwd)

CXX:=g++
CXX_FLAGS:=-Wall -Werror
CXX_INC:=-I../common/include -I./include
## SHOULD NOT HAVE MANY EXTERNAL DEPENDECIES, WE WANT TO STAY LIGHTWEIGHT
CXX_LIB_PATH:=
CXX_LIBS:=

OUT_NAME:=master
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

build: $(SRC_OBJ)
	$(CXX) $(CXX_FLAGS) $^ -o $(OUT_DIR)/$(OUT_NAME) $(CXX_LIB_PATH) $(CXX_LIBS)

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