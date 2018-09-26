tmpfile=$(mktemp /tmp/mail-XXXXXX.txt)
echo -e "To: costyr@gmail.com" >> $tmpfile
echo -e "From: costyrpithermostat@gmail.com" >> $tmpfile
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

ssmpt costyr@gmail <<< $tmpfile
rm $tmpfile
