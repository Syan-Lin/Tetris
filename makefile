# 定义变量
SRC_DIR   := ./src
INC_DIR   := ./include
BUILD_DIR := ./build
TEST_DIR  := ./test
CFLAG := -g

# 自动获取目录下的源文件和编译目标文件
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD)/%.o, $(SRCS))

make_build_dir:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
        echo "Creating directory: $(BUILD_DIR)"; \
        mkdir -p $(BUILD_DIR); \
    fi

# 构建 keyboard
KEYBOARD = keyboard
$(KEYBOARD): make_build_dir $(BUILD_DIR)/$(KEYBOARD).o
	@echo "Building $(KEYBOARD)..."; \
	g++ $(CFLAG) -I$(INC_DIR) \
	$(BUILD_DIR)/$(KEYBOARD).o $(TEST_DIR)/$(KEYBOARD).cpp -o \
	$(BUILD_DIR)/$(KEYBOARD); \
	echo "Build $(KEYBOARD) done." \

# 构建 block
BLOCK = block
$(BLOCK): make_build_dir $(BUILD_DIR)/$(BLOCK).o
	@echo "Building $(BLOCK)..."; \
	g++ $(CFLAG) -I$(INC_DIR) \
	$(BUILD_DIR)/$(BLOCK).o $(TEST_DIR)/$(BLOCK).cpp -o \
	$(BUILD_DIR)/$(BLOCK); \
	echo "Build $(BLOCK) done." \

# 编译规则
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@g++ $(CFLAG) -I$(INC_DIR) -c $< -o $@

# 清理规则
clean:
	rm -rf $(BUILD_DIR)