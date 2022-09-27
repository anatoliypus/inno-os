gcc ex3.c -o ex3

echo Running with n=3!
./ex3 3 &

for i in $(seq 1 3);
  do
  pstree $$ -p
  sleep 5;
  done

echo Running with n=5!
./ex3 5 &

for i in $(seq 1 5);
  do
  pstree $$ -p
  sleep 5;
  done

rm -f ex3
