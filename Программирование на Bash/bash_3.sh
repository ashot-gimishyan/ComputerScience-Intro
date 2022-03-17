#!/usr/bin/bash

if [ $# -ne 2 ]
then
        echo Дайте 2 аргумента
fi

if [ ! -d $1 ]
then
        echo Такого каталога не существует!
        echo Создаю его...
        mkdir $1
        echo Каталог $1 успешно создан
fi

masterfile=$(stat $2 --print=%U)
mastercd=$(stat $1 --print=%U)

if [ -f $2 -a $masterfile==$mastercd ]
then
        cp $2 $1
else
        echo Нет такого файла или авторы файла и каталога не совпадают
fi
