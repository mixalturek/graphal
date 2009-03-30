#!/bin/bash
grep -v 'debug: ' run.log | grep -v '\[i\]' > run_`date +%F_%T | tr ':' '-'`.log
