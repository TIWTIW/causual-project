#!/bin/bash

if [ $# -ne 3 ]
then
    echo "Usage: upload_to_arm.sh [filename] [IP] [port]"
    exit 1
else
    echo "downloading $1 from the root@$2:/home/limin/$1"
    scp -P $3 root@$2:/home/limin/$1 $1
    echo "Downloaded!"
    exit 0
fi
