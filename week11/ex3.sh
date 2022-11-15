filename=_ex3.txt
rm -rf $filename
touch $filename
echo "Anatoliy" > $filename
chmod a-x $filename > ex3.txt
chmod u=rwx,o=rwx $filename >> ex3.txt
chmod g=u $filename >> ex3.txt
echo "we can imagine permissions state rwx as a binary number in format
abc, where a, b and c are 1 or 0 (whether corresponding permission)
is set or not. 

For example, rwx is 111 in binary format. If we translate
it to decimal, we get 7.

r_x is 101, which is 5 and so forth...

We have user permissions, group permissions and other permissions, so
we need 3 3-digit binary numbers to specify them, or just 3 decimal numbers (0-7).

For example, -rw-r--r-- is 110-100-100, or just 644.

660 means 110-110-000 -> -rw-rw----
775 means 111-111-101 -> -rwxrwxr-x
777 means 111-111-111 -> -rwxrwxrwx" >> ex3.txt
