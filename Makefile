# compiler env.
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	CXX=ccache clang++
	LDLIBS=-ldl -lasound
	CXXFLAGS=-std=c++2a -MMD -MP -Wall -fPIC
	SHARED_CXXFLAGS= -fPIC -shared
endif
ifeq ($(UNAME),Darwin)
	CXX=ccache clang++
	LDLIBS=-stdlib=libc++
	CXXFLAGS=-std=c++2a -MMD -MP -Wall
#	SHARED_CXXFLAGS= -flat_namespace -dynamiclib
	SHARED_CXXFLAGS=-dynamiclib
endif

LDFLAGS=-pthread

# project config
AFW_DIR=../audioframework
AFW_INC_DIR=$(AFW_DIR)/include
AFW_LIB_DIR=$(AFW_DIR)/lib

AFW_HELPER_DIR=../AndroidAudioHalHelper
AFW_HELPER_INC=$(AFW_HELPER_DIR)/src
AFW_HELPER_LIB_DIR=$(AFW_HELPER_DIR)/lib

ANDROID_HOME := $(shell printenv ANDROID_HOME)
ANDROID_MEDIA_INC=$(ANDROID_HOME)/system/media/audio/include
ANDROID_CUTIL_INC=$(ANDROID_HOME)/system/core/libcutils/include
ANDROID_FMQ_INC=$(ANDROID_HOME)/system/libfmq/include
ANDROID_UTILS_INC=$(ANDROID_HOME)/system/core/libutils/include
ANDROID_HIDL_INC=$(ANDROID_HOME)/system/libhidl/base/include
ANDROID_LOG_INC=$(ANDROID_HOME)/system/core/liblog/include

SRC_DIR = ./src
OBJ_DIR = ./out
BIN_DIR = ./bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
AFWHAL_TARGET =$(BIN_DIR)/afwhal


# --- Build for sink example(shared) ------------
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	AFW_HELPER_DYNAMIC_LIB = $(AFW_HELPER_LIB_DIR)/libaudiohalhelper.so
	AFW_DYNAMIC_LIB = $(AFW_LIB_DIR)/libafw.so
endif
ifeq ($(UNAME),Darwin)
	AFW_HELPER_DYNAMIC_LIB = $(AFW_HELPER_LIB_DIR)/libaudiohalhelper.dylib
	AFW_DYNAMIC_LIB = $(AFW_LIB_DIR)/libafw.dylib
endif
DEPS = $(OBJS:.o=.d)

default: $(AFWHAL_TARGET)
.PHONY: default

$(AFWHAL_TARGET): $(OBJS)
	@[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS) $(AFW_DYNAMIC_LIB) $(AFW_HELPER_DYNAMIC_LIB)

$(OBJS): $(SRCS)
	echo Android home is $(ANDROID_HOME)

	@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I $(AFW_INC_DIR) -I $(AFW_HELPER_INC) -I $(ANDROID_MEDIA_INC) -I $(ANDROID_CUTIL_INC) -I $(ANDROID_FMQ_INC) -I $(ANDROID_UTILS_INC) -I $(ANDROID_HIDL_INC) -I $(ANDROID_LOG_INC) -c $(SRC_DIR)/$(notdir $(@:.o=.cpp)) -o $@

-include $(DEPS)

# --- clean up ------------------------
clean:
	rm -f $(OBJS) $(AFWHAL_TARGET)
