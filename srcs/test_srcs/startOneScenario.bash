#!/bin/bash
FILES=$(ls $1)
cd $1
cat $FILES | nc localhost 3333