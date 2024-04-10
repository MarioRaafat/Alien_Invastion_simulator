#!/usr/bin/env bash
# this script is for fast pushing to git
if [ "${#}" -ge 2 ]
then
    msg="${1}"
else
    read -p "Enter Your Commit Msg Plz: " msg
fi

git add .
git commit -m "${msg}"
git push