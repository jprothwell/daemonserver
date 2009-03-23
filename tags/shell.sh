#! /bin/sh

cd
cd Desktop
ls -la > desktop

git add desktop
git commit -a -m 'desktop'

git-svn dcommit
