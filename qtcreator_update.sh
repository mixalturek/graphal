#!/bin/bash

find . -type f \
| grep -v '^\./\.' \
| grep -v '^\./build/' \
| grep -v '^\./history/' \
| grep -v '^\./man/' \
| grep -v '^\./graphs_generator/' \
| sort > graphal.files
