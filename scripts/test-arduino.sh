#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
. "$SCRIPT_DIR/common.sh"

usage() {
    printf '%s\n' "Usage: $0 [--fqbn <board>] [--foundation <source-directory>] [--cpstl <source-directory>]"
    printf '%s\n' "Foundation defaults to MCC_FOUNDATION_SOURCE or the sibling ../Foundation."
    printf '%s\n' "CPSTL defaults to MCC_CPSTL_SOURCE or the sibling ../CPSTL."
}

# The validated Arduino source-mode board. Other cores are not validated here.
FQBN=arduino:avr:uno
FOUNDATION=${MCC_FOUNDATION_SOURCE:-$MCC_ROOT/../Foundation}
CPSTL=${MCC_CPSTL_SOURCE:-$MCC_ROOT/../CPSTL}

while [ "$#" -gt 0 ]; do
    case "$1" in
        --fqbn)
            mcc_require_value "$1" "${2:-}"
            FQBN=$2
            shift 2
            ;;
        --foundation)
            mcc_require_value "$1" "${2:-}"
            FOUNDATION=$2
            shift 2
            ;;
        --cpstl)
            mcc_require_value "$1" "${2:-}"
            CPSTL=$2
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            mcc_die "unknown argument: $1"
            ;;
    esac
done

command -v arduino-cli >/dev/null 2>&1 || mcc_die "arduino-cli not found"
[ -f "$FOUNDATION/library.properties" ] || \
    mcc_die "Foundation Arduino library not found at $FOUNDATION"
FOUNDATION=$(mcc_absolute_path "$FOUNDATION")
[ -f "$CPSTL/library.properties" ] || \
    mcc_die "CPSTL Arduino library not found at $CPSTL"
CPSTL=$(mcc_absolute_path "$CPSTL")

BUILD_ROOT="$MCC_ROOT/build/arduino/$(printf '%s' "$FQBN" | tr ':' '_')"
rm -rf "$BUILD_ROOT"

# Compile each sketch against the repository and Foundation as libraries,
# exactly as an Arduino user who installed both would.
COUNT=0
for SKETCH in "$MCC_ROOT"/examples/MCC/*/*/*.ino; do
    SKETCH_DIR=$(dirname -- "$SKETCH")
    NAME=${SKETCH_DIR#"$MCC_ROOT/examples/MCC/"}
    LOG="$BUILD_ROOT/$NAME.log"
    mkdir -p -- "$(dirname -- "$LOG")"
    printf '%s\n' "== $NAME ($FQBN)"

    STATUS=0
    arduino-cli compile \
        --fqbn "$FQBN" \
        --library "$MCC_ROOT" \
        --library "$FOUNDATION" \
        --library "$CPSTL" \
        --build-path "$BUILD_ROOT/$NAME" \
        --warnings default \
        "$SKETCH_DIR" >"$LOG" 2>&1 || STATUS=$?
    cat -- "$LOG"
    [ "$STATUS" -eq 0 ] || mcc_die "$NAME failed to compile"

    # The stock AVR core passes -fpermissive, which demotes real type errors
    # to warnings; any warning in MCC or its examples fails the gate.
    if grep -F "$MCC_ROOT/" "$LOG" | grep -q "warning:"; then
        mcc_die "$NAME compiled with MCC warnings"
    fi
    COUNT=$((COUNT + 1))
done

[ "$COUNT" -gt 0 ] || mcc_die "no Arduino sketches found"
printf '%s\n' "All $COUNT Arduino sketches compiled for $FQBN."
