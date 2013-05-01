#!/bin/bash

find . -type f \
| grep -v '^\./\.' \
| grep -v '^\./build/' \
| grep -v '^\./history/' \
| grep -v '^\./man/' \
| sort > graphal.files
