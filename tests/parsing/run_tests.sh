#!/bin/bash

echo "=== INVALID TESTS ==="
for f in tests/invalid/*.rt; do
    echo "Running $f"
    ./a.out $f
    echo "------------------"
done

echo "=== VALID TESTS ==="
for f in tests/valid/*.rt; do
    echo "Running $f"
    ./a.out $f
    echo "-------------------"
done