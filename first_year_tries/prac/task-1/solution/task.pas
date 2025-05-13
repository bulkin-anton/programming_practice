const MINVALUE=-9223372036854775808;
      NAXVALUE=9223372036854775807;
      BASIS='0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*';
      
var result, number:Int64;
    c, m:char;
    i, num_base, bit_width, width, err, j, base:integer;
    num_base_output:array[2..70] of boolean;
    flag_eoln, flag_eof, flag_skip:boolean;
    operacia, s, znak, bit_wide_input, inp:string;
    
function Stepen(x:integer):Int64;
    var i:integer;
        s:Int64;
    begin
        s:=1;
        for i:=1 to x-2 do 
        begin
            s:=s*2
        end;
        Stepen:=2*(s-1)+1
    end;

function Perevod(osn:integer; var res:Int64):string;
    var f:Int64; zn, s:string;
    begin
      f:=res;
      if f=0 then Perevod:='0'
      else
          begin
            if (f<>MinValue) then 
              begin
                if (f<0) then zn:='-'
                else zn:='+';
                f:=abs(f);
                s:='';
                while f>0 do
                    begin
                        s:=BASIS[(f mod osn)+1]+s;
                        f:=f div osn;
                    end;
               end;
          case zn of
              '+': Perevod:=s;
              '-': Perevod:='-'+s;
          end;
        end;
    end;

function Perepolnenie(num:Int64; wdth: integer):boolean; 
    begin
        if (num>=-1-Stepen(wdth)) and (num<=Stepen(wdth))
        then Perepolnenie:=False
        else Perepolnenie:=True;
    end;

function Proverka(c:char; osn:integer):boolean;
    var i, k:integer;
    begin
        k:=0;
        for i:=1 to osn do 
            begin
                if c = BASIS[i] then 
                    begin
                        Proverka:=True;
                        break;
                    end
          else k:=k+1;
            end;
      if (k=osn) then Proverka:=False;
    end;

function Findex(c:char):integer;
    var i:integer;
    begin
        for i:=1 to 70 do 
        begin
            if c = BASIS[i] then
            begin
                Findex:=i-1;
                break;
            end;
        end;
    end;


procedure Out;
    var i:integer;
        s:string;
    begin
        for i:=2 to 70 do begin
          if (num_base_output[i]=True) then 
              begin
                  s:=Perevod(i, result);
                  if (i<10) then WriteLn(i, '  ', s)
                  else WriteLn(i, ' ', s);
              end;
        end;
    end;

procedure Konec(tip:string);
begin
  case tip of 
  'finish' : 
      begin    
          Out;
          Halt(1);
      end;
  'operation':
      begin
          WriteLn('Wrong type of operation');
          Out;
          Halt(0);
      end;
  'parametr':
      begin
          WriteLn('Wrong values of parametrs');
          Out;
          Halt(0);
      end;
  'perepolnenie':
      begin
          WriteLn('The value is overflowing');
          Out;
          Halt(0);
      end;
  'basis':
      begin
          WriteLn('Wrong number base');
          Out;
          Halt(0);
      end;
  'bit':
      begin
          WriteLn('Wrong bit_width of a number');
          Out;
          Halt(0);
      end;
  'number':
      begin
          WriteLn('Wrong value of a number');
          Out;
          Halt(0);
      end;
  else 
      begin
          WriteLn('Wrong input');
          Out;
          Halt(0);
      end;
  end;
end;


procedure Probel_reset(var c:char);
begin
    repeat 
    if not(eof) then 
        begin
            if not(eoln) then Read(c)
            else 
                begin
                    if eoln then begin flag_eoln:=True; break; end;
                end;
        end
    else begin flag_eof:=True; break; end;
    until c<>' ';
end;



