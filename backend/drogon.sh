#!/bin/bash

PROJECT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
CTL_BINARY="$PROJECT_ROOT/cmake-build-debug/vcpkg_installed/x64-linux/tools/drogon/drogon_ctl"
if [ ! -f "$CTL_BINARY" ]; then
    echo "错误: 找不到 drogon_ctl！"
    echo "请确保你已经在使用vcpkg编译安装了vcpkg.json内的所有内容"
    exit 1
fi
"$CTL_BINARY" "$@"