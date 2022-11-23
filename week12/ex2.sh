touch lofsdisk/file1
echo "Anatoliy" > lofsdisk/file1
touch lofsdisk/file2
echo "Pushkarev" > lofsdisk/file2
gcc ex2.c -o ex2
cp ex2 lofsdisk/ex2

mkdir lofsdisk/bin
cp /usr/bin/echo lofsdisk/bin/echo
cp /usr/bin/ls lofsdisk/bin/ls
cp /usr/bin/bash lofsdisk/bin/bash
cp /usr/bin/cat lofsdisk/bin/cat

list="$(ldd lofsdisk/bin/echo | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp --parents "$i" "lofsdisk/${chr}"; done
list="$(ldd lofsdisk/bin/ls | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp --parents "$i" "lofsdisk/${chr}"; done
list="$(ldd lofsdisk/bin/bash | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp --parents "$i" "lofsdisk/${chr}"; done
list="$(ldd lofsdisk/bin/cat | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp --parents "$i" "lofsdisk/${chr}"; done

sudo chroot lofsdisk ./ex2 > ex2.txt
echo "--------------------" >> ex2.txt
./ex2 >> ex2.txt
rm -rf ex2
