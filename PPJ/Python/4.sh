#!/usr/bin/env bash


echo '<h3>Grupe</h3>'
echo '<table border="1px">'
echo '<tr><th>GROUP NAME</th><th>PASSWORD</th><th>GID</th></tr>'
egrep '([a-z]+):([a-z]):([0-9]+)' -o '/etc/group' \
| sed -E 's?^([a-z]+):([a-z]):([0-9]+)?<tr><td>\1</td><td>\2</td><td>\3</td></tr>?g'
echo '</table>'
