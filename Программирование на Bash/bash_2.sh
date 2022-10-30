#!/usr/bin/bash

if [ $# -ne 2 ]
then
        echo ДВА аргемента!!!
        exit 1
fi

if [ -f $1 -a -f $2 ]
then

	#var1 хранит имя первого аргумента (файла)
	var1=$1

	#var2 хранит имя второго аргумента (файла)
	var2=$2

	#"склеивание" имен двух файлов
	var3=$1$2

	#команда touch создает файл
	touch $var3

        cat $var1 > $var3
        cat $var2 >> $var3

	echo Процесс успешно закончился
        exit 0
fi

echo Файл не существуют

# ashot-gimishyan
