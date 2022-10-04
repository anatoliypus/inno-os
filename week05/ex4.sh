gcc -pthread ex4.c -o ex4
test -f ex4 &&\
rm -f ex4.txt &&\
/usr/bin/time -a -o ex4.txt ./ex4 10000000 1 &&\
/usr/bin/time -a -o ex4.txt ./ex4 10000000 2 &&\
/usr/bin/time -a -o ex4.txt ./ex4 10000000 4 &&\
/usr/bin/time -a -o ex4.txt ./ex4 10000000 10 &&\
/usr/bin/time -a -o ex4.txt ./ex4 10000000 100 &&\
rm -rf ex4
