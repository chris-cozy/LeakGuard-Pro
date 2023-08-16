CC := clang
CFLAGS := -Wall -g
LDFLAGS := -ldl

BINS := leakcount
SHARED_BINS := memory_shim.so

all: $(BINS) $(SHARED_BINS)

%.so: %.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^ $(LDFLAGS)

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BINS) $(SHARED_BINS)
