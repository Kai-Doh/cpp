#!/bin/bash
# regression tests for BitcoinExchange (cpp09 ex00)
set -u
cd "$(dirname "$0")/.."

make re > /dev/null || { echo "BUILD FAILED"; exit 1; }

pass=0
fail=0

check() {
	local name="$1"
	local actual="$2"
	local expected="$3"

	if [ "$actual" = "$expected" ]; then
		echo "PASS: $name"
		pass=$((pass + 1))
	else
		echo "FAIL: $name"
		diff <(echo "$actual") <(echo "$expected")
		fail=$((fail + 1))
	fi
}

# main regression case: exact match, closest-earlier lookup, leap years,
# out-of-range dates, bad values, missing pipe
actual=$(./btc tests/input1.txt)
expected=$(cat tests/expected1.txt)
check "input1 full run" "$actual" "$expected"

# wrong number of arguments
actual=$(./btc 2>&1)
check "no argument" "$actual" "Error: could not open file."

# nonexistent input file
actual=$(./btc tests/does_not_exist.txt 2>&1)
check "nonexistent input file" "$actual" "Error: could not open file."

echo "----"
echo "passed: $pass, failed: $fail"
[ "$fail" -eq 0 ]
