syntax on

set autoindent
set smartindent

set tabstop=4
set shiftwidth=4

set vb t\_vb=

set ruler
set incsearch
set ignorecase

color murphy

set guifont=Lucida\ Console\ Semi-Condensed\ 12

set tags=tags;/

"using mouse
set mouse=a

" show the command
set showcmd

let Tlist\_Use\_Right\_Window=1
let Tlist\_File\_Fold\_Auto\_Close=1

"map 

&lt;F5&gt;

 :Explore

&lt;CR&gt;



"map 

&lt;F6&gt;

 :TlistToggle

&lt;CR&gt;



"map 

&lt;F7&gt;

 :call Search\_Word()

&lt;CR&gt;



"inoremap 

&lt;F8&gt;

 

&lt;C-x&gt;



&lt;C-o&gt;



" step into
"map 

&lt;F2&gt;

 <C-]>
" step out
"map 

&lt;F3&gt;

 

&lt;C-t&gt;


"map 

&lt;F4&gt;

 <\-m>

" auto full the command under command pattern
set wildmode=list:full
set wildmenu