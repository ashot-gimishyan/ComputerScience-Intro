#!/usr/bin/bash

if [ $# -ne 2 ]
then    
        echo Дайте 2 аргумента
fi

if [ -d $1 && -d $2 ]
then
	continue
else
	echo Нужны 2 каталога
fi

res=diff $1 $2

if [ $res == 0 ]
then
	mkdir BKP
fi

if [ $1 -nt $2 && -s $1 ]
then
	cp $2.{$(stat --print=%x)} BKP
	cp $1 $2
fi
