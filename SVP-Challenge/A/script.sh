#!/bin/bash

arr=("8 12 20 30 40")
make
for i in $arr
do
    echo Currently, n = $i
    ./main $i
    echo
    echo
    echo Done with n = $i
    echo ----------------------------------------------------------------------------------------------------------------------------------
done
