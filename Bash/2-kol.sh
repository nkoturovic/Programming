#!/usr/bin/env bash

egrep '.*' 'rezultati.csv' \
| sed -E 's:([A-Z][a-z]*\s*([A-Za-z][a-z]*)?\s*([A-Z][a-z]*)?)\s*,\s*([A-Z][a-z]+)\s*,\s*([1-9][0-9]*)\s*,\s*([1-9][0-9]*)\s*,\s*([0-9]{4})-([0-9]{4}?\s*)\s*,(.*):\1 (\4) [\7-\8] \: \9 golmark \6:g' \
| sed -E 's/,/ -> /g' \
| sed -E 's/golmark [0-9]{2}//g' \
| egrep -E '[0-9]+$' \
| sed -E 's/[0-9]+$//g' \
| egrep -E '[0-9]{4}-[0-9]{4}'
