#!/bin/bash

targetfile=fastmult.cpp
cppfile=fastmult.cpp
maxtime=8

if [ ! -f "$targetfile" ]; then
    echo "Error: file $targetfile not found"
    echo "Final score: score - penalties = 0 - 0 = 0"
    exit 1
fi

# Compiling
results=$(g++ -O3 -std=c++17 -Wall -Werror -pedantic-errors -fmessage-length=0 $targetfile -o fastmult)
if [ $? -ne 0 ]; then
    echo "$results"
    echo "Final score: score - penalties = 0 - 0 = 0"
    exit 1
fi

num_tests=0
num_right=0

run_test() {
    ((num_tests++))
    args="$1"
    expected="$2"
    output=$(./fastmult $args)
    if [ "$output" = "$expected" ]; then
        ((num_right++))
        echo "Test $num_tests passed"
    else
        echo "Test $num_tests failed"
        echo "Expected: $expected"
        echo "Got: $output"
    fi
}

# Tests
run_test "2 3" "6"
run_test "12 34" "408"
run_test "123 456" "56088"
run_test "1234 5678" "7006652"
run_test "9999 9999" "99980001"
run_test "123456789 987654321" "121932631112635269"
run_test "123456789123456789 987654321987654321" "121932631356500531347203169112635269"

echo "Tests passed: $num_right / $num_tests"
