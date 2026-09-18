#!/bin/bash
# regression tests for RPN (cpp09 ex01)
set -u
cd "$(dirname "$0")/.."

make re > /dev/null || { echo "BUILD FAILED"; exit 1; }

pass=0
fail=0

check_ok() {
	local name="$1"
	local expr="$2"
	local expected="$3"
	local actual
	actual=$(./RPN "$expr" 2>&1)
	local rc=$?

	if [ "$rc" -eq 0 ] && [ "$actual" = "$expected" ]; then
		echo "PASS: $name"
		pass=$((pass + 1))
	else
		echo "FAIL: $name (got '$actual', rc=$rc, expected '$expected', rc=0)"
		fail=$((fail + 1))
	fi
}

check_err() {
	local name="$1"
	shift
	local actual
	actual=$("$@" 2>&1)
	local rc=$?

	if [ "$rc" -ne 0 ] && [ "$actual" = "Error" ]; then
		echo "PASS: $name"
		pass=$((pass + 1))
	else
		echo "FAIL: $name (got '$actual', rc=$rc, expected 'Error', rc!=0)"
		fail=$((fail + 1))
	fi
}

check_ok "subject example 1" "8 9 * 9 - 9 - 9 - 4 - 1 +" "42"
check_ok "subject example 2" "7 7 * 7 -" "42"
check_ok "subject example 3" "1 2 * 2 / 2 * 2 4 - +" "0"
check_ok "simple addition" "3 4 +" "7"
check_ok "single value" "5" "5"
check_ok "negative intermediate result" "3 4 + 5 -" "2"
check_ok "chained additions" "1 1 1 + +" "3"

check_err "too few operands" ./RPN "1 2"
check_err "division by zero" ./RPN "5 0 /"
check_err "invalid characters" ./RPN "(1 + 1)"
check_err "multi-digit operand rejected" ./RPN "10 2 +"
check_err "empty expression" ./RPN ""
check_err "no argument" ./RPN
check_err "too many arguments" ./RPN "1 2 +" "extra"

echo "----"
echo "passed: $pass, failed: $fail"
[ "$fail" -eq 0 ]
