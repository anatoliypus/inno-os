path=../week01/file.txt
rm -rf path
rm -rf _ex2.txt
rm -rf ex2.txt
touch $path
echo "Anatoliy" > $path
link $path _ex2.txt
inodenumber=`ls -i $path | head -n1 | cut -d " " -f1`
find . -inum $inodenumber > ex2.txt
find . -inum $inodenumber -exec rm {} \; >> ex2.txt
ls -l >> ex2.txt # our TA Daniel said, that we have to make sure, that the link was deleted
