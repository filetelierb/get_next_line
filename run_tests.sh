#!/usr/bin/env bash
# Quick helper to build and run the test driver for get_next_line.
# Usage: BUFFER_SIZE=42 ./run_tests.sh

set -euo pipefail

CC="cc"
CFLAGS="-Wall -Wextra -Werror"
SRC="get_next_line.c get_next_line_utils.c test.c"
BIN="gnl_test"
SAMPLE="sample_input.txt"

# Recreate a small sample file on each run so you can tweak easily.
cat > "$SAMPLE" <<'EOF'
First line\n
Second line is longer than the buffer size to force multiple reads.
Third line (no trailing newline at EOF)
EOF

echo "[1/2] Building $BIN..."
if [[ -n "${BUFFER_SIZE-}" ]]; then
  echo "  BUFFER_SIZE=${BUFFER_SIZE}"
  $CC $CFLAGS -DBUFFER_SIZE=${BUFFER_SIZE} $SRC -o "$BIN"
else
  $CC $CFLAGS $SRC -o "$BIN"
fi

echo "[2/2] Running $BIN against $SAMPLE"
./"$BIN" "$SAMPLE"

echo "Done. You can also run ./gnl_test < file or ./gnl_test file1 file2 ..."