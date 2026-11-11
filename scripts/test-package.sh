#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
. "$SCRIPT_DIR/common.sh"

usage() {
    printf '%s\n' "Usage: $0 <preset> [--parallel <jobs>] [--fresh]"
}

PRESET=""
PARALLEL=""
FRESH=0

while [ "$#" -gt 0 ]; do
    case "$1" in
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

set -- "$SCRIPT_DIR/export.sh" "$PRESET"
[ "$FRESH" -eq 0 ] || set -- "$@" --fresh
[ -z "$PARALLEL" ] || set -- "$@" --parallel "$PARALLEL"
"$@"

MCC_PREFIX="$MCC_DIST_ROOT/$PRESET"
CONSUMER_SOURCE="$MCC_ROOT/tests/PackageConsumer"
CONSUMER_BUILD="$MCC_BUILD_ROOT/package-consumer/$PRESET"

MCC_CACHE="$(mcc_build_dir "$PRESET")/CMakeCache.txt"

mcc_cache_value() {
    sed -n "s/^$1:[^=]*=//p" "$MCC_CACHE" | sed -n '1p'
}

GENERATOR=$(mcc_cache_value CMAKE_GENERATOR)
GENERATOR_PLATFORM=$(mcc_cache_value CMAKE_GENERATOR_PLATFORM)
CXX_COMPILER=$(mcc_cache_value CMAKE_CXX_COMPILER)
TOOLCHAIN_FILE=$(mcc_cache_value CMAKE_TOOLCHAIN_FILE)
OSX_ARCHITECTURES=$(mcc_cache_value CMAKE_OSX_ARCHITECTURES)
CROSSCOMPILING=$(mcc_cache_value CMAKE_CROSSCOMPILING)

[ "$CROSSCOMPILING" != "TRUE" ] || \
    mcc_die "package execution requires a native preset"
[ -n "$GENERATOR" ] || mcc_die "configured preset has no CMake generator"

# The package consumer must use the same ABI and compiler family as the
# package. Recreate it so a previous run cannot retain another generator.
cmake -E remove_directory "$CONSUMER_BUILD"

set -- cmake \
    -S "$CONSUMER_SOURCE" \
    -B "$CONSUMER_BUILD" \
    -G "$GENERATOR" \
    -DMCC_DIR="$MCC_PREFIX/lib/cmake/MCC" \
    -DCMAKE_PREFIX_PATH="$MCC_PREFIX"

[ -z "$GENERATOR_PLATFORM" ] || set -- "$@" -A "$GENERATOR_PLATFORM"
[ -z "$OSX_ARCHITECTURES" ] || \
    set -- "$@" "-DCMAKE_OSX_ARCHITECTURES=$OSX_ARCHITECTURES"

if [ -n "$TOOLCHAIN_FILE" ]; then
    set -- "$@" "-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE"
else
    case "$GENERATOR" in
        "Visual Studio"*|Xcode)
            ;;
        *)
            [ -z "$CXX_COMPILER" ] || \
                set -- "$@" "-DCMAKE_CXX_COMPILER=$CXX_COMPILER"
            ;;
    esac
fi

"$@"

set -- cmake --build "$CONSUMER_BUILD" --config Release
[ -z "$PARALLEL" ] || set -- "$@" --parallel "$PARALLEL"
"$@"

set -- ctest --test-dir "$CONSUMER_BUILD" --output-on-failure \
    --no-tests=error --build-config Release
[ -z "$PARALLEL" ] || set -- "$@" --parallel "$PARALLEL"
"$@"

printf '%s\n' "Verified installed MCC package and transitive Foundation dependency"
