
DEBUG=0

BUILD=$(MAKE) -nologo DEBUG=$(DEBUG)

all: all.real

DIRS=crt       \

all.real:
	@for %%i in ($(DIRS)) do @if exist %%i echo *** Compiling %%i & cd %%i & $(BUILD) & cd ..

clean:
	@for %%i in ($(DIRS)) do @if exist %%i echo *** Cleaning %%i & cd %%i & $(BUILD) clean & cd ..
	@if exist *~ erase *~

distclean: clean

help:
	@echo "DEBUG=[0|1] - If set, will compile debug build without optimization and with instrumentation"

