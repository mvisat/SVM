
CXXFLAGS += -O2 -Wall -m32
ifneq ($(OS),Windows_NT)
    LDFLAGS += -ldl
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
	$(CXX) $^ -o $(BIN_DIR)/$@ $(CXXFLAGS) $(LDFLAGS)
endef

.PHONY: all checkdirs clean

all: checkdirs svm svmc

svm: $(OBJ) $(foreach sdir,$(SRC_DIR)/interpreter,$(wildcard $(sdir)/*.cpp))
	$(make-bin)

svmc: $(OBJ) $(foreach sdir,$(SRC_DIR)/compiler,$(wildcard $(sdir)/*.cpp))
	$(make-bin)

checkdirs: $(MODULE_BUILD_DIR)

$(MODULE_BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(MODULE_BUILD_DIR)

$(foreach bdir,$(MODULE_BUILD_DIR),$(eval $(call make-goal,$(bdir))))
