" Terminal windows are insert by default
let g:previous_window = -1
function SmartInsert()
  if &buftype == 'terminal'
    if g:previous_window != winnr()
      startinsert
    endif
    let g:previous_window = winnr()
  else
    let g:previous_window = -1
  endif
endfunction

au BufEnter * call SmartInsert()

" Double esc in terminal gives normal mode
tnoremap <silent> <C-[><C-[> <C-\><C-n>
