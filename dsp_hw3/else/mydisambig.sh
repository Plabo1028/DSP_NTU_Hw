myexec="./disambig -lm bigram.lm -m Big5-ZhuYin.map"

for i in $(seq 1 10)
do
   $myexec < ../testdata_/$i.txt > ../my_output/my_ans$i.txt
   echo "ans$i done..."
done