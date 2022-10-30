#!/usr/bin/bash

if [ $# -eq 3 ]
then
        SUM=$(($1+$2+$3))
        SRED=$(($SUM/3))
        echo $SRED
	exit 0
fi

echo Give me three numeric arguments!!!

# ashot-gimishyan
