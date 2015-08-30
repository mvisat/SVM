
CXXFLAGS += -O2 -Wall
STR_DUMMY := __DUMMY__
ifeq ($(OS),Windows_NT)
	CHAR_PATH 	:= \\
	CMD_SEP		:= &
	CMD_MKDIR 	:= if not exist $(STR_DUMMY) mkdir
	CMD_RMDIR 	:= if exist $(STR_DUMMY)$(CHAR_PATH) rmdir /S /Q
else
	CHAR_PATH 	:= /
	CMD_SEP		:= ;
	CMD_MKDIR 	:= mkdir -p
	CMD_RMDIR 	:= rm -rf
    LDFLAGS 	+= -ldl
endif

SRC_DIR := src
BIN_DIR	:= bin
MODULES := common command

MODULE_SRC_DIR	 := $(addprefix $(SRC_DIR)/,$(MODULES))
MODULE_BUILD_DIR := $(addprefix $(BIN_DIR)/,$(MODULES))

SRC       := $(foreach sdir,$(MODULE_SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(MODULE_SRC_DIR))

vpath %.cpp $(MODULE_SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CXX) $(INCLUDES) -c $$< -o $$@ $(CXXFLAGS) $(LDFLAGS)
endef

define make-bin
	$(CXX) $^ -o $(BIN_DIR)$(CHAR_PATH)$@ $(CXXFLAGS) $(LDFLAGS)
endef

.PHONY: all checkdirs clean

all: checkdirs svm svmc

svm: $(OBJ) $(foreach sdir,$(SRC_DIR)/interpreter,$(wildcard $(sdir)/*.cpp))
	$(make-bin)

svmc: $(OBJ) $(foreach sdir,$(SRC_DIR)/compiler,$(wildcard $(sdir)/*.cpp))
	$(make-bin)

checkdirs: $(MODULE_BUILD_DIR)

$(MODULE_BUILD_DIR):
	@$(subst $(STR_DUMMY),$(subst /,$(CHAR_PATH),$@),$(CMD_MKDIR)) $(subst /,$(CHAR_PATH),$@)

clean:
	$(foreach bdir,$(MODULE_BUILD_DIR),$(subst $(STR_DUMMY),$(subst /,$(CHAR_PATH),$(bdir)),$(CMD_RMDIR)) $(subst /,$(CHAR_PATH),$(bdir)) $(CMD_SEP))

$(foreach bdir,$(MODULE_BUILD_DIR),$(eval $(call make-goal,$(bdir))))
