#!/bin/bash

echo "Content-type: text/plain"
echo ""

POST_DATA=$(</dev/stdin)

#echo “Post data: ${POST_DATA}”

regex=${POST_DATA#regex=}

#echo "running on Regex: ${regex}"

#// TODO: run backend Program, save output to file (./program > $regex.json)
#// run script converting json to LaTeX (./template $regex.json > $regex.tex)
#// echo a json object with "FAILURE" or "SUCCESS" ( echo "{ "status" : "SUCCESS", "file" : "$regex.pdf"})
#// front end will then load the pdf and inject it in to the webpage

echo '{"status" : "SUCCESS", "file" : "'${regex}.pdf'"}' | tee ./json/${regex}.json
#echo '{"status" : "ERROR", "message" : "Unable to Complete"}'
