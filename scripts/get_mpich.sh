#!/bin/bash

echo "Downloading mpich source."
wget http://www.mpich.org/static/downloads/3.2/mpich-3.2.tar.gz
tar xfz mpich-3.2.tar.gz
rm mpich-3.2.tar.gz
echo "configuring and building mpich."
cd mpich-3.2
./configure \
        --enable-static=false \
        --enable-alloca=true \
        --disable-long-double \
        --enable-threads=single \
        --enable-fortran=no \
        --enable-fast=all \
        --enable-g=none \
        --enable-timing=none
make -j4
make install
cd -
rm -rf mpich-3.2