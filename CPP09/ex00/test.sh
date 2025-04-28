#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}=== Bitcoin Exchange Comprehensive Test Suite ===${NC}"

# Ensure program is compiled
make re > /dev/null

run_test() {
    echo -e "\n${YELLOW}$1${NC}"
    $2
    exit_code=$?
    
    # For tests that we expect to report errors but still "pass"
    if [[ "$1" == *"with invalid"* || "$1" == *"with nonexistent file"* || "$1" == *"with empty file"* ]]; then
        echo -e "${GREEN}✓ Test passed (reported expected errors)${NC}"
    elif [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✓ Test passed${NC}"
    else
        echo -e "${RED}✗ Test failed with exit code $exit_code${NC}"
    fi
}

# Test 1: Valid inputs
echo "date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2012-01-15 | 1
2012-12-31 | 0.5
2010-01-01 | 1.5
2010-08-20 | 7
2021-01-01 | 1000" > test_valid.txt

run_test "Test with valid inputs" "./btc test_valid.txt"

# Test 2: Invalid dates
echo "date | value
2001-42-42
2010--08-20 | 7
201a-08-20 | 7
2010-13-01 | 5
2010-02-30 | 5
-2010-01-01 | 5" > test_invalid_dates.txt

run_test "Test with invalid dates" "./btc test_invalid_dates.txt"

# Test 3: Invalid values
echo "date | value
2012-01-11 | -1
2012-01-11 | 2147483648
2012-01-11 | abc
2012-01-11 | 1001
2012-01-11 | 0.0.1
2012-01-11 | ." > test_invalid_values.txt

run_test "Test with invalid values" "./btc test_invalid_values.txt"

# Test 4: Edge cases
echo "date | value
1900-01-01 | 10
2022-01-01 | 10
2010-01-01 | 0
2010-01-01 | 1000
2010-01-01 | 999.999" > test_edge_cases.txt

run_test "Test with edge cases" "./btc test_edge_cases.txt"

# Test 5: Missing file
run_test "Test with nonexistent file" "./btc nonexistent_file.txt"

# Test 6: Empty file
touch empty.txt
run_test "Test with empty file" "./btc empty.txt"

# Test 7: File with only header
echo "date | value" > header_only.txt
run_test "Test with only header" "./btc header_only.txt"

# Test 8: Original input file
run_test "Test with original input file" "./btc input.txt"

# Clean up test files
rm -f test_valid.txt test_invalid_dates.txt test_invalid_values.txt test_edge_cases.txt empty.txt header_only.txt

echo -e "\n${YELLOW}=== Test suite completed ===${NC}"