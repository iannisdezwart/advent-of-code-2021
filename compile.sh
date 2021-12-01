if [ -z "$1" ]; then
	echo "Usage: $0 <date>"
	exit 1
fi

echo compiling $1A
$CXX $CXXFLAGS -o $1A $1A.cpp
echo compiling $1B
$CXX $CXXFLAGS -o $1B $1B.cpp