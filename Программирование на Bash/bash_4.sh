#!/usr/bin/bash

if [ $# -ne 2 ]
then
        echo Дайте два аргумента
fi


if [ -f $1 -a -f $2 ]
then
        echo $1 и $2 обычные файлы
fi

# разница для сравнения с нулем
differ=$(cmp -b $1 $2)

if [ $2 -ot $1 ]
then
        new=$1
        echo $new новее, чем $2
        myFileSize=$(stat -c %s $new)

        if [[ $differ!=0 && $myFileSize!=0 ]]
        then
                cat $new >> $2
        fi

else
        new=$2
        echo $new новее, чем $1
        myFileSize=$(stat -c %s $new)

        if [[ $differ!=0 && $myFileSize!=0 ]]
        then
                cat $new >> $1
        fi
fi
      
