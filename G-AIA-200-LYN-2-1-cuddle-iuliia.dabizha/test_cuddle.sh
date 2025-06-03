#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test files
TEST_FILES=("test_files/testdata.csv" "test_files/numbers.csv" "test_files/measurements.csv" "test_files/users.csv" "test_files/survey.csv")

# Output files to clean up
OUTPUT_FILES=("head.csv" "tail.csv" "filtered.csv" "sorted.csv" "custom_separator.csv")
TEMP_FILES=("test_files/semicolon_data.csv" "test_files/tab_data.csv" "test_files/types_test.csv" "test_tab.sh")

# Function to clean up temporary and output files
cleanup() {
    echo -e "${YELLOW}Cleaning up output and temporary files...${NC}"
    
    # Remove output files
    for file in "${OUTPUT_FILES[@]}"; do
        if [ -f "$file" ]; then
            rm -f "$file"
            echo -e "Removed $file"
        fi
    done
    
    # Remove temporary files
    for file in "${TEMP_FILES[@]}"; do
        if [ -f "$file" ]; then
            rm -f "$file"
            echo -e "Removed $file"
        fi
    done
    
    echo -e "${GREEN}Cleanup complete!${NC}"
}

# Print test header
print_header() {
    echo -e "\n${BLUE}====== Testing: $1 ======${NC}"
}

# Run a test and check result
run_test() {
    local command=$1
    local file=$2
    local description=$3
    local extra_args=$4
    
    echo -e "${YELLOW}Testing ${command} on ${file}:${NC} ${description}"
    if [[ -z "$extra_args" ]]; then
        if ./cuddle ${command} ${file}; then
            echo -e "${GREEN}✓ Success!${NC}\n"
            return 0
        else
            echo -e "${RED}✗ Failed!${NC}\n"
            return 1
        fi
    else
        if ./cuddle ${command} ${file} ${extra_args}; then
            echo -e "${GREEN}✓ Success!${NC}\n"
            return 0
        else
            echo -e "${RED}✗ Failed!${NC}\n"
            return 1
        fi
    fi
}

# Create a semicolon-separated test file
create_semicolon_file() {
    cat > test_files/semicolon_data.csv << EOF
name;age;city
Alice;25;Paris
Bob;30;London
Charlie;35;Berlin
David;40;Madrid
Eve;45;Rome
EOF
    echo -e "${GREEN}Created semicolon-separated test file: test_files/semicolon_data.csv${NC}"
}

# Create a tab-separated test file
create_tab_file() {
    cat > test_files/tab_data.csv << EOF
name	age	city
Alice	25	Paris
Bob	30	London
Charlie	35	Berlin
David	40	Madrid
Eve	45	Rome
EOF
    echo -e "${GREEN}Created tab-separated test file: test_files/tab_data.csv${NC}"
}

# Ensure we have the program
if [ ! -x "./cuddle" ]; then
    echo -e "${RED}Error: cuddle executable not found${NC}"
    echo "Running make to build it..."
    make re
fi

# Run cleanup before tests to remove leftover files from previous runs
cleanup

# Create test files with different separators
create_semicolon_file
create_tab_file

# Header of the test
echo -e "${BLUE}=======================================${NC}"
echo -e "${BLUE}       CUDDLE TEST SUITE              ${NC}"
echo -e "${BLUE}=======================================${NC}"

# Test shape command
print_header "SHAPE"
for file in "${TEST_FILES[@]}"; do
    run_test "shape" "$file" "should display dimensions"
done

# Test info command
print_header "INFO"
for file in "${TEST_FILES[@]}"; do
    run_test "info" "$file" "should display column information"
done

# Test head command
print_header "HEAD"
for file in "${TEST_FILES[@]}"; do
    run_test "head" "$file" "should display first 3 rows and save to head.csv"
    if [ -f "head.csv" ]; then
        echo -e "${YELLOW}Contents of head.csv:${NC}"
        cat head.csv
        echo ""
    fi
done

# Test tail command
print_header "TAIL"
for file in "${TEST_FILES[@]}"; do
    run_test "tail" "$file" "should display last 3 rows and save to tail.csv"
    if [ -f "tail.csv" ]; then
        echo -e "${YELLOW}Contents of tail.csv:${NC}"
        cat tail.csv
        echo ""
    fi
done

# Test describe command
print_header "DESCRIBE"
for file in "${TEST_FILES[@]}"; do
    run_test "describe" "$file" "should display statistics for numeric columns"
done

# Test filter command
print_header "FILTER"
run_test "filter" "test_files/testdata.csv" "should filter rows with age > 50"
if [ -f "filtered.csv" ]; then
    echo -e "${YELLOW}Contents of filtered.csv:${NC}"
    cat filtered.csv
    echo ""
fi

# Test sort command
print_header "SORT"
run_test "sort" "test_files/testdata.csv" "should sort rows by age"
if [ -f "sorted.csv" ]; then
    echo -e "${YELLOW}Contents of sorted.csv:${NC}"
    cat sorted.csv
    echo ""
fi

# Test get_value command
print_header "VALUE"
run_test "value" "test_files/testdata.csv" "should display specific values"

# Test get_unique_values command
print_header "UNIQUE"
run_test "unique" "test_files/testdata.csv" "should display unique values in city column"

# Test custom separators
print_header "CUSTOM SEPARATORS"
echo -e "${YELLOW}Testing with semicolon separator:${NC}"
echo -e "./cuddle custom test_files/semicolon_data.csv ';'"
./cuddle custom test_files/semicolon_data.csv ';'
echo ""
if [ -f "custom_separator.csv" ]; then
    echo -e "${YELLOW}Contents of custom_separator.csv (from semicolon file):${NC}"
    cat custom_separator.csv
    echo ""
fi

echo -e "${YELLOW}Testing with tab separator:${NC}"
echo -e "Creating temp command file for tab character..."
echo '#!/bin/bash' > test_tab.sh
echo './cuddle custom test_files/tab_data.csv "	"' >> test_tab.sh
chmod +x test_tab.sh
./test_tab.sh
rm -f test_tab.sh
echo ""
if [ -f "custom_separator.csv" ]; then
    echo -e "${YELLOW}Contents of custom_separator.csv (from tab file):${NC}"
    cat custom_separator.csv
    echo ""
fi

# Test different data types
print_header "DATA TYPES"
cat > test_files/types_test.csv << EOF
int_value,float_value,string_value,unsigned_value,bool_value
-42,3.14159,"Hello, World!",100,true
-10,2.71828,"Testing",200,false
-25,1.61803,"Types",150,true
EOF

echo -e "${YELLOW}Testing custom data types:${NC}"
./cuddle custom-dtypes test_files/types_test.csv
echo ""

# Summary
echo -e "${BLUE}=======================================${NC}"
echo -e "${BLUE}       TEST SUITE COMPLETED           ${NC}"
echo -e "${BLUE}=======================================${NC}"

# Ask user if they want to keep the output files
echo -e "${YELLOW}Would you like to keep the output files? (y/n)${NC}"
read -p "" keep_files

if [[ "$keep_files" == "y" || "$keep_files" == "Y" ]]; then
    echo -e "${GREEN}Output files have been preserved.${NC}"
    echo -e "${YELLOW}The following files were created:${NC}"
    for file in "${OUTPUT_FILES[@]}"; do
        if [ -f "$file" ]; then
            echo "- $file"
        fi
    done
else
    # Clean up after tests are complete
    cleanup
fi