#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
. "$SCRIPT_DIR/common.sh"

usage() {
    printf '%s\n' "Usage: $0 <preset> [--dist]"
    printf '%s\n' "       $0 --all [--dist]"
}

PRESET=""
ALL=0
REMOVE_DIST=0

while [ "$#" -gt 0 ]; do
    case "$1" in
        --all)
            ALL=1
            shift
            ;;
        --dist)
            REMOVE_DIST=1
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

if [ "$ALL" -eq 1 ] && [ -n "$PRESET" ]; then
    mcc_die "specify either a preset or --all, not both"
fi
if [ "$ALL" -eq 0 ] && [ -z "$PRESET" ]; then
    usage
    mcc_die "a preset or --all is required"
fi

if [ "$ALL" -eq 1 ]; then
    cmake -E remove_directory "$MCC_BUILD_ROOT"
    [ "$REMOVE_DIST" -eq 0 ] || cmake -E remove_directory "$MCC_DIST_ROOT"
else
    mcc_require_preset "$PRESET"
    cmake -E remove_directory "$MCC_BUILD_ROOT/$PRESET"
    [ "$REMOVE_DIST" -eq 0 ] || cmake -E remove_directory "$MCC_DIST_ROOT/$PRESET"
fi
