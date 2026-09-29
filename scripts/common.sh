#!/bin/sh

. "$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)/romodular-adapter.sh"
. "$MCC_ROMODULAR_SCRIPTS/common.sh"

mcc_die() {
    romodular_die "$@"
}

mcc_require_command() {
    romodular_require_command "$@"
}

mcc_require_value() {
    romodular_require_value "$@"
}

mcc_require_preset() {
    romodular_require_preset "$@"
}

mcc_build_dir() {
    romodular_build_dir "$@"
}

mcc_configuration() {
    romodular_configuration "$@"
}

mcc_require_configuration() {
    romodular_require_configuration "$@"
}

mcc_require_configured() {
    romodular_require_configured "$@"
}

mcc_absolute_path() {
    romodular_absolute_path "$@"
}

mcc_require_safe_dist_child() {
    romodular_require_safe_dist_child "$@"
}
