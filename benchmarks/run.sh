#!/bin/bash
# ./run.sh > run.log 2>&1

echo '-----------------------------------------------------'

echo 'command: time ./var'
time ./var

echo '---------------------------'

echo 'command: time ../bbd/bbd var.txt'
time ../bbd/bbd var.txt

echo '-----------------------------------------------------'

echo 'command: time ./array'
time ./array

echo '---------------------------'

echo 'command: time ../bbd/bbd array.txt'
time ../bbd/bbd array.txt

echo '-----------------------------------------------------'

echo 'command: time ./func'
time ./func

echo '---------------------------'

echo 'command: time ../bbd/bbd func.txt'
time ../bbd/bbd func.txt

echo '-----------------------------------------------------'
