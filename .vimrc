"基本
syntax on
set number     "行番号
set autoindent "インデント引き継ぎ
set showmode   "モード表示
set enc=utf-8
set fencs=utf-8
set tabstop=3
set shiftwidth=3
set expandtab
setlocal formatoptions-=r
setlocal formatoptions-=o

set title   "タイトルを表示
set ruler   "ルーラーを表示
set autoread   "他で書き換えられたら自動で読み直し
set showmatch  "対応するカッコのハイライト
set laststatus=2  "常にステータスラインを表示する
set noswapfile
set nobackup
"前回開いたときの位置を呼び出し
function! GetEFstatus()
   let str = ''
   let fenc = ''
   if &fileformat == 'unix'
      let str = '[UNIX]'
   else
      let str = '[' . &fileformat . ']'
   endif
   if &fileencoding != ''
      if &fileencoding =~# 'iso-2022-jp'
         let fenc = 'J'
      elseif &fileencoding == 'utf-8'
         let fenc = 'U'
      elseif &fileencoding == 'cp932'
         let fenc = 'S'
      elseif &fileencoding =~# 'euc-jp'
         let fenc = 'E'
      else
         let fenc = &fileencoding
      endif
         let str = str . '[' . fenc . ']'
      else
         let str = str . '[-]'
      endif
         unlet fenc
         return str
      endfunction
set statusline=%-50.50F\ %16(\ %m%r%{GetEFstatus()}%)%=%l/%L\ %5P

"copy and paste"-related
set guioptions+=a
set clipboard+=autoselect
set clipboard+=unnamed
nmap ? :.w !pbcopy<CR><CR>
vmap ? :w !pbcopy<CR><CR>
nmap Z :r !pbpaste<CR>
vmap Z : !pbpaste<CR>


abbr incldue include
nnoremap vf ][v[[?^?s*$<CR>   "C/C++で関数を範囲選択
nnoremap vb /{<CR>%v%0     "forのエリア表示

"backspace function"
set backspace=indent,eol,start

"color setting
set background=dark
hi clear
if exists("syntax_on")
  syntax reset
endif
hi Normal guibg=Black guifg=seashell ctermfg=White
hi NonText guifg=LavenderBlush ctermfg=LightMagenta
hi DiffDelete guibg=DarkRed guifg=Black ctermbg=DarkRed ctermfg=White
hi DiffAdd guibg=DarkGreen ctermbg=DarkGreen ctermfg=White
hi DiffChange guibg=Gray30 ctermbg=DarkCyan ctermfg=White
hi DiffText gui=NONE guibg=DarkCyan ctermbg=DarkCyan ctermfg=Yellow
hi Comment guifg=LightBlue
hi PreProc ctermfg=Magenta
hi VertSplit guifg=Gray
hi Type gui=NONE
hi Identifier guifg=Cyan
hi Statement guifg=brown3 ctermfg=DarkRed
hi Search guibg=Gold3 ctermfg=White
hi Folded guibg=gray20
hi FoldColumn guibg=gray10

"mis-spelling"
highlight ZenkakuSpace cterm=underline ctermfg=DarkCyan guibg=white
match ZenkakuSpace /　/

" vim-indent-guides
let g:indent_guides_auto_colors=0
autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd   ctermbg=235
autocmd VimEnter,Colorscheme * :hi IndentGuidesEven  ctermbg=17
let g:indent_guides_enable_on_vim_startup=1
let g:indent_guides_guide_size=1

"常に補完候補を表示するように
set completeopt=menuone
for k in split("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_",'\zs')
  exec "imap <expr> " . k . " pumvisible() ? '" . k . "' : '" . k . "\<C-X>\<C-P>\<C-N>'"
endfor



"statusline
let g:hi_insert = 'highlight StatusLine guifg=darkblue guibg=darkyellow gui=none ctermfg=blue ctermbg=lightblue cterm=none'
if has('syntax')
   augroup InsertHook
       autocmd!
       autocmd InsertEnter * call s:StatusLine('Enter')
       autocmd InsertLeave * call s:StatusLine('Leave')
     augroup END
   endif
let s:slhlcmd = ''
function! s:StatusLine(mode)
  if a:mode == 'Enter'
    silent! let s:slhlcmd = 'highlight ' . s:GetHighlight('StatusLine')
    silent exec g:hi_insert
  else
    highlight clear StatusLine
    silent exec s:slhlcmd
  endif
endfunction

function! s:GetHighlight(hi)
  redir => hl
  exec 'highlight '.a:hi
  redir END
  let hl = substitute(hl, '[\r\n]', '', 'g')
  let hl = substitute(hl, 'xxx', '', '')
  return hl
endfunction

""""
 " Note: Skip initialization for vim-tiny or vim-small.
 if 0 | endif

 if has('vim_starting')
   if &compatible
     set nocompatible               " Be iMproved
   endif

   " Required:
   set runtimepath+=~/.vim/bundle/neobundle.vim/
 endif

 " Required:
 call neobundle#begin(expand('~/.vim/bundle/'))

 " Let NeoBundle manage NeoBundle
 " Required:
 NeoBundleFetch 'Shougo/neobundle.vim'

 " My Bundles here:
 " Refer to |:NeoBundle-examples|.
 " Note: You don't set neobundle setting in .gvimrc!
NeoBundle 'Shougo/vimproc'
NeoBundle 'Shougo/neocomplcache'
NeoBundle 'nathanaelkane/vim-indent-guides'

 call neobundle#end()

 " Required:
 filetype plugin indent on

 " If there are uninstalled bundles found on startup,
 " this will conveniently prompt you to install them.
 NeoBundleCheck

 set nowrap
