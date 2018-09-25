rm mail.txt
echo -e "To: costyr@gmail.com" >> mail.txt
echo -e "From: costyrpithermostat@gmail.com" >> mail.txt
echo -e "Content-type: text/html;" >> mail.txt
IFS=
LastErrors=$(tail /var/log/syslog)
IFS='\n'
read -rd '' -a array <<< "$LastErrors"

echo -e >> mail.txt
echo -e >> mail.txt
echo -e '<html><body><div style="background: #e9ecef; padding: 10pt;"/>' >> mail.txt
for element in "${array[@]}"
do
    echo "<p>$element</p>" >> mail.txt
done
echo -e "</div></body></html>" >> mail.txt

