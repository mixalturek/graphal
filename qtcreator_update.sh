#!/bin/bash

find . -type f \
| grep -v '^\./\.' \
| grep -v '^\./build/' \
| grep -v '^\./history/' \
| sort > graphal.files
