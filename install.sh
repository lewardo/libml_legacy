#!/usr/bin/env bash

if [[ $(command -v git) ]] && [[ $(command -v sudo) ]] && [[ $(command -v make) ]]
then
    DIR=${TMPDIR:-/var/tmp/}/libml
    
    mkdir -p $DIR
    
    git clone https://github.com/lewardo/libml.git $DIR
    
    cd $DIR
    make install PREFIX=/usr/local
    
    rm -rf $DIR
else
    echo "pls install dependencies and retry"
    [ ! $(command -v git) ] && echo -e "\t✘ git" || echo -e "\t✔ git"
    [ ! $(command -v sudo) ] && echo -e "\t✘ sudo" || echo -e "\t✔ sudo"
    [ ! $(command -v make) ] && echo -e "\t✘ make" || echo -e "\t✔ make"
fi