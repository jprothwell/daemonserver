#!/bin/sh

find . -name "**.h" -o -name "**.c" -o -name "**.cc" > cscope.files**

cscope -bkq -i cscope.files

ctags -R

and open the cpp file with the vim, you can use the vim to search the function call, you can use ctrl+] to step in and ctrl+t to step out.