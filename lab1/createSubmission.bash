
declare -A inc
declare -A src
SubmitFiles="./src/main.cpp"


DIR=./include


if [ "$(ls -A $DIR)" ]; then

  for f in $DIR/*
  do
    inc[$f]=1

    SubmitFiles="$SubmitFiles $f"


    filename=$(basename -- "$f")
    cppsrc="./src/${filename%.*}.cpp"
    src[$cppsrc]=1

    SubmitFiles="$SubmitFiles $cppsrc"

  done
fi

SubmitFiles="$SubmitFiles ./Makefile"

zip "$1".zip $SubmitFiles
./pppdf.bash $1 $SubmitFiles
