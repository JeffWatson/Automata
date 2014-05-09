#!/bin/bash

echo "Content-type: text/plain"
echo "" # Blank line to meet HTTP protocol

POST_DATA=""
read -n $CONTENT_LENGTH POST_DATA <&0
#hash -r
echo “Post data: ${POST_DATA}” > test.txt
echo $(whoami) >> test.txt
echo $(type pdflatex) &>> test.txt
echo $(type /usr/bin/pdflatex) &>> test.txt
echo $(ls) >> test.txt

regex=${POST_DATA#regex=}

#echo "running on Regex: ${regex}"

#// TODO: run backend Program, save output to file (./program > $regex.json)
#// run script converting json to LaTeX (./template $regex.json > $regex.tex)
#// echo a json object with "FAILURE" or "SUCCESS" ( echo "{ "status" : "SUCCESS", "file" : "$regex.pdf"})
#// front end will then load the pdf and inject it in to the webpage

./AutomataBack "${regex}" "" > "./tex/${regex}"
cd tex
./pdflatex "${regex}" &>> ./../test.txt
mv "${regex}.pdf" "../pdf/${regex}.pdf"

echo '{"status" : "SUCCESS", "file" : "'${regex}'.pdf"}' | tee ./json/$regex.json
#echo '{"status" : "ERROR", "message" : "Unable to Complete"}'
