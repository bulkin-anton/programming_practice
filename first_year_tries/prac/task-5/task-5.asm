include console.inc
    
    .data
        
        ;описание, использованных элементов, в памяти
        
        N equ 512
        Text1 db N dup(?), 0
        Text2 db N dup(?), 0
        T db "Text error: empty or too big text ", 0
        MSG1 db "Enter first  text:", 0
        MSG2 db "Enter second text:", 0
        T1 db "Hi! You are welcome 2 text which will", 0
        T2 db "be proceeded and printed by the following rules:", 0
        T3 db "1. The text`s metric will be the number of spaces(3)", 0
        T4 db "2. Text with shorter length will be proceeded first", 0
        T5 db "3. 1st: every letter after 'a' will be replaced with '*'(6)", 0
        T6 db "4. 2nd: every letter will be cyclicaly shifted to the left for k=4(5)", 0
        S1 db "Shorter text:", 0
        S2 db "Longer text:", 0
        L1 db "Length of first  text: ", 0
        L2 db "Length of second text: ", 0
        L db "It`s length after proceeding: ", 0
        C1 db '"""', 0
    
    .code

;начало программы
    ;function Leng(адрес массива):длина в метрике на eax
    
    Leng proc
          
          ;сохранение регистров
          
          push ebp
          mov ebp, esp
          sub esp, 4
          S equ dword ptr [ebp-4]
          push ebx
          push ecx
          mov ebx, [ebp+8];адрес массива
          sub ecx, ecx
          mov S, 0
    BACK: 
          ;проверка символов по условию - ищем 9,13,10,32
          
          cmp byte ptr [ebx + ecx], 9
          je SUMM
          cmp byte ptr [ebx + ecx], 10
          je SUMM
          cmp byte ptr [ebx + ecx], 13
          je SUMM
          cmp byte ptr [ebx + ecx], 32
          je SUMM
          jmp PROD
    SUMM: 
          ;нашли такой символ
          
          add S, 1
    PROD: 
          ;восстановление регистров
          
          inc ecx
          cmp byte ptr [ebx + ecx], 0
          jne BACK
          mov eax, S
          pop ecx
          pop ebx
          mov esp, ebp
          pop ebp
          ret 4
    Leng endp
 ;***********************************************
  ;function Readfunc():1-текст/0-не текст на eax
   
   Readfunc proc
          
          ;сохранение esi, edx, edi, ebx, ecx
          
          push ebp
          mov ebp, esp
          push esi
          push edx
          push edi
          push ebx
          push ecx
          mov ebx, [ebp+8]
          
          ;обнуление регистров(на всякий случай)
          
          sub esi, esi
          sub edx, edx
          sub edi, edi
          sub ecx, ecx
          mov ecx, N
          
          ;начинаем ввод
          
          inchar al
   Read:  
          ;сравнение символа с \, esi=0 при отсутствии \
          
          sub esi, esi
          cmp al, '\'
          jne FINC
          sub ah, ah
 ;***********************************************
          ;проверка на \\
          
          inchar al
          cmp al, '\'
          je Cont
          inc esi
          cmp al, '-'
          je FINC
    CHRI: 
          ;проверка на цифру
          
          cmp al, '9'
          ja LETT
          cmp al, '0'
          jb CHRE
          
          ;ошибка в одном из чисел
          
          sub al, '0'
          cmp ah, 0
          jne CHRF ;ah и al есть
          mov ah, al
          inchar al
          jmp CHRI
    LETT: 
          ;проверка на букву
          
          cmp al, 'f'
          ja CHRE
          
          ;ошибка в одном из чисел
          
          cmp al, 'a'
          jb CHRE
          
          ;ошибка в одном из чисел
          
          sub al, 'a'
          add al, 10
          cmp ah, 0
          jne CHRF ;ah и al есть
          mov ah, al
          inchar al
          jmp CHRI
    CHRF: 
          ;вычисление 16-го числа
          
          mov edi, edx
          mov dl, 16
          mov dh, al
          mov al, ah
          mul dl
          sub dl, dl
          add al, dh
          sub ah, ah
          sub dh, dh
          mov edx, edi
          mov edi, 1
          jmp Cont
    CHRE: 
          ;ввод символов при ошибке
          
          cmp ah, 0
          je CHRC     
          
          ;ошибка сразу в первой букве
          
          cmp ah, 10
          jb CHRL
          sub ah, 10
          add ah, 'a'
          sub ah, '0'
    CHRL: 
          ;ошибка во втором символе
          
          add ah, '0'
          dec ecx
          mov byte ptr [ebx+edx], ah
          inc edx
          cmp ecx, 0
          jle  ERRR
          sub ah, ah
    CHRC: 
          dec esi
 ;***********************************************
    FINC: 
          ;проверка на финиш
          
          cmp al, '-'
          jne Cont
          
          ;первый символ финиша -:fin:-
          
          inchar al
          cmp al, ':'   ;2-й
          jne A1
          inchar al
          cmp al, 'f'   ;3-й
          jne A2
          inchar al
          cmp al, 'i'   ;4-й
          jne A3
          inchar al
          cmp al, 'n'   ;5-й
          jne A4
          inchar al
          cmp al, ':'   ;6-й
          jne A5
          inchar al
          cmp al, '-'   ;7-й
          jne A6
          cmp esi, 0
          
          ;получили fin
          
          je  REND
          
          ;конец текста
 ;***********************************************
          ;проверка на зазеркаленный fin
          
          sub ecx, 7
          cmp ecx, 0
          jl  ERRR
          
          ;ошибки нет
          
          mov byte ptr [ebx+edx], '-'
          inc edx
          mov byte ptr [ebx+edx], ':'
          inc edx
          mov byte ptr [ebx+edx], 'f'
          inc edx
          mov byte ptr [ebx+edx], 'i'
          inc edx
          mov byte ptr [ebx+edx], 'n'
          inc edx
          mov byte ptr [ebx+edx], ':'
          inc edx
          mov byte ptr [ebx+edx], '-'
          inc edx
          inchar al
          jmp Read
          
          ;fin зазеркаленный есть
 ;***********************************************
    A1:   
          ;не fin на 2м символе
          sub ecx, 1
          cmp ecx, 0
          jl  ERRR
          
          ;ошибки нет
          
          mov byte ptr [ebx+edx], '-'
          inc edx
          jmp Read
 ;***********************************************
    A2:   
          ;не fin на 3м символе
          
          sub ecx, 2
          cmp ecx, 0
          jl  ERRR
          
          ;ошибки нет
          
          mov byte ptr [ebx+edx], '-'
          inc edx
          mov byte ptr [ebx+edx], ':'
          inc edx
          jmp Read
 ;***********************************************
    A3:   
          ;не fin на 4м символе
          
          sub ecx, 3
          cmp ecx, 0
          jl  ERRR
          
          ;ошибки нет
          
          mov byte ptr [ebx+edx], '-'
          inc edx
          mov byte ptr [ebx+edx], ':'
          inc edx
          mov byte ptr [ebx+edx], 'f'
          inc edx
          jmp Read
 ;***********************************************
    A4:   
          ;не fin на 5м символе
          
          sub ecx, 4
          cmp ecx, 0
          jl  ERRR
          
          ;ошибки нет
          
          mov byte ptr [ebx+edx], '-'
          inc edx
          mov byte ptr [ebx+edx], ':'
          inc edx
          mov byte ptr [ebx+edx], 'f'
          inc edx
          mov byte ptr [ebx+edx], 'i'
          inc edx
          jmp Read
 ;***********************************************
    A5:   
          ;не fin на 6м символе
          
          sub ecx, 5
          cmp ecx, 0
          jl  ERRR
          
          ;ошибки нет
          
          mov byte ptr [ebx+edx], '-'
          inc edx
          mov byte ptr [ebx+edx], ':'
          inc edx
          mov byte ptr [ebx+edx], 'f'
          inc edx
          mov byte ptr [ebx+edx], 'i'
          inc edx
          mov byte ptr [ebx+edx], 'n'
          inc edx
          jmp Read
 ;***********************************************
     A6:  
          ;не fin на 7м символе
          
          sub ecx, 6
          cmp ecx, 0
          jl  ERRR
          
          ;ошибки нет
          
          mov byte ptr [ebx+edx], '-'
          inc edx
          mov byte ptr [ebx+edx], ':'
          inc edx
          mov byte ptr [ebx+edx], 'f'
          inc edx
          mov byte ptr [ebx+edx], 'i'
          inc edx
          mov byte ptr [ebx+edx], 'n'
          inc edx
          mov byte ptr [ebx+edx], ':'
          inc edx
          jmp Read
 ;***********************************************
    Cont: 
          ;продолжаем ввод
          
          dec ecx
          mov byte ptr [ebx+edx], al
          inc edx
          cmp ecx, 0
          
          ;выдать ошибку нет финиша
          
          jle  ERRR
          inchar al
          jmp Read
    REND: 
          ;задаем конец текста
          
          mov byte ptr [ebx+edx], 0
          sub eax, eax
          jmp PEND
    ERRR: 
          ;не текст
          
          mov eax, 1
    PEND: 
          ;восстановление стека
          
          pop ecx
          pop ebx
          pop edi
          pop edx
          pop esi
          mov esp, ebp
          pop ebp
          ret 4
    Readfunc endp
 ;***********************************************
 ;procedure Preobr1(адрес текста) - изменяет по первому правилу
 
  Preobr1 proc
          push ebp
          mov ebp, esp
          push ebx
          push edx
          sub edx, edx
          mov ebx, [ebp+8]
          x equ byte ptr [ebx+edx]
   BJMP:  
          ;ищем первое вхождение 'a'
          
          cmp x, 0
          je END1
          cmp x, 'a'
          je POBR
          inc edx
          jmp BJMP
    POBR: 
          ;заменяем последующие символы
          
          inc edx
          cmp x, 0
          je END1
          mov x, '*'
          jmp POBR
    END1: 
          ;восстановление значений регистров
          
          pop edx
          pop ebx
          mov esp, ebp
          pop ebp
          ret 4
  Preobr1 endp
 ;***********************************************
 ;procedure Preobr2(адрес текста, на сколько сдвиг) - изменяет по второму правилу
  
  Preobr2 proc
          
          ;сохранение регистров
          
          push ebp
          mov ebp, esp
          push ebx
          push edx
          push ecx
          push eax
          sub eax, eax
          mov ebx, [ebp+8]
          mov ecx, [ebp+12];число k
    CIKL: 
          ;сохраняем первый элемент
          
          cmp ecx, 0
          je END2
          dec ecx
          sub edx, edx
          mov al, byte ptr [ebx+edx]
    BPRJ: 
          ;производим сдвиг
          
          cmp byte ptr [ebx+edx+1], 0
          je CENP
          mov ah, byte ptr [ebx+edx+1]
          mov byte ptr [ebx+edx], ah
          inc edx
          jmp BPRJ
    CENP: 
          ;в последний элемент кладем первый
          
          mov byte ptr [ebx+edx], al
          jmp CIKL
    END2: 
          ;восстановление регистров
          
          pop eax
          pop ecx
          pop edx
          pop ebx
          mov esp, ebp
          pop ebp
          ret 2*4
  Preobr2 endp
  
 ;***********************************************
 
 ;procedure Printfunc(адрес текста) - выводит один из текстов
  
  Printfunc proc
          
          ;сохранение регистров в стек
          
          push ebp
          mov ebp, esp
          push ebx
          push edx
          ;адрес текста
          mov ebx, [ebp+8]
          sub edx, edx
          outstrln offset C1
          
          ;вывод текста
          
    OUTP: 
          ;проверка на '"""'
          
          cmp byte ptr [ebx+edx], 0
          je PRCN
          cmp byte ptr [ebx+edx], '"'
          jne PRP1
          inc edx
          cmp byte ptr [ebx+edx], '"'
          jne PRP2
          inc edx
          cmp byte ptr [ebx+edx], '"'
          jne PRP3
          outchar '\'
          outstr offset C1
          inc edx
          jmp OUTP
    PRP3: 
          ;ошибка в 3м символе
          
          outchar '"'
    PRP2: 
          ;ошибка в 2м символе
          
          outchar '"'
    PRP1: 
          ;не '"""' и вывод
          
          cmp byte ptr [ebx+edx], 0
          je PRCN
          outchar byte ptr [ebx+edx]
          inc edx
          jmp OUTP
    PRCN: 
          ;восстановление регистров из стека
          
          outstrln offset C1
          pop edx
          pop ebx
          mov esp, ebp
          pop ebp
          ret 4
  Printfunc endp
  
 ;***********************************************
 
    Start:
          sub eax, eax
          
          ;outstrln сообщение в начале
          
          outstrln offset T1
          outstrln offset T2
          outstrln offset T3
          outstrln offset T4
          outstrln offset T5
          outstrln offset T6
          newline
          
          ;считываем тексты
          
          outstrln offset MSG1
          push offset Text1
          call Readfunc
          cmp eax, 0
          jne ERR0
          newline
          
          ;теперь второй
          
          outstrln offset MSG2
          push offset Text2
          inchar al
          call Readfunc
          cmp eax, 0
          jne ERR0        
 ;***********************************************
    RFIN: 
          ;вычислем длину текстов
          
          push offset Text1
          call Leng
          mov edx, eax
          push offset Text2
          call Leng
          newline
          outstr offset L1
          outwordln edx
          outstr offset L2
          outwordln eax
          
          ;печать длины первого и второго
 ;***********************************************
          ;преобразование текстов
          
          cmp edx, eax
          jle FLES
          push offset Text2
          call Preobr1
          push 4
          push offset Text1
          call Preobr2
          push offset Text1
          call Leng
          mov edx, eax
          push offset Text2
          call Leng
          newline
          outstrln offset S1
          
          ;вывод текстов
          
          push offset Text2
          call Printfunc
          outstr offset L
          outwordln edx
          newline
          outstrln offset S2
          push offset Text1
          call Printfunc
          outstr offset L
          outwordln eax
          jmp ENDOTL
    FLES:
          ;преобразование при другом соотношении длин

          push offset Text1
          call Preobr1
          push 4
          push offset Text2
          call Preobr2
          push offset Text1
          call Leng
          mov edx, eax
          push offset Text2
          call Leng
          newline
          outstrln offset S1

          ;вывод текстов

          push offset Text1
          call Printfunc
          outstr offset L
          outwordln edx
          newline
          outstrln offset S2
          push offset Text2
          call Printfunc
          outstr offset L
          outwordln eax;
          jmp ENDOTL
    
 ;***********************************************
 
  ENDOTL: 
          exit 0
          
 ;***********************************************
    ERR0: 
          ;вывод ошибки
          
          outstrln offset T
          exit 1
    end Start
