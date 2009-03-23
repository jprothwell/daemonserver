#! /bin/sh

ls -l /home/michael > hometree

git add hometree
git commit -a -m 'hometree'

git-svn dcommit
