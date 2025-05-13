.686
.model flat
    .code

extern P$PROGRAM_$$_PRINTL$LINK_T:near
extern P$PROGRAM_$$_POINT$LINK_T$LONGINT:near
public movtr

    .code
movtr proc

  ;пролог
  
  push ebp
  mov ebp, esp
  push edx
  push ebx
  push ecx
  push esi
  
  ; адрес в памяти элемента
  
  mov edx, [ebp+8]
  
  ;печать элемента
  
  push edx
  call P$PROGRAM_$$_PRINTL$LINK_T
  
  ;получаем адрес левого поддерева
  
  mov edx, [ebp+8]
  add edx, 32
  mov ecx, [edx]  ;a^.left
  
  ;проверка на nil
  
  cmp ecx, 0
  je CONT
  mov edx, [ebp+8]
  
  ;печать путей из корня
  
  push 1
  push edx
  call P$PROGRAM_$$_POINT$LINK_T$LONGINT
  
  ;переходим на левое поддерево
  
  mov edx, [ebp+8]
  add edx, 32
  mov ecx, [edx]
  push ecx
  call movtr
  
  ;получена высота левого поддерева
  
  mov esi, eax

CONT:

  ;получаем адрес левого поддерева
  
  mov edx, [ebp+8]
  add edx, 36
  mov ecx, [edx] ;a^.right
  cmp ecx, 0
  je PRDL
  
  ;печать путей из корня
  
  mov edx, [ebp+8]
  push 0
  push edx
  call P$PROGRAM_$$_POINT$LINK_T$LONGINT
  
  ;переходим на правое поддерево
  
  mov edx, [ebp+8]
  add edx, 36
  mov ecx, [edx]
  push ecx
  call movtr
  
  ;получена высота правого
  ;сравнение высот левого и правого
  
  cmp eax, esi
  jge FIN
  mov eax, esi

PRDL:

  ;вводим высоту у листа

  mov edx, [ebp+8]
  add edx, 32
  mov ecx, [edx]
  cmp ecx, 0
  jne FIN
  sub eax, eax

FIN:

  ;эпилог
  
  inc eax
  pop esi
  pop ecx
  pop ebx
  pop edx
  pop ebp
  ret 4
movtr endp
end
