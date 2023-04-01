#!/usr/bin/env bash

if [[ $(command -v git) ]] && [[ $(command -v sudo) ]] && [[ $(command -v make) ]]
then
    DIR=${TMPDIR:-/var/tmp/}/libml
    
    mkdir -p $DIR
    
    git clone https://github.com/lewardo/libml.git $DIR
    
    cd $DIR
    PREFIX=/usr/local make install
    
    rm -rf $DIR
fi
