#!/bin/bash
set -e

if [ ! -d extern ]; then
	mkdir extern
	ln -s ../../ extern/B3d
fi

buildDir='build'
if [ ! -d "$buildDir" ]; then
	mkdir "$buildDir"
fi

clear
pushd "$buildDir"

cmake .. -G "Unix Makefiles"
cmake --build . -- -j $(nproc)

popd