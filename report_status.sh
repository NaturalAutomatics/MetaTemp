#!/bin/bash<p></p>
<p>STATUS=$1</p>
<p>if [ "$STATUS" == "Success" ]; then
  CONCLUSION="success"
else
  CONCLUSION="failure"
fi</p>
