#!/bin/bash

# Arduino Multi-Sensor Platform Build Script
# This script handles compilation, upload, and testing

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Arduino Multi-Sensor Platform Build   ${NC}"
echo -e "${BLUE}========================================${NC}"

# Configuration
PROJECT_NAME="Arduino-Multi-Sensor-Platform"
BOARD="arduino:avr:uno"
PORT="/dev/ttyUSB0"
SKETCH_PATH="src/main/Arduino_Multi_Sensor.ino"
BUILD_DIR="build"
OUTPUT_DIR="output"

# Create directories
mkdir -p $BUILD_DIR
mkdir -p $OUTPUT_DIR

# Function to compile sketch
compile() {
    echo -e "${YELLOW}Compiling sketch...${NC}"
    
    if arduino-cli compile --fqbn $BOARD $SKETCH_PATH; then
        echo -e "${GREEN}✓ Compilation successful${NC}"
        return 0
    else
        echo -e "${RED}✗ Compilation failed${NC}"
        return 1
    fi
}

# Function to upload sketch
upload() {
    echo -e "${YELLOW}Uploading to Arduino...${NC}"
    
    if arduino-cli upload -p $PORT --fqbn $BOARD $SKETCH_PATH; then
        echo -e "${GREEN}✓ Upload successful${NC}"
        return 0
    else
        echo -e "${RED}✗ Upload failed${NC}"
        return 1
    fi
}

# Function to run tests
run_tests() {
    echo -e "${YELLOW}Running tests...${NC}"
    
    if python3 scripts/test_runner.py -p $PORT -f json -o $OUTPUT_DIR/test_results; then
        echo -e "${GREEN}✓ Tests passed${NC}"
        return 0
    else
        echo -e "${RED}✗ Tests failed${NC}"
        return 1
    fi
}

# Function to generate documentation
generate_docs() {
    echo -e "${YELLOW}Generating documentation...${NC}"
    
    if doxygen docs/Doxyfile 2>/dev/null; then
        echo -e "${GREEN}✓ Documentation generated${NC}"
        return 0
    else
        echo -e "${YELLOW}⚠ Documentation generation skipped (doxygen not installed)${NC}"
        return 0
    fi
}

# Function to create release package
create_release() {
    echo -e "${YELLOW}Creating release package...${NC}"
    
    RELEASE_NAME="${PROJECT_NAME}_$(date +%Y%m%d_%H%M%S)"
    RELEASE_DIR="$OUTPUT_DIR/$RELEASE_NAME"
    
    mkdir -p $RELEASE_DIR
    
    # Copy important files
    cp -r src $RELEASE_DIR/
    cp -r lib $RELEASE_DIR/
    cp -r examples $RELEASE_DIR/
    cp -r tools $RELEASE_DIR/
    cp -r docs $RELEASE_DIR/
    cp README.md $RELEASE_DIR/
    cp LICENSE $RELEASE_DIR/
    cp CHANGELOG.md $RELEASE_DIR/
    cp .gitignore $RELEASE_DIR/
    
    # Create archive
    cd $OUTPUT_DIR
    tar -czf "${RELEASE_NAME}.tar.gz" $RELEASE_NAME
    zip -r "${RELEASE_NAME}.zip" $RELEASE_NAME
    cd ..
    
    echo -e "${GREEN}✓ Release package created: $OUTPUT_DIR/${RELEASE_NAME}.tar.gz${NC}"
    echo -e "${GREEN}✓ Release package created: $OUTPUT_DIR/${RELEASE_NAME}.zip${NC}"
}

# Function to display usage
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo "Options:"
    echo "  -c, --compile    Only compile the sketch"
    echo "  -u, --upload     Upload to Arduino"
    echo "  -t, --test       Run tests"
    echo "  -d, --docs       Generate documentation"
    echo "  -r, --release    Create release package"
    echo "  -a, --all        Do everything (default)"
    echo "  -h, --help       Show this help"
}

# Parse arguments
ACTION="all"

while [[ $# -gt 0 ]]; do
    case $1 in
        -c|--compile) ACTION="compile"; shift ;;
        -u|--upload) ACTION="upload"; shift ;;
        -t|--test) ACTION="test"; shift ;;
        -d|--docs) ACTION="docs"; shift ;;
        -r|--release) ACTION="release"; shift ;;
        -a|--all) ACTION="all"; shift ;;
        -h|--help) usage; exit 0 ;;
        *) echo -e "${RED}Unknown option: $1${NC}"; usage; exit 1 ;;
    esac
done

# Execute action
case $ACTION in
    compile)
        compile
        ;;
    upload)
        compile && upload
        ;;
    test)
        run_tests
        ;;
    docs)
        generate_docs
        ;;
    release)
        compile && generate_docs && create_release
        ;;
    all)
        compile && upload && run_tests && generate_docs && create_release
        ;;
esac

echo -e "${BLUE}========================================${NC}"
echo -e "${GREEN}Build process completed!${NC}"
echo -e "${BLUE}========================================${NC}"
