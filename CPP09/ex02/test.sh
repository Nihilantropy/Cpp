#!/bin/bash

# Colors for better output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counter for tests
PASSED=0
FAILED=0
TOTAL=0

# Function to run a test and check if the output contains expected patterns
run_test() {
    local test_name="$1"
    local input="$2"
    local expected_pattern="$3"
    local should_fail="$4"  # Optional, if "true" then the program should fail
    
    ((TOTAL++))
    echo -e "${YELLOW}Test $TOTAL: $test_name${NC}"
    echo -e "${BLUE}Input:${NC} $input"
    
    # Run the PmergeMe program with the input
    result=$(./PmergeMe $input 2>&1)
    exit_code=$?
    
    # Print summarized output (first few lines if it's too long)
    echo -e "${BLUE}Output (summary):${NC}"
    echo "$result" | head -n 5
    if [ $(echo "$result" | wc -l) -gt 5 ]; then
        echo "..."
    fi
    
    # Check if the test should fail or succeed
    if [ "$should_fail" = "true" ]; then
        # Program should fail with error
        if [ $exit_code -ne 0 ] || [[ "$result" == *"Error"* ]]; then
            echo -e "${GREEN}✓ Test passed! Program correctly failed with error${NC}"
            ((PASSED++))
        else
            echo -e "${RED}✘ Test failed! Program should have failed but didn't${NC}"
            ((FAILED++))
        fi
    else
        # Program should succeed and output should match pattern
        if [ $exit_code -eq 0 ] && [[ "$result" == *"$expected_pattern"* ]]; then
            echo -e "${GREEN}✓ Test passed!${NC}"
            ((PASSED++))
        else
            echo -e "${RED}✘ Test failed! Output doesn't match expected pattern${NC}"
            echo -e "${BLUE}Expected to contain:${NC} $expected_pattern"
            ((FAILED++))
        fi
    fi
    echo "-----------------------"
}

# Function to generate a sequence of numbers
generate_sequence() {
    local count="$1"
    local type="$2"  # "random", "sorted", "reverse"
    
    if [ "$type" = "random" ]; then
        # Generate random numbers between 1 and 10000
        seq 1 $count | sort -R | tr '\n' ' '
    elif [ "$type" = "sorted" ]; then
        # Generate sorted numbers
        seq 1 $count | tr '\n' ' '
    elif [ "$type" = "reverse" ]; then
        # Generate reverse sorted numbers
        seq $count -1 1 | tr '\n' ' '
    fi
}

# Build the project if necessary
if [ ! -f "PmergeMe" ]; then
    echo "Building PmergeMe program..."
    make
fi

echo "===== TESTING PMERGE-ME ====="

# Basic functionality tests
run_test "Basic sorting" "5 3 7 1 8 6 2 4" "After: 1 2 3 4 5 6 7 8"
run_test "Already sorted" "1 2 3 4 5" "After: 1 2 3 4 5"
run_test "Reverse sorted" "5 4 3 2 1" "After: 1 2 3 4 5"
run_test "Duplicate numbers" "5 3 3 7" "Error" "true"
run_test "Single number" "42" "Error" "true"

# Error handling tests
run_test "Negative number" "5 3 -7 1 8" "Error" "true"
run_test "Non-numeric input" "5 3 abc 1 8" "Error" "true"
run_test "Very large number" "5 3 2147483648 1 8" "Error" "true"
run_test "Empty input" "" "Error" "true"

# Performance tests with different sizes
echo -e "${BLUE}Running performance tests with different sequence sizes...${NC}"

# Small sequence (10 numbers)
sequence=$(generate_sequence 10 "random")
run_test "Small sequence (10 numbers)" "$sequence" "Time to process"

# Medium sequence (100 numbers)
sequence=$(generate_sequence 100 "random")
run_test "Medium sequence (100 numbers)" "$sequence" "Time to process"

# Large sequence (1000 numbers)
sequence=$(generate_sequence 1000 "random")
run_test "Large sequence (1000 numbers)" "$sequence" "Time to process"

# Edge cases with sequence types
echo -e "${BLUE}Testing different sequence patterns...${NC}"

# Sorted sequence (100 numbers)
sequence=$(generate_sequence 100 "sorted")
run_test "Sorted sequence (100 numbers)" "$sequence" "Time to process"

# Reverse sorted sequence (100 numbers)
sequence=$(generate_sequence 100 "reverse")
run_test "Reverse sorted sequence (100 numbers)" "$sequence" "Time to process"

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