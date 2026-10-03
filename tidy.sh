#!/usr/bin/env bash
set -euo pipefail

find src tests -name '*.c' \
    | xargs clang-tidy -p build \
        --header-filter='^(?!.*/external/).*' \
        "$@"
