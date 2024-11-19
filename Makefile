ifeq ($(origin CXX),default)
	CXX = g++
endif

CXXFLAGS ?= -Wall -Wextra -O0 -g -std=c++20
OUT_O_DIR ?= build
COMMONINC = -I./include
SRC = ./src
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

override CXXFLAGS += $(COMMONINC)

CPPSRC = calc.cpp

PREF = $(OUT_O_DIR)/obj
CPPOBJ := $(addprefix $(PREF)/,$(CPPSRC:.cpp=.o))
DEPS = $(CPPOBJ:.o=.d)

.PHONY: all
all: calc

calc: $(CPPOBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)
	
$(CPPOBJ) : $(PREF)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DEPS) : $(PREF)/%.d : %.cpp
	@mkdir -p $(@D)
	$(CXX) -E $(CXXFLAGS) $< -MM -MT $(@:.d=.o) > $@

.PHONY: clean
clean:
	rm -rf $(CPPOBJ) $(DEPS) $(PREF) calc

# targets which we have no need to recollect deps
NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
include $(DEPS)
endif