all: bin bin/a1 bin/a2 bin/a3 bin/a3_int128 bin/a3_gmp bin/a4_int bin/a4_unsigned bin/a5

CFLAGS=-Wall -Wextra

clean:
	rm bin/*

bin:
	mkdir -p bin

bin/a1: q1.cpp
	gcc $(CFLAGS) $< -o $@

bin/a2: q2.cpp
	g++ $(CFLAGS) $< -o $@

bin/a3: q3.cpp
	g++ $(CFLAGS) $< -o $@

bin/a3_int128: q3_int128.cpp
	g++ $< -o $@

# ./configure --prefix=/usr/local --enable-cxx
# make
# sudo make install
# http://stackoverflow.com/questions/25347054/install-gmp-library-on-mac-os-x-10-9-and-xcode
bin/a3_gmp: q3_gmp.cpp
	g++ $< -o $@ -I/usr/local/include -L/usr/local/lib -lgmp

bin/a4_int: q4_int.cpp
	g++ $(CFLAGS) $< -o $@

bin/a4_unsigned: q4_unsigned.cpp
	g++ $(CFLAGS) $< -o $@

bin/a5: q5.cpp
	g++ $(CFLAGS) $< -o $@

