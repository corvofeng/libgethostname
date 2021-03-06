#   _ _ _     _                         _ _
#  | (_) |__ | | _____  ___ _ __   __ _| (_)_   _____
#  | | | '_ \| |/ / _ \/ _ \ '_ \ / _` | | \ \ / / _ \
#  | | | |_) |   <  __/  __/ |_) | (_| | | |\ V /  __/
#  |_|_|_.__/|_|\_\___|\___| .__/ \__,_|_|_| \_/ \___|
#                          |_|
#
#  (C) Fabio Busatto <fabio.busatto@sikurezza.org>

CC=gcc
CFLAGS=-fPIC
LDFLAGS=-shared -Wl,-soname,libgethostname.so
LDLIBS=-ldl

default: libgethostname.so

%.so: %.o
	$(CC) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm -f *.so *.o
