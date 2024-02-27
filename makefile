# 定义变量
SRC_DIR   := ./src
INC_DIR   := ./include
BUILD_DIR := ./build
TEST_DIR  := ./test
CFLAG := -g

# 自动获取目录下的源文件和编译目标文件
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
INCLUDE := -I$(INC_DIR) -I$(TEST_DIR)

make_build_dir:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
        echo "Creating directory: $(BUILD_DIR)"; \
        mkdir -p $(BUILD_DIR); \
    fi

# 构建主程序
MAIN = main
$(MAIN): make_build_dir $(OBJS)
	@echo "Building $(MAIN)..."; \
	g++ $(CFLAG) $(INCLUDE) \
	$(OBJS) $(MAIN).cpp -o \
	$(MAIN); \
	echo "Build $(MAIN) done." \

# 构建 keyboard
KEYBOARD = keyboard
$(KEYBOARD): make_build_dir $(BUILD_DIR)/$(KEYBOARD).o
	@echo "Building $(KEYBOARD)..."; \
	g++ $(CFLAG) $(INCLUDE) \
	$(BUILD_DIR)/$(KEYBOARD).o $(TEST_DIR)/$(KEYBOARD).cpp -o \
	$(BUILD_DIR)/$(KEYBOARD); \
	echo "Build $(KEYBOARD) done." \

# 构建 display
DISPLAY = display
$(DISPLAY): make_build_dir $(BUILD_DIR)/$(DISPLAY).o $(OBJS)
	@echo "Building $(DISPLAY)..."; \
	g++ $(CFLAG) $(INCLUDE) \
	$(OBJS) $(TEST_DIR)/$(DISPLAY).cpp -o \
	$(BUILD_DIR)/$(DISPLAY); \
	echo "Build $(DISPLAY) done." \

# 构建测试
TEST = test
$(TEST): make_build_dir $(BUILD_DIR)/$(TEST).o $(OBJS)
	@echo "Building $(TEST)..."; \
	g++ $(CFLAG) $(INCLUDE) \
	$(OBJS) $(BUILD_DIR)/$(TEST).o $(TEST).cpp -o \
	$(BUILD_DIR)/$(TEST); \
	echo "Build $(TEST) done." \

$(BUILD_DIR)/$(TEST).o: $(TEST_DIR)/$(TEST).cpp
	g++ $(CFLAG) $(INCLUDE) -c $< -o $@

# 编译规则
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAG) $(INCLUDE) -c $< -o $@

# 清理规则
clean:
	@rm -rf $(BUILD_DIR) \
	rm $(MAIN)