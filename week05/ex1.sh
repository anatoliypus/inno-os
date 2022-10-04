gcc publisher.c -o publisher
gcc subscriber.c -o subscriber
test -f publisher && gnome-terminal -- ./publisher $1
for i in $(seq 1 $1);
do
    test -f subscriber && gnome-terminal -- ./subscriber
done
rm -rf publisher
rm -rf subscriber
