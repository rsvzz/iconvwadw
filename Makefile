SRC_DIR = src
BIN_DIR = bin

SRC_DIR_MGTK = $(SRC_DIR)/model_gtk
SRC_DIR_MODEL = $(SRC_DIR)/model

OBJ_DIR = $(BIN_DIR)/obj

OBJ = ${OBJ_DIR}/main.o ${OBJ_DIR}/bxnav.o $(OBJ_DIR)/itemfiles.o  \
	  ${OBJ_DIR}/readfile.o ${OBJ_DIR}/readdir.o $(OBJ_DIR)/gdview.o $(OBJ_DIR)/winimg.o $(OBJ_DIR)/imgevt.o \
	  ${OBJ_DIR}/bxbody.o ${OBJ_DIR}/app.o

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
gtkmm_LIBS = `pkgconf --libs --cflags gtkmm-4.0`

TARGET = $(BIN_DIR)/app

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CXX) -o $(TARGET) $^ $(CXXFLAGS) $(gtkmm_LIBS)


$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(gtkmm_LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR_MGTK)/%.cpp
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(gtkmm_LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR_MODEL)/%.cpp
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

exe: $(TARGET)
	@echo "Executable created at $(TARGET)"
	@echo "Running the program..."
	@./$(TARGET)
	@echo "Program finished."

clean:
	@rm -rf $(BIN_DIR)
	@echo "Cleaned up object files and target binary."

