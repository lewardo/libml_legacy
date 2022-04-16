#!/usr/bin/env bash

function print_command_available {
    [ ! $(command -v $1) ] && echo -n " ✘ " || echo -n " ✔ " && echo $1
}

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
    
    for dep in "git" "sudo" "make"; do
        print_command_available $dep
    done
fi