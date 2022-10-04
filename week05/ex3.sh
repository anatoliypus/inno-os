gcc -pthread ex3.c -o ex3
test -f ex3 &&\
rm -f ex3.txt &&\
/usr/bin/time -a -o ex3.txt ./ex3 10000000 1 &&\
/usr/bin/time -a -o ex3.txt ./ex3 10000000 2 &&\
/usr/bin/time -a -o ex3.txt ./ex3 10000000 4 &&\
/usr/bin/time -a -o ex3.txt ./ex3 10000000 10 &&\
/usr/bin/time -a -o ex3.txt ./ex3 10000000 100 &&\
rm -rf ex3
