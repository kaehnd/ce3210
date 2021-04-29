#Script to create pdf and zip submission from source files in
#src/ and inc/ directories
#Takes one parameter, the name (without extension) of both output files

declare -A src #src files already processed

outFilename=$1

rm -r -f ./testSub
rm -f ./$outFilename.pdf
rm -f ./$outFilename.zip
mkdir -p tempFiles


#add main.cpp first (it'd better exist)
submitFiles="./src/main.cpp"
src[$submitFiles]=1

cp ./src/main.cpp ./tempFiles/main.cpp
compileFiles="./main.cpp"

#Add each inc/ header file if files exist in inc/ dir
#and add the corresponding cpp files in order if they exist
DIR=./inc
if [ "$(ls -A $DIR)" ]; then

  for f in $DIR/*; do
    submitFiles="$submitFiles $f"
    
    incFilename=$(basename -- "$f")
    cp $f ./tempFiles/$incFilename

    cppFileName="${incFilename%.*}.cpp"
    cppFilePath="./src/$cppFileName"

    if test -f "$cppFilePath"; then
      src[$cppFilePath]=1
      submitFiles="$submitFiles $cppFilePath"
      cp $cppFilePath ./tempFiles/$cppFileName
      compileFiles="$compileFiles ./$cppFileName"

    fi
  done
fi

#Add any .cpp files that do not have header files (not sure why this would happen)
DIR=./src
if [ "$(ls -A $DIR)" ]; then

  for f in $DIR/*; do
    if [ ${src["$f"]} -ne 1 ]; then
      src[$f]=1
      submitFiles="$submitFiles $f"
      fileName=$(basename -- "$f")
      cp $f ./tempFiles/$fileName
      compileFiles="$compileFiles ./$fileName"
    fi
  done
fi

cp ../Template_Makefile ./tempFiles/Makefile
sed -i "s/<LABNAME>/$outFilename/" ./tempFiles/Makefile

cd tempFiles
echo -e "\n\nCreating $outFilename.zip... \n"
zip "../$outFilename".zip ./*
cd ..

submitFiles="$submitFiles ./tempFiles/Makefile"

echo -e "Creating $outFilename.pdf...\n"

a2ps --pro=color --toc -E -1 --header="$outFilename" --line-numbers=1 \
  -l 90 -T 4 -o - $submitFiles | ps2pdfwr - "$outFilename".pdf



rm -r ./tempFiles
echo -e "\nTesting Submission.."
unzip ./$outFilename.zip -d ./testSub/
cd ./testSub
make
valgrind ./$outFilename
