#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
. "$SCRIPT_DIR/common.sh"

usage() {
    printf '%s\n' "Usage: $0 <preset> [--config <name>] [--parallel <jobs>] [--filter <regex>] [--fresh] [--allow-no-tests]"
}

PRESET=""
CONFIGURATION=""
PARALLEL=""
FILTER=""
FRESH=0
ALLOW_NO_TESTS=0

while [ "$#" -gt 0 ]; do
    case "$1" in
        --config)
            mcc_require_value "$1" "${2:-}"
            CONFIGURATION=$2
            shift 2
            ;;
        --parallel)
            mcc_require_value "$1" "${2:-}"
            PARALLEL=$2
            shift 2
            ;;
        --filter)
            mcc_require_value "$1" "${2:-}"
            FILTER=$2
            shift 2
            ;;
        --fresh)
            FRESH=1
            shift
            ;;
        --allow-no-tests)
            ALLOW_NO_TESTS=1
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

BUILD_DIR=$(mcc_build_dir "$PRESET")
CONFIGURATION=$(mcc_configuration "$PRESET" "$CONFIGURATION" "Debug")
mcc_require_configuration "$CONFIGURATION"

if [ "$FRESH" -eq 1 ]; then
    "$SCRIPT_DIR/configure.sh" "$PRESET" --fresh -- \
        -DMCC_TESTING=ON
else
    "$SCRIPT_DIR/configure.sh" "$PRESET" -- \
        -DMCC_TESTING=ON
fi

set -- cmake --build "$BUILD_DIR" --config "$CONFIGURATION"
[ -z "$PARALLEL" ] || set -- "$@" --parallel "$PARALLEL"
"$@"

set -- ctest --test-dir "$BUILD_DIR" --output-on-failure
[ "$ALLOW_NO_TESTS" -eq 1 ] || set -- "$@" --no-tests=error
set -- "$@" --build-config "$CONFIGURATION"
[ -z "$PARALLEL" ] || set -- "$@" --parallel "$PARALLEL"
[ -z "$FILTER" ] || set -- "$@" --tests-regex "$FILTER"
"$@"
