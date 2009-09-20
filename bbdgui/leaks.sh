#!/bin/bash
valgrind --leak-check=full --show-reachable=yes ./bbdgui 2>&1 | sed 's/^==.*== //' | sed 's/\(at\|by\) 0x[0-9A-F]*: //' > leaks_`date +%F_%T | tr ':' '-'`.txt
