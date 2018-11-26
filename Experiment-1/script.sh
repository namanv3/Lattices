make
directories=($(ls -d */ | cut -f1 -d'/'))

for dir in ${directories[@]}; do
    cd $dir
    files=($(ls))
    cd ..
    for file in ${files[@]}; do
        echo $dir/$file
        python3 scrap_matrix_from_file.py $dir/$file
        ./main matrix.txt >> $dir.txt
        echo ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ >> $dir.txt
    done
done
