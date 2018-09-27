#!/bin/bash

tmpfile=$(mktemp /tmp/mail-XXXXXX.txt)
echo -e "From: $1" >> $tmpfile
echo -e "Date: $(date -R)" >> $tmpfile
echo -e "Subject: Thermostat service failed!" >> $tmpfile
echo -e "MIME-Version: 1.0" >> $tmpfile
echo -e "Content-type: text/html; charset=utf-8" >> $tmpfile
IFS=
LastErrors=$(tail /var/log/thermostat.log)
IFS=$'\n'
read -rd '' -a array <<< "$LastErrors"

echo -e >> $tmpfile
echo -e >> $tmpfile
echo -e '<html><body><div style="background: #e9ecef; padding: 10pt;"/>' >> $tmpfile
for element in "${array[@]}"
do
    echo "<p>$element</p>" >> $tmpfile
done
echo -e "</div></body></html>" >> $tmpfile

cat $tmpfile | ssmtp $2
rm $tmpfile
