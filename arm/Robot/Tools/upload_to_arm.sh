#!/bin/bash

if [ $# -ne 3 ]
then
    echo "Usage: upload_to_arm.sh [filename] [IP] [port]"
    exit 1
else
    echo "uploading $1 to the root@$2:/home/limin/$1"
    scp -P $3 $1 root@$2:/home/limin/$1
    echo "Uploaded!"
    exit 0
fi
