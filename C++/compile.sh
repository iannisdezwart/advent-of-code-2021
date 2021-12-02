: ${CXX=g++}

if [ -z "$1" ]; then
	echo "Usage: $0 <advent of code date (1-25)>"
	exit 1
fi

echo compiling $1A
$CXX -o $1A $1A.cpp
echo compiling $1B
$CXX -o $1B $1B.cpp