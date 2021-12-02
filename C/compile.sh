: ${CC=cc}

if [ -z "$1" ]; then
	echo "Usage: $0 <advent of code date (1-25)>"
	exit 1
fi

echo compiling $1A
$CC -o $1A $1A.c
echo compiling $1B
$CC -o $1B $1B.c