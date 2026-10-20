# Makefile — автоматизированная сборка задачи 2.25 (C++).
#
#   make            — то же, что make release
#   make release    — исполняемый файл chess (оптимизация -O2)
#   make debug      — исполняемый файл chess_debug с отладочными символами (-g)
#   make test       — автотесты обеих сборок
#   make run ARGS="e1 e8 h4" — запуск
#   make clean      — удалить промежуточные файлы (*.o, *.d)
#   make distclean  — удалить всё собранное
#   make rebuild    — принудительная пересборка (clean + release)
#   make info       — значения мета-переменных
#
# Мета-переменные можно переопределить: make CXX=clang++ OPTFLAGS=-O3

# ---------- мета-переменные ----------
CXX       ?= g++
CXXSTD    := -std=c++17
WARNINGS  := -Wall -Wextra -Wpedantic
OPTFLAGS  ?= -O2
DBGFLAGS  ?= -g -O0 -DDEBUG
CPPFLAGS  := -Ilib -MMD -MP
LDFLAGS   ?=
RM        := rm -rf

SRC       := app/main.cpp lib/chess_threat.cpp
BUILD     := build
TARGET    := chess
TARGET_DBG:= chess_debug

OBJ_REL   := $(SRC:%.cpp=$(BUILD)/release/%.o)
OBJ_DBG   := $(SRC:%.cpp=$(BUILD)/debug/%.o)

.PHONY: all release debug test run clean distclean rebuild info FORCE
.DEFAULT_GOAL := release

all: release debug

# ---------- 1. сборка исполняемого файла ----------
release: $(TARGET)

$(TARGET): $(OBJ_REL)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD)/release/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXSTD) $(WARNINGS) $(OPTFLAGS) $(CPPFLAGS) -c $< -o $@

# ---------- 2. сборка с отладочными символами ----------
debug: $(TARGET_DBG)

$(TARGET_DBG): $(OBJ_DBG)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD)/debug/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXSTD) $(WARNINGS) $(DBGFLAGS) $(CPPFLAGS) -c $< -o $@

# ---------- тесты и запуск ----------
test: $(TARGET) $(TARGET_DBG)
	./run_tests.sh ./$(TARGET)
	./run_tests.sh ./$(TARGET_DBG)

run: $(TARGET)
	./$(TARGET) $(ARGS)

# ---------- 3. очистка ----------
clean:
	$(RM) $(BUILD)

distclean: clean
	$(RM) $(TARGET) $(TARGET_DBG)

# ---------- принудительное выполнение ----------
# rebuild выполняется всегда (PHONY); FORCE — пустая цель-«пустышка»,
# от которой можно сделать зависимой любую цель, чтобы она
# выполнялась при каждом вызове.
rebuild: distclean
	$(MAKE) release

info: FORCE
	@echo "CXX      = $(CXX) ($(shell $(CXX) --version | head -1))"
	@echo "CXXSTD   = $(CXXSTD)"
	@echo "OPTFLAGS = $(OPTFLAGS)"
	@echo "DBGFLAGS = $(DBGFLAGS)"
	@echo "SRC      = $(SRC)"
	@echo "OBJ_REL  = $(OBJ_REL)"
	@echo "OBJ_DBG  = $(OBJ_DBG)"

FORCE:

# автоматические зависимости от заголовков (-MMD -MP)
-include $(OBJ_REL:.o=.d) $(OBJ_DBG:.o=.d)
