#!/bin/sh

# get base file name
filename=$1
html_file=${filename%.*}.html
opf_file=${filename%.*}.opf

# remove page numbers
sed 's/^[[:space:]]*[[:digit:]]\+[[:space:]]*$//g' <$filename >temp.1

# remove separators
sed 's/^[[:space:]]*\(\*\+[[:space:]]*\)\+[[:space:]]*$//g' <temp.1 >temp.2

# remove other things

# process chapters/titles

# remove empty lines
tr '\n' '~' <temp.2 >temp.3
sed 's/\([[:lower:]]\)\~\~\+/\1\~/g' <temp.3 >temp.a

# split paragraphs
sed 's/\([[:punct:]]\)\~[[:space:]]*\(\-\|[[:upper:]]\|\"\|[[:digit:]]\)/\1~~\2/g' <temp.a >temp.4

# join paragraphs
sed 's/\([^\~]\)\~\([^\~]\)/\1 \2/g' <temp.4 >temp.5
tr '~' '\n' <temp.5 >temp.6

# add <p>
sed 's/^\([^<].*\)$/<p>\1<\/p>/g' <temp.6 >temp.7

# change HTML special chars

# change hyphens
sed 's/-\([[[:space:]]\|[[:punct:]]]\)/\&\#8212;\1/g' <temp.7 >temp.8

# add header/footer
echo '<html><body>' > $html_file
cat temp.8 >> $html_file
echo '</body></html>' >> $html_file

# create ODF

# remove temp files
rm temp.*
