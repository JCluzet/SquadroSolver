# #infinite loop
# while :
# do
#     open -a Visual\ Studio\ Code DeepLearning.txt
# done

## find the shortest line in DeepLaaaaarning.txt
#!/bin/sh
result=100000
shortest=""
# read file DeepLaaaaarning.txt line by line
# while read line
# do
#     # if the line is shorter than result, then update result and shortest
#     if [ ${#line} -lt $result ]
#     then
#         result=${#line}
#         shortest=$line
#     fi
# done < DeepLaaaaarning.txt

while read line
do
    output=$(echo $line | wc -c)
    # printf "$output\n"
    if [ $output -lt $result ]
    then
        result=$output
        shortest=$line
        echo "$shortest\n"
    fi
done < DeepLearning.txt 

echo "$shortest"