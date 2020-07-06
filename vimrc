filetype plugin on
filetype indent on
colorscheme pablo

map L $
map H ^

filetype plugin indent on

" ****************************************************
" ****** Environment settings ************************
" ****************************************************
" Tab completion done right
set wildmode=longest,list
set wildmenu
set completeopt=longest,menu,preview
" Show line numbers at all times, just like real programmers
set number
" Use hidden buffers in stead of mindless default
set hidden
" Non-horrible indentation
set tabstop=2
set shiftwidth=2
set expandtab
" Syntax highlighting
syntax on
" Incremental search, visual feedback
set incsearch
" Bells
set noerrorbells
set visualbell
autocmd VimEnter * set vb t_vb= " Make the visual bell zero time, so it doesn't blink.
" Use search highlight as default
set hls
" Smart indentation search
set ignorecase
set smartcase

set noautochdir


" Keep state about editing
set viminfo='50,\"1000,:100,n~/.vim/viminfo
" gVim specific settings
set guioptions-=T     " Remove the toolbar and menubar
set guioptions-=m
set guioptions-=r     " Remove right- and left-hand scrollbars
set guioptions-=L
set guioptions+=c     " Console-based dialogs for simple queries
"set guifont=suxus     " Yay fonts!



" ****************************************************
" ****** Key mappings ********************************
" ****************************************************
" F1: Toggle hlsearch (highlight search matches).
nmap <F1> :set hls!<CR>
" F2: Toggle list (display unprintable characters).
nnoremap <F2> :set list!<CR>
" join lines with ctrl j, to free the space
noremap <C-j> J
" scroll up/down with k and j
noremap J <c-d>
noremap K <c-u>
" use <Ctrl>+U/<Ctrl>+I to cycle through buffers, <Ctrl>+p to close current:
noremap  <C-I> :bnext<CR>
noremap  <C-U> :bprevious<CR>
noremap  <C-P> :call Kwbd(1)<CR>
" S to cycle through windows
noremap s <C-w><C-w>
" Make y behave like logic, not vi
map Y y$
" Tags!
map <S-Return> :GtagsCursor<CR>

" ****************************************************
" ****** Plugin settings *****************************
" ****************************************************
" Buffer explorer
":source ~/.vim/plugin/bufexplorer.vim
let g:bufExplorerDefaultHelp = 0
let g:bufExplorerSplitBelow = 1
let g:bufExplorerOpenMode = 1
let g:bufExplorerSplitHorzSize = 7
noremap <silent> <unique> S :BufExplorerVerticalSplit<CR>



" ****************************************************
" ****** Other stuff *********************************
" ****************************************************


" Syntastic defaults
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1

let g:elm_syntastic_show_warnings = 1


" Remember base dir to use with scripts
let g:startdir = getcwd()

"compile with F2:
nmap <F2> :make silent<RETURN>

" Specify a directory for plugins (for Neovim: ~/.local/share/nvim/plugged)
call plug#begin('~/.vim/plugged')
  Plug 'vim-syntastic/syntastic'
  Plug 'jlanzarotta/bufexplorer'
  Plug 'Valloric/YouCompleteMe'
  
call plug#end()
