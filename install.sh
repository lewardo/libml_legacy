#!/usr/bin/env bash

if [[ $(command -v git) ]] && [[ $(command -v sudo) ]] && [[ $(command -v make) ]]
then
    export DIR = ${TMPDIR:-/var/tmp/}
    
    mkdir -p $DIR
    
    git clone https://github.com/lewardo/libml.git $DIR
    
    cd $DIR
    sudo make install
    
    rm -rf $DIR
else
    echo "pls install git and retry"
fi