OUT=$1
shift
echo $OUT
a2ps --pro=color --toc -E -1 --header="$OUT" --line-numbers=1   \
-l 90 -T 4 -o - $*  | ps2pdfwr - "$OUT".pdf