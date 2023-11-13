SRC_DIR:=src
INCLUDE_DIR:=include
OUT_DIR:=out

SRC_FILES:=$(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJ:=$(SRC_FILES:$(SRC_DIR)/%=$(OUT_DIR)/%.o)
SRC_OBJ_CMP:=$(SRC_FILES:$(SRC_DIR)/%=$(OUT_DIR)/%.cmp.o)

CXX:=g++
CXX_FLAGS:=-Wall -Werror
CXX_INC:=-I./include
## SHOULD NOT HAVE MANY EXTERNAL DEPENDECIES, WE WANT TO STAY LIGHTWEIGHT
CXX_LIB_PATH:=
CXX_LIBS:=-pthread

CMP_DATABASE_BUILDER:=comp_database_gen
CMP_DATABASE_FILE:=compile_commands.json

CURRENT_DIR:=$(shell pwd)

## FILE TYPE RULES
define COMPILE =
$(CXX) $(CXX_FLAGS) $(CXX_INC) -c $< -o $@
endef
$(OUT_DIR)/%.o:$(SRC_DIR)/%
	$(COMPILE)

build: $(SRC_OBJ)

## COMPILE COMMANDS
$(OUT_DIR)/%.cmp.o:$(SRC_DIR)/%
	$(CMP_DATABASE_BUILDER) $(CMP_DATABASE_FILE) $(CURRENT_DIR) "$(COMPILE)" $<
compileCommands: $(SRC_OBJ_CMP)
	$(CMP_DATABASE_BUILDER) $(CMP_DATABASE_FILE) --end

clean:
	rm -rf $(OUT_DIR)/*