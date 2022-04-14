#!/usr/bin/env bash

if [[ $(command -v git) ]]
then
    if [ -w $TMPDIR ] 
    then DIR=$TMPDIR/libml
    else DIR=/var/tmp/libml
    fi
    
    mkdir -p $DIR
    
    git clone https://github.com/lewardo/libml.git $DIR
    
    cd $DIR
    sudo make install
    
    rm -rf $DIR
else
    echo "pls install git and retry"
fi