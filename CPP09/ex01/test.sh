#!/bin/bash

# Colors for better output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Counter for tests
PASSED=0
FAILED=0
TOTAL=0

# Function to run a test and check if the output matches the expected result
run_test() {
    local test_name="$1"
    local input="$2"
    local expected="$3"
    local expected_exit_code="$4"
    
    ((TOTAL++))
    echo -e "${YELLOW}Test $TOTAL: $test_name${NC}"
    echo "Input: $input"
    echo "Expected: $expected"
    
    # Run the RPN program with the input
    result=$(./RPN "$input" 2>&1)
    exit_code=$?
    
    echo "Got: $result"
    
    # Check if the exit code matches expected (if specified)
    if [ -n "$expected_exit_code" ] && [ $exit_code -ne $expected_exit_code ]; then
        echo -e "${RED}✘ Test failed! Exit code mismatch: Expected $expected_exit_code, got $exit_code${NC}"
        ((FAILED++))
        return
    fi
    
    # Check if the output matches expected
    if [[ "$result" == "$expected" ]]; then
        echo -e "${GREEN}✓ Test passed!${NC}"
        ((PASSED++))
    else
        echo -e "${RED}✘ Test failed!${NC}"
        ((FAILED++))
    fi
    echo "-----------------------"
}

# Build the project if necessary
if [ ! -f "RPN" ]; then
    echo "Building RPN program..."
    make
fi

# Basic valid tests
run_test "Basic addition" "3 4 +" "Result: 7" 0
run_test "Basic subtraction" "5 2 -" "Result: 3" 0
run_test "Basic multiplication" "3 4 *" "Result: 12" 0
run_test "Basic division" "6 2 /" "Result: 3" 0
run_test "Multiple operations 1" "3 4 + 2 *" "Result: 14" 0
run_test "Multiple operations 2" "3 4 2 + *" "Result: 18" 0
run_test "Examples from subject" "8 9 * 9 - 9 - 9 - 4 - 1 +" "Result: 42" 0
run_test "Examples from subject" "7 7 * 7 -" "Result: 42" 0
run_test "Examples from subject" "1 2 * 2 / 2 * 2 4 - +" "Result: 0" 0

# Error cases
run_test "Invalid character" "3 a +" "Error: invalid token 'a'" 0
run_test "Division by zero" "5 0 /" "Error: Division by zero" 0
run_test "Insufficient operands" "+" "Error: insufficient operands" 0
run_test "Too many operands" "3 4 5 +" "Error: Invalid RPN expression (too few operators or operands)" 0
run_test "Invalid RPN (single number)" "3" "Error: Missing operator in expression" 0
run_test "Invalid RPN (parentheses)" "(1 + 1)" "Error: invalid token '(1'" 0
run_test "Empty input" "" "Error: Empty or invalid expression" 0

# Edge cases
run_test "Negative numbers" "5 -3 +" "Result: 2" 0
run_test "Large numbers" "1000 1000 *" "Result: 1000000" 0
run_test "Zero result" "5 5 -" "Result: 0" 0
run_test "Multiple spaces" "3   4    +" "Result: 7" 0

# Print summary
echo "===== TEST SUMMARY ====="
echo -e "PASSED: ${GREEN}$PASSED${NC}"
echo -e "FAILED: ${RED}$FAILED${NC}"
echo -e "TOTAL: $TOTAL"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi