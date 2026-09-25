#!/bin/sh

MCC_SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
MCC_ROOT=$(CDPATH= cd -- "$MCC_SCRIPT_DIR/.." && pwd)
MCC_BUILD_ROOT="$MCC_ROOT/build"
MCC_DIST_ROOT="$MCC_ROOT/dist"

mcc_die() {
    printf '%s\n' "error: $*" >&2
    exit 2
}

mcc_require_command() {
    command -v "$1" >/dev/null 2>&1 || mcc_die "required command not found: $1"
}

mcc_require_value() {
    [ "$#" -ge 2 ] || mcc_die "internal error: mcc_require_value expects a flag and value"
    [ -n "$2" ] || mcc_die "$1 requires a value"
}

mcc_require_preset() {
    [ -n "${1:-}" ] || mcc_die "a CMake configure preset is required"
    case "$1" in
        *..*|*/*|*\\*)
            mcc_die "invalid preset name: $1"
            ;;
    esac
}

mcc_build_dir() {
    printf '%s\n' "$MCC_BUILD_ROOT/$1"
}

mcc_configuration() {
    if [ -n "${2:-}" ]; then
        printf '%s\n' "$2"
        return
    fi

    case "$1" in
        documentation)
            printf '%s\n' "Release"
            ;;
        *)
            printf '%s\n' "${3:-Debug}"
            ;;
    esac
}

mcc_require_configuration() {
    case "$1" in
        Debug|Release)
            ;;
        *)
            mcc_die "unsupported configuration '$1'; expected Debug or Release"
            ;;
    esac
}

mcc_require_configured() {
    BUILD_DIR=$(mcc_build_dir "$1")
    [ -f "$BUILD_DIR/CMakeCache.txt" ] || mcc_die "preset '$1' is not configured; run scripts/configure.sh $1 first"
}

mcc_absolute_path() {
    case "$1" in
        /*)
            printf '%s\n' "$1"
            ;;
        *)
            printf '%s\n' "$MCC_ROOT/$1"
            ;;
    esac
}

mcc_require_safe_dist_child() {
    case "$1" in
        "$MCC_DIST_ROOT"/*)
            ;;
        *)
            mcc_die "refusing to remove export path outside $MCC_DIST_ROOT: $1"
            ;;
    esac
}

mcc_require_command cmake
cd "$MCC_ROOT" || mcc_die "cannot enter repository root: $MCC_ROOT"
