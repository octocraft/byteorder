
STATUS=0

for bin in build/*.o
do
    echo ${bin}:
    ./$bin
    [ $? -ne 0 ] && STATUS=1
    
    echo -e "\n"
done

exit $STATUS
