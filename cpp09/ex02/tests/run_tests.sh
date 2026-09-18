#!/bin/bash
# regression + fuzz tests for PmergeMe (cpp09 ex02)
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
		echo "  actual:   $actual"
		echo "  expected: $expected"
		fail=$((fail + 1))
	fi
}

get_after() {
	./PmergeMe "$@" 2>&1 | sed -n 's/^After: //p'
}

# hand-verified small cases
check "subject-style example" "$(get_after 3 5 9 7 4)" "3 4 5 7 9"
check "single element" "$(get_after 1)" "1"
check "two elements, reversed" "$(get_after 2 1)" "1 2"
check "three elements" "$(get_after 5 1 3)" "1 3 5"
check "all duplicates" "$(get_after 5 5 5 5)" "5 5 5 5"
check "already sorted" "$(get_after 1 2 3 4 5 6 7)" "1 2 3 4 5 6 7"
check "reverse sorted" "$(get_after 9 8 7 6 5 4 3 2 1)" "1 2 3 4 5 6 7 8 9"
check "quoted whitespace-separated string" "$(get_after "3 5 9 7 4")" "3 4 5 7 9"

# error cases
actual=$(./PmergeMe -3 4 2>&1); rc=$?
[ "$rc" -ne 0 ] && [[ "$actual" == Error* ]] && { echo "PASS: negative number rejected"; pass=$((pass+1)); } || { echo "FAIL: negative number rejected ($actual)"; fail=$((fail+1)); }

actual=$(./PmergeMe abc 2>&1); rc=$?
[ "$rc" -ne 0 ] && [[ "$actual" == Error* ]] && { echo "PASS: non-numeric rejected"; pass=$((pass+1)); } || { echo "FAIL: non-numeric rejected ($actual)"; fail=$((fail+1)); }

actual=$(./PmergeMe 2>&1); rc=$?
[ "$rc" -ne 0 ] && [[ "$actual" == Error* ]] && { echo "PASS: no arguments rejected"; pass=$((pass+1)); } || { echo "FAIL: no arguments rejected ($actual)"; fail=$((fail+1)); }

# fuzz: many random sizes, compare against `sort -n` as ground truth,
# and cross-check that the vector-backed and deque-backed sorts agree
fuzz_fail=0
for trial in $(seq 1 40); do
	size=$((RANDOM % 300 + 1))
	numbers=()
	for ((i = 0; i < size; i++)); do
		numbers+=("$((RANDOM % 10000 + 1))")
	done

	expected=$(printf '%s\n' "${numbers[@]}" | sort -n | tr '\n' ' ' | sed 's/ $//')
	actual=$(./PmergeMe "${numbers[@]}" | sed -n 's/^After: //p')

	if [ "$actual" != "$expected" ]; then
		echo "FAIL: fuzz trial $trial (size=$size)"
		echo "  input:    ${numbers[*]}"
		echo "  actual:   $actual"
		echo "  expected: $expected"
		fuzz_fail=$((fuzz_fail + 1))
	fi
done

if [ "$fuzz_fail" -eq 0 ]; then
	echo "PASS: fuzz (40 random trials, sizes 1-300)"
	pass=$((pass + 1))
else
	echo "FAIL: fuzz ($fuzz_fail/40 trials failed)"
	fail=$((fail + 1))
fi

# large input: must complete quickly and match `sort -n`
big=()
for ((i = 0; i < 3000; i++)); do
	big+=("$((RANDOM % 1000000 + 1))")
done
expected_big=$(printf '%s\n' "${big[@]}" | sort -n | tr '\n' ' ' | sed 's/ $//')
start=$(date +%s%N)
actual_big=$(./PmergeMe "${big[@]}" | sed -n 's/^After: //p')
end=$(date +%s%N)
elapsed_ms=$(( (end - start) / 1000000 ))
check "large input (3000 elements) sorted correctly" "$actual_big" "$expected_big"
echo "  large input wall time: ${elapsed_ms} ms"

echo "----"
echo "passed: $pass, failed: $fail"
[ "$fail" -eq 0 ]
