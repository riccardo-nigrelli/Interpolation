bin_objects=$(patsubst %.c, %.o, $(wildcard ../src/*.c))

include mk/*.mk


.PHONY: all static shared clean

all: static shared

static: $(bin_objects)
	$(AR) rcs libupoalglib_s.a $^

clean:
	$(RM) $(bin_objects) *.so *.a
