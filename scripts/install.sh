#!/bin/sh
set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
. "$SCRIPT_DIR/common.sh"

usage() {
    printf '%s\n' "Usage: $0 <preset> [--prefix <path>]"
}

PRESET=""
PREFIX=""

while [ "$#" -gt 0 ]; do
    case "$1" in
        --prefix)
            mcc_require_value "$1" "${2:-}"
            PREFIX=$2
            shift 2
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
mcc_require_configured "$PRESET"

BUILD_DIR=$(mcc_build_dir "$PRESET")
[ -n "$PREFIX" ] || PREFIX="$MCC_DIST_ROOT/$PRESET"
PREFIX=$(mcc_absolute_path "$PREFIX")

set -- cmake --install "$BUILD_DIR" --prefix "$PREFIX"
set -- "$@" --config Release

"$@"
