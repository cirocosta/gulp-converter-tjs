#!/bin/bash

ROOT="assets"

show_help() {
cat << EOF
Tests Tracking capabilities.

Usage: ./test.sh -d directory

Params:
  -d  Directory containing the images/videos and
			one or more trackers to be run against.
			Defaults to 'assets/'

	-h	Shows this help message

Example:
  $ ./test.sh -d assets
EOF
}


#### CLI

while getopts ":d:h" opt; do
  case $opt in
    d)
      ROOT=$OPTARG
      ;;
    h)
      show_help
      exit 0
      ;;
    \?)
      show_help >&2
      echo "Invalid argument: $OPTARG" &2
      exit 1
      ;;
  esac
done

shift $((OPTIND-1))


#### Main

if [ "${ROOT: -1}" == "/" ]; then
	ROOT=${ROOT::-1}
fi

echo "Root dir for tests: $ROOT"
echo ""

for directory in $ROOT/*/; do
	echo $directory
	# ./track -d $directory -c $directory/classifier.xml & pidlist="$pidlist $!"
done

# FAIL=0
# for job in $pidlist; do
# 	wait $job || let "FAIL += 1"
# done

# if [ "$FAIL" -eq 0 ]; then
#   echo "SUCCESS!"
# else
#   echo "Failed Tests: ($FAIL)"
# fi

