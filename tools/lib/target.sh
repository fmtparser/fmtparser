#!/bin/bash

# Get default build folder for Win32
function target_win32_def_build_folder()
{
    echo "build-win32"
    return 0
}

# Get default build folder for Linux
function target_linux_def_build_folder()
{
    echo "build"
    return 0
}
