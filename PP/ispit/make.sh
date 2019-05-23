#!/bin/bash

clear

echo "Compiling $1 to PDF ..."
ARGUMENT="$1"
pandoc $ARGUMENT.md --template template.latex --listings --pdf-engine=xelatex -o $ARGUMENT.pdf --toc --reference-links --toc-depth=3

#--reference-links 
#--number-sections
#--filter pandoc-crossref

ps axf | grep epdfview | grep -v grep | awk '{print "kill -s SIGHUP " $1}' | bash