begin
    flag_eof:=False;
    result:=0;
    if (ParamCount<2) then
      begin
          WriteLn('Not enough values to start a program');
          Out;
          Halt(0);
      end;
    bit_wide_input:=ParamStr(1);
    Val(bit_wide_input, width, err);
    if err<>0 then 
        begin
            WriteLn('Wrong value of bit_wide');
            Out;
            Halt(0);
        end
    else 
    begin
        if (width>64) or (width<1) then
            begin
                WriteLn('Wrong value of bit_wide');
                Out;
                Halt(0);
            end;
    end;
    for j:=2 to ParamCount do
        begin
            inp:=ParamStr(j);
            Val(inp, base, err);
            if err<>0 then
                begin
                    WriteLn('Wrong value of number base');
                    Out;
                    Halt(0);
                end
            else
                begin
                    if (base>70) or (base<2) then
                        begin
                            WriteLn('Wrong value of number base');
                            Out;
                            Halt(0);
                        end
                    else 
                        begin
                            num_base_output[base]:=True;
                        end;
                end;
        end;
    repeat
        flag_skip:=False;
        flag_eoln:=False;
        c:=' ';
        Probel_reset(c);
        if not(flag_eoln) and not(flag_eof) then
            begin
            case c of
            '+': 
                begin
                    s:='+';
                    if not(flag_eoln and flag_eof) then
                        begin
                            Read(m);
                            s:=s+m;
                        end
                    else Konec('basis');
                    if (s='+ ') then operacia:='+'
                    else Konec('operator');
                end;
            '-':
                begin
                    s:='-';
                    if not(flag_eoln and flag_eof) then
                        begin
                            Read(m);
                            s:=s+m;
                        end
                    else Konec('basis');
                    if (s='- ') then operacia:='-'
                    else Konec('operator');
                end;
            '*': 
                begin
                    s:='*';
                    if not(flag_eoln and flag_eof) then
                        begin
                            Read(m);
                            s:=s+m;
                        end
                    else Konec('basis');
                    if (s='* ') then operacia:='*'
                    else Konec('operator');
                end;
            'd':
                begin
                    s:='d';
                    for i:=1 to 3 do 
                        begin
                            if not(flag_eoln and flag_eof) then
                                begin
                                    Read(m);
                                    s:=s+m;
                                end
                            else Konec('operator');
                        end;
                    if (s='div ') then operacia:='div'
                    else Konec('operator');
                end;
            'm': 
                begin
                    s:='m';
                    for i:=1 to 3 do 
                        begin
                            if not(flag_eoln and flag_eof) then
                                begin
                                    Read(m);
                                    s:=s+m;
                                end
                            else Konec('operator');
                        end;
                    if (s='mod ') then operacia:='mod'
                    else Konec('operator');
                end;
            'f':
                begin
                    s:='f';
                    for i:=1 to 6 do 
                        begin
                            if not(flag_eoln and flag_eof) then
                                begin
                                    Read(m);
                                    s:=s+m;
                                end
                            else Konec('operator');
                        end;
                    if ((s='finish ') or (s='finish;')) then Konec('finish')
                    else Konec('operator');
                end;
            ';':
                begin
                      flag_skip:=True;
                end;
            else Konec('operacia');
            end;
            end
        else
            begin
                if (flag_eof=True) then Konec('finish');
                if (flag_eoln=True) then flag_skip:=True;
            end;
            
        {
            получена операция
        }
        if not(flag_skip) then begin 
        c:=' ';
        Probel_reset(c);
        num_base:=0;
        if not(flag_eoln and flag_eof) then
            begin
                while not(eof) and (c<>':') and (num_base<100) do
                    begin 
                    if not(eoln) then 
                    begin
                        if (Proverka(c, 10) = True)
                        then num_base:=num_base*10+ord(c)-ord('0')
                        else Konec('basis');
                        Read(c);
                    end
                    else break;
                    end;
                if (num_base<2) or (num_base>70) then Konec('basis');
            end
        else
            begin
                if (flag_eof=True) then Konec('basis');
                if (flag_eoln=True) then Konec('basis');
            end;
        {
            получено основание системы счисления
        }
        bit_width:=0;
        if not(eof) then begin
        if not(eoln) and not(flag_skip) then
            begin
                Read(c); 
                if (Proverka(c, 10) = False) then Konec('bit')
                else 
                begin
                    bit_width:=bit_width*10+ord(c)-ord('0');
                    while not(eof) and (c<>':') and (bit_width<100) do 
                        begin
                            if not(eoln) then begin
                            Read(c);
                            if (Proverka(c, 10) = True)
                            then bit_width:=bit_width*10+ord(c)-ord('0')
                            else 
                                begin
                                    if (c=':') then break
                                    else Konec('bit');
                                end;
                            end
                            else break;
                        end;
                    if (bit_width<1) or (bit_width>64) then Konec('bit');
                end;
            end
        else Konec('bit');
        end 
        else Konec('bit');
        
        {
            получена ширина в битах
        }
        if not(eof) then begin
        if not(eoln) then
            begin
                number:=0;
                Read(c);
                if c='-' then 
                    begin
                        znak:='-';
                        if not(eof) then begin
                        if not(eoln) then
                        begin
                           Read(c);
                        end
                        else Konec('number');
                        end
                        else Konec('number');
                    end
                else znak:='+';
                while not(eof) 
                      and (c<>';') and (c<>' ') do 
                    begin
                        if not(eoln) then begin
                        if (Proverka(c, num_base) = True) then
                            begin
                                if (NAXVALUE - Findex(c)) div num_base < number then
                                    Konec('perepolnenie')
                                else
                                    number:=number*num_base + Findex(c);
                            end
                        else Konec('number');
                        Read(c);
                        end
                        else break;
                    end;
                if (c<>';') and (c<>' ') then
                    begin
                        if (Proverka(c, num_base) = True) then
                            begin
                                if (NAXVALUE - Findex(c)) div num_base < number then
                                    Konec('perepolnenie')
                                else
                                number:=number*num_base + Findex(c);
                            end
                        else Konec('number');
                    end;
            end
        else Konec('number');
        end
        else Konec('number');
        if (znak = '-') then number:=0-number;
        
        if (c = ' ') then 
            begin
                repeat
                    if not(eof) then begin 
                    if not(eoln) then Read(c)
                    else 
                        begin
                            if eoln then begin flag_eoln:=True; break; end
                        end;
                    end
                    else begin flag_eof:=True; break; end; 
                until c<>' ';
                if not(flag_eoln) and not(flag_eof) then
                    begin
                        if (c<>';') and (c<>' ') then Konec('number');
                    end
                else
                    if (flag_eof=True) then Konec('finish');
            end;
        
        {
            получено число
        }
        
        if Perepolnenie(number, bit_width) then Konec('perepolnenie');
        case operacia of 
            '+':
                begin
                    if (result < 0) and (number > 0) then
                        begin
                            if Perepolnenie(result+number, width) 
                            then Konec('perepolnenie');
                        end;
                    if (result < 0) and (number < 0) then
                        begin
                            if -Stepen(width)-1-number<result
                            then Konec('perepolnenie');
                        end;
                    if (result > 0) and (number > 0) then
                        begin
                            if Stepen(width)-number<result
                            then Konec('perepolnenie'); 
                        end;
                    if (result > 0) and (number < 0) then
                        begin
                            if Perepolnenie(result+number, width)  
                            then Konec('perepolnenie');
                        end;
                    if (result = 0) then 
                        begin
                            if Perepolnenie(number, width)
                            then Konec('perepolnenie')
                        end;
                    result:=result+number;
                end;
            '-':
                begin
                    if (result > 0) and (number >=0) then
                        begin
                            if Perepolnenie(result-number, width) 
                            then Konec('perepolnenie');
                        end;
                    if (result < 0) and (number > 0) then
                        begin
                            if -Stepen(width)-1+number>result
                            then Konec('perepolnenie');
                        end;
                    if (result > 0) and (number < 0) then
                        begin
                            if Stepen(width)-result<-number
                            then Konec('perepolnenie');
                        end;
                    if (result < 0) and (number < 0) then
                        begin
                            if -Stepen(width)-1+result>number  
                            then Konec('perepolnenie');
                        end;
                    if (result = 0) then
                        begin
                            if Perepolnenie(-number, width)  
                            then Konec('perepolnenie');
                        end;
                    result:=result-number;
                end;
            '*':
                begin
                    if (number = 0) or (result = 0) then 
                        begin
                            if Perepolnenie(number, width) 
                            then Konec('perepolnenie')
                            else result:=0;
                        end;
                    if (result > 0) and (number > 0) then
                        begin
                            if (Stepen(width)/number<result) 
                            then Konec('perepolnenie');
                        end;
                    if (result < 0) and (number > 0) then
                        begin
                            if (-Stepen(width)-1)/number>result
                            then Konec('perepolnenie');
                        end;
                    if (result > 0) and (number < 0) then
                        begin
                            if (-Stepen(width)-1)/number<result
                            then Konec('perepolnenie');
                        end;
                    if (result < 0) and (number < 0) then
                        begin
                            if (Stepen(width)/number>result)  
                            then Konec('perepolnenie');
                        end;
                    result:=result*number;
                end;
            'div': 
                begin
                    if (number = 0) then
                        begin
                            WriteLn('impossible operation');
                            Out;
                            Halt(0);
                        end;
                    if Perepolnenie(result div number, width)
                    then Konec('perepolnenie');
                    result:=result div number
                end;
            'mod':
                begin
                    if (number = 0) then
                        begin
                            WriteLn('impossible operation');
                            Out;
                            Halt(0);
                        end;
                    if Perepolnenie(result mod number, width)
                    then Konec('perepolnenie');
                    result:=result mod number;
                end;
        end;
        end;
        if not(eof) then ReadLn;
    until eof;
    Konec('finish');
end.