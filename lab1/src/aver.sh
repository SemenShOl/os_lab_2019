count=1
sum=0
while read arg
do
count=$(( $count + 1 ))
sum=$(($sum + $arg))
done
ans=$(($sum/$count))
echo $ans
# echo "Finished"