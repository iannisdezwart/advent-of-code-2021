if [ -z "$1" ]; then
	echo "Usage: $0 <advent of code date (1-25)>"
	exit 1
fi

echo "$1A:"
./$1A < ../Inputs/$1.input
echo
echo "$1B:"
./$1B < ../Inputs/$1.input