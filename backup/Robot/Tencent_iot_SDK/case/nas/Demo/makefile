TARGETS := NasSDKDemo
OBJS	:= $(patsubst %.cpp, %.o, $(wildcard *.cpp))
CROSS   := 

#需要包含的头文件搜索路径
INCLUDE += -I../../../include   #txdevicesdk headers
INCLUDE += -I../include         #libnassdk.so headers
INCLUDE += -I./util
INCLUDE += -I./rapidjson
INCLUDE += -I./

#需要引用的库
LIB     += -L../../../lib -ltxdevicesdk   
LIB	+= -L../lib -lnassdk
LIB     += -lpthread  -lrt  

#需要的标志位
CXX	:= $(CROSS)g++
STRIP	:= $(CROSS)strip
CXXFLAGS+= -fpermissive -Wall -Wno-deprecated -Wno-conversion-null -fpermissive -Wno-format -std=c++0x -D_FILE_OFFSET_BITS=64
CXXFLAGS += -g
#增加根据d文件自动推导编译的标志
CXXFLAGS    += $(INCLUDE)


-include util/util.mk

#deps
DEPS    += $(patsubst %.o, %.d, $(OBJS))

.PHONY: all
all: $(DEPS) $(OBJS)
	$(CXX) -o $(TARGETS) $(OBJS) $(LIB)
	#$(STRIP) $(TARGETS)

-include $(DEPS)

%.d: %.cpp
	@echo "make $@"
	@set -e $@ &&  rm -f $@; \
	$(CXX) -MM $(CFLAGS) $(CXXFLAGS) $< > $@; \

.PHONY:clean
clean:
	rm -rf $(TARGETS) $(OBJS) $(DEPS)

