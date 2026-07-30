#!/usr/bin/env bash
set -euo pipefail

find src tests -name '*.c' \
    | xargs clang-tidy --fix -p build \
        --header-filter='^(?!.*/external/).*'
