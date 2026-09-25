#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
. "$SCRIPT_DIR/common.sh"

usage() {
    printf '%s\n' "Usage: $0 <preset> [--foundation-prefix <path>] [--parallel <jobs>] [--fresh]"
}

PRESET=""
FOUNDATION_PREFIX=""
PARALLEL=""
FRESH=0

while [ "$#" -gt 0 ]; do
    case "$1" in
        --foundation-prefix)
            mcc_require_value "$1" "${2:-}"
            FOUNDATION_PREFIX=$2
            shift 2
            ;;
        --parallel)
            mcc_require_value "$1" "${2:-}"
            PARALLEL=$2
            shift 2
            ;;
        --fresh)
            FRESH=1
            shift
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        -*)
            mcc_die "unknown option: $1"
            ;;
        *)
            [ -z "$PRESET" ] || mcc_die "only one preset may be specified"
            PRESET=$1
            shift
            ;;
    esac
done

mcc_require_preset "$PRESET"
case "$PRESET" in
    macos_*|linux_*|windows_*)
        ;;
    *)
        mcc_die "package consumer tests require a runnable desktop preset"
        ;;
esac

if [ -z "$FOUNDATION_PREFIX" ]; then
    FOUNDATION_PREFIX=${MCC_FOUNDATION_PREFIX:-"$MCC_ROOT/../Foundation/dist/$PRESET"}
fi
FOUNDATION_PREFIX=$(mcc_absolute_path "$FOUNDATION_PREFIX")
FOUNDATION_CONFIG="$FOUNDATION_PREFIX/lib/cmake/Foundation/FoundationConfig.cmake"
[ -f "$FOUNDATION_CONFIG" ] || \
    mcc_die "Foundation package not found at $FOUNDATION_PREFIX"

set -- "$SCRIPT_DIR/export.sh" "$PRESET"
[ "$FRESH" -eq 0 ] || set -- "$@" --fresh
[ -z "$PARALLEL" ] || set -- "$@" --parallel "$PARALLEL"
set -- "$@" -- -DMCC_FOUNDATION_PREFIX="$FOUNDATION_PREFIX"
"$@"

MCC_PREFIX="$MCC_DIST_ROOT/$PRESET"
CONSUMER_SOURCE="$MCC_ROOT/tests/PackageConsumer"
CONSUMER_BUILD="$MCC_BUILD_ROOT/package-consumer/$PRESET"

if [ "$FRESH" -eq 1 ]; then
    cmake -E remove_directory "$CONSUMER_BUILD"
fi

cmake \
    -S "$CONSUMER_SOURCE" \
    -B "$CONSUMER_BUILD" \
    -DCMAKE_BUILD_TYPE=Release \
    -DMCC_DIR="$MCC_PREFIX/lib/cmake/MCC" \
    -DFoundation_DIR="$FOUNDATION_PREFIX/lib/cmake/Foundation"

set -- cmake --build "$CONSUMER_BUILD" --config Release
[ -z "$PARALLEL" ] || set -- "$@" --parallel "$PARALLEL"
"$@"

set -- ctest --test-dir "$CONSUMER_BUILD" --output-on-failure \
    --no-tests=error --build-config Release
[ -z "$PARALLEL" ] || set -- "$@" --parallel "$PARALLEL"
"$@"

printf '%s\n' "Verified installed MCC package and transitive Foundation dependency"
