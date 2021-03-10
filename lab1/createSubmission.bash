#Script to create pdf and zip submission from source files in
#src/ and include/ directories
#Takes one parameter, the name (without extension) of both output files

declare -A src #src files already processed

outFilename=$1

#add main.cpp first (it'd better exist)
submitFiles="./src/main.cpp"
src[$submitFiles]=1

#Add each include/ header file if files exist in include/ dir
#and add the corresponding cpp files in order if they exist
DIR=./include
if [ "$(ls -A $DIR)" ]; then

  for f in $DIR/*; do
    submitFiles="$submitFiles $f"

    incFilename=$(basename -- "$f")
    cppFilename="./src/${incFilename%.*}.cpp"

    if test -f "$cppFilename"; then
      src[$cppFilename]=1
      submitFiles="$submitFiles $cppFilename"
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
    fi
  done
fi

#Add Makefile last
submitFiles="$submitFiles ./Makefile"

echo -e "Creating $outFilename.pdf...\n"

a2ps --pro=color --toc -E -1 --header="$outFilename" --line-numbers=1 \
  -l 90 -T 4 -o - $submitFiles | ps2pdfwr - "$outFilename".pdf

echo -e "\n\nCreating $outFilename.zip... \n"
zip "$outFilename".zip $submitFiles
