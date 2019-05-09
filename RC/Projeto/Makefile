CXXFLAGS            += -Wall
CXXFLAGS            += -Wextra
CXXFLAGS            += -Werror
CXXFLAGS            += -Wpedantic
CXXFLAGS            += -std=c++11

SHARED_INCLUDEPATH  += shared/include
SHARED_SOURCE       += $(wildcard shared/src/*.cpp)

CLIENT              += client.bin
CLIENT_INCLUDEPATH  += client/include/
CLIENT_SOURCE       := $(wildcard client/src/*.cpp) $(SHARED_SOURCE)

SERVER              += server.bin
SERVER_INCLUDEPATH  += server/include/
SERVER_SOURCE       := $(wildcard server/src/*.cpp) $(SHARED_SOURCE)

all: clean build run

build: $(SERVER) $(CLIENT)

$(SERVER):
	$(CXX) $(CXXFLAGS) -I$(SHARED_INCLUDEPATH) -I$(SERVER_INCLUDEPATH) -o $(@) $(SERVER_SOURCE)

$(CLIENT):
	$(CXX) $(CXXFLAGS) -I$(SHARED_INCLUDEPATH) -I$(CLIENT_INCLUDEPATH) -o $(@) $(CLIENT_SOURCE)

run:
	@ gnome-terminal -e ./$(SERVER)
	@ gnome-terminal -e ./$(CLIENT)
	@ gnome-terminal -e ./$(CLIENT)

clean:
	@ rm -f -v *.record

distclean: clean
	@ rm -f -v $(CLIENT) $(SERVER)

.PHONY: $(CLIENT)
.PHONY: $(SERVER)
.PHONY: build
.PHONY: clean
.PHONY: distclean
.PHONY: run
