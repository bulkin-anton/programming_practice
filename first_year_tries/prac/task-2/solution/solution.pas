{
    Блок создания типов данных
}

{
    Запись с описанием одной дороги в графе
}
type 
    Cost_time_t = record
    cost :LongInt;
    time :LongInt;
end;

type 
    City_trans_t = record
    city :string;
    trans :string;
end;

type 
    Graph3_t = record
    cost :LongInt;
    time :LongInt;
    cities :integer;
    way :array of City_trans_t;
end;

type Transportation= record
    c_from :string;
    c_to :string;
    tr_type :string;
end;

type 
    Graph_t = record
    cost :LongInt;
    time :LongInt;
    way :array of City_trans_t;
end;

type 
    Way = record

    {
        Город отправления
    }
    c_from :string;

    {
        Город прибытия
    }
    c_to :string;

    {
        Тип транспорта
    }
    tr_type :string;

    {
        Время до пункта назначения
    }

    c_time :LongInt;

    {
        Цена поездки
    }
    c_fare :LongInt;
end;

{
    Создание типа основного массива с данными
}
type 
    Mas = array of Way;

{
    Блок инициализации переменных
}

var
    {
        Переменные счетчики циклов
    }
    i :integer;
    
    {
        Счетчик считанных линий из файла
    }
    line :integer;
    
    {
        Имя файла для считывания из параметров программы
    }
    name_of_file :string;

    {
        Переменная для сбора города отправления из файла
    }
    from_city :string;
    
    
    option :string;

    {
        Переменная для сбора города прибытия из файла
    }
    to_city :string;

    {
        Переменная для сбора типа транспорта из файла
    }
    trans_type :string;
    
    
    city_start :string;
    
    
    city_end :string;

    {
        Переменные для посимвольного ввода из файла
    }
    s :string;
    c :char;
    m :char;
    d :char;

    {
        Флаг проверки на конец строки
    }
    flag_eoln :boolean;
    
    flag_end :boolean;
    
    error :boolean;
    
    flag_wrong_input :boolean;

    {
        Флаг проверки на конец файла
    }
    flag_eof :boolean;

    {
        Флаг проверки времени из файла
    }
    flag_time :boolean;

    {
        Флаг проверки стоимости пути из файла
    }
    flag_fare :boolean;
    flag_num :boolean;

    {
        Переменная-файл для считывания графа
    }
    f : text;

    {
        Переменная для сбора времени из файла
    }
    cruise_time :LongInt;
    limit :LongInt;

    {
        Переменная для сбора стоимости поездки из файла
    }
    cruise_fare :LongInt;

    {
        Запись для объеденения одного пути графа
    }
    Poesdka :Way;

    {
        Общий двумерный массив для распределения записей
        по вершинам и создания графа
    }
    Usel :array of Mas;
    
    cities :array of string;
    
    transport :array of string;
    
    trans_want :array of string;

{
    Блок процедур
}

{
    Процедура для избавления от пробельных символов в файле
}

procedure Probel_reset(var c:char);
begin
    repeat 
    if not(eof(f)) then 
        begin
            if not(eoln(f)) then Read(f, c)
            else 
                begin
                    if eoln(f) then begin flag_eoln:=True; break; end;
                end;
        end
    else begin flag_eof:=True; break; end;
    until c<>' ';
end;

procedure Probels(var c:char);
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

function Find(name :string; var mas :array of string): boolean;
var i :integer;
begin
    if Length(mas)>0 then
    begin
        for i:=0 to High(mas) do
        begin
            if (mas[i] = name) then
            begin
                Find:= True;
                Exit;
            end;
        end;
    end;
    Find:= False;
end;

procedure Trans_use;
var num :LongInt;
    trans_no :array of integer;
    i, j, k :integer;
begin
    SetLength(trans_no, 0);
    flag_num:= False;
    SetLength(trans_want, 0);
    WriteLn('Выберите транспорт, которым не желаете воспользоваться');
    WriteLn('Необходимо напечатать только цифры в строчку через пробел');
    WriteLn('Если возможно использовать весь транспорт напишите "0"');
    for i:=0 to High(transport) do
    begin
        WriteLn(i+1, ' ', '-', ' ', transport[i]);
    end;
    if not(eof) then ReadLn
    else
    begin
        WriteLn('Поток ввода завершился');
        Halt(0);
    end;
    flag_eoln:=True;
    while flag_eoln do
    begin
        flag_eoln:=False;
        Probels(d);
        if flag_eoln then
        begin
            if (eof) then
            begin
                WriteLn('Поток ввода завершился');
                Halt(0);
            end
            else ReadLn;
        end;
    end;
    while not(flag_eoln) do
    begin
        if (d>='0') and (d<='9') and
        not(flag_eoln) then
        begin
            num:=0;
            while (d<>' ') do
            begin
                num:=num*10-ord('0')+ord(d);
                if (num>Length(transport)) then
                begin
                    WriteLn('Слишком большое число');
                    flag_num:=True;
                    Exit;
                end;
                if not(eoln) then Read(d)
                else Break;
                if not((d>='0') and (d<='9')) and
                (d<>' ') then
                begin
                    WriteLn('Wrong number');
                    flag_num:=True;
                    Exit;
                end;
            end;
            SetLength(trans_no, Length(trans_no)+1);
            trans_no[High(trans_no)]:= num;
            flag_eoln:= False;
            Probels(d);
            if eoln then
            begin
                if (d>='0') and (d<='9') and
                ((-ord('0')+ord(d))<>num) then
                begin
                    num:= -ord('0')+ord(d);
                    SetLength(trans_no, Length(trans_no)+1);
                    trans_no[High(trans_no)]:= num;
                end;
                Break;
            end;
        end
        else
        begin
            if not(flag_eoln) then
            begin
                WriteLn('Wrong number');
                flag_num:=True;
                Exit;
            end;
        end;
    end;
    if (Length(trans_no)>0) then
    begin
        for i:=0 to High(trans_no) do
        if (trans_no[i] = 0) then num:= 0;
    end;
    if (num<>0) then
    begin
        if (Length(trans_no) = Length(transport)) then
        begin
            WriteLn('Не существует доступного транспорта');
            flag_num:= True;
            Exit;
        end;
        for i:=0 to High(transport) do
        begin
            k:=0;
            for j:=0 to High(trans_no) do
            begin
                if (trans_no[j] <> i+1) then k:=k+1;
            end;
            if (k = Length(trans_no)) then
            begin
                SetLength(trans_want, Length(trans_want)+1);
                trans_want[High(trans_want)]:= transport[i];
            end;
        end;
    end
    else trans_want:= transport;
end;

{
    Процедура добавления в общий массив
    по городу отправления
}
Procedure Dobavit(Psdk :Way);
var i:integer;
begin
    if (Length(Usel)>0) then
    begin
        for i:=0 to High(Usel) do
        begin
            if (Psdk.c_from = Usel[i][0].c_from) then
                begin
                    SetLength(Usel[i], Length(Usel[i])+1);
                    Usel[i][High(Usel[i])]:= Psdk;
                    Exit;
                end;
        end;
    end;    
    SetLength(Usel, Length(Usel)+1);
    SetLength(Usel[High(Usel)], 1);
    Usel[High(Usel)][0]:= Psdk;
end;

function Start_index(s :string): integer;
var i:integer;
begin
    for i:=0 to High(cities) do
    begin
        if (cities[i] = s) then
        begin
            Start_index:=i;
            Break;
        end;
    end;
end;

Procedure Vvod_1;
var i :integer;
    d :char;
    s :string;
begin
    if not(eof) then ReadLn
    else
    begin
        WriteLn('Wrong input of cities');
        Halt(0);
    end;
    flag_wrong_input:= False;
    WriteLn('Введите город отправления и город прибытия');
    WriteLn('Формат: "город отправления" "город прибытия"');
    flag_eoln:=True;
    while flag_eoln do
    begin
        flag_eoln:= False;
        Probels(d);
        if flag_eof or eof then
        begin
                WriteLn('Wrong input of cities');
                Halt(0);
        end;
        if flag_eoln and not(eof) then ReadLn;
    end;
    if (d<>'"') then
    begin
        WriteLn('Неправильный город отправления');
        WriteLn;
        ReadLn;
        flag_wrong_input:= True;
        Exit;
    end
    else
    begin
        for i:=1 to 2 do
        begin
            s:='';
            if not(eoln) then
            begin
                Read(d);
                s:= s+d;
                while (d<>'"') and (Length(s)<255) do
                begin
                    if not(eoln) then Read(d)
                    else Break;
                    if (d<>'"') then s:= s+d;
                end;
                if (d<>'"') then
                begin
                    WriteLn('Wrong input');
                    WriteLn;
                    flag_wrong_input:= True;
                    Break;
                end;
                if eoln and (i=1) then
                begin
                    WriteLn('Wrong input');
                    WriteLn;
                    flag_wrong_input:= True;
                    Break;
                end;
                if (i=1) then
                begin
                    city_start:= s;
                    Probels(d);
                    if (d<>'"') or flag_eoln then
                    begin
                        WriteLn('Wrong input');
                        WriteLn; 
                        flag_wrong_input:= True;
                        Break;
                    end;
                end
                else
                begin
                    city_end:=s;
                    if not(eoln) then
                    begin
                        Probels(d);
                        if not(flag_eoln) then
                        begin
                            WriteLn('Wrong input');
                            WriteLn; 
                            flag_wrong_input:= True;
                            Break;
                        end;
                    end;
                end;
            end
            else
            begin
                WriteLn('Wrong input');
                WriteLn; 
                flag_wrong_input:= True;
                Break;    
            end;
        end;
        if flag_wrong_input then
        begin
            ReadLn;
            Exit;
        end;
    end;
end;


procedure Vvod_2;
var flag_done :boolean;
    d :char;
    s :string;
begin
    if not(eof) then ReadLn
    else
    begin
        WriteLn('Wrong input of cities');
        Halt(0);
    end;
    flag_wrong_input:= False;
    WriteLn('Введите город отправления и ограничение');
    WriteLn('Формат: "город отправления" limit');
    flag_eoln:=True;
    while flag_eoln do
    begin
        flag_eoln:= False;
        Probels(d);
        if flag_eof or eof then
        begin
            WriteLn('Wrong input of cities');
            Halt(0);
        end;
        if flag_eoln and not(eof) then ReadLn;
    end;
    if (d<>'"') then
    begin
        WriteLn('Неправильный город отправления');
        WriteLn;
        ReadLn;
        flag_wrong_input:= True;
        Exit;
    end
    else
    begin
        s:='';
        if not(eoln) then
        begin
            Read(d);
            s:= s+d;
            while (d<>'"') and (Length(s)<255) do
            begin
                if not(eoln) then Read(d)
                else Break;
                if (d<>'"') then s:= s+d;
            end;
            if (d<>'"') then
            begin
                WriteLn('Wrong input');
                WriteLn;
                flag_wrong_input:= True;
            end;
            if eoln then
            begin
                WriteLn('Wrong input');
                WriteLn;
                flag_wrong_input:= True;
            end;
            city_start:=s;
            Probels(d);
            if not(flag_eoln) then
            begin
                limit:=0;
                flag_done:= False;
                while not(eoln) and (d>='0') and (d<='9') do
                begin
                    limit:=limit*10-ord('0')+ord(d);
                    flag_done := True;
                    if not(eoln) then Read(d);
                end;
                if (d>='0') and (d<='9') then
                begin
                    limit:=limit*10-ord('0')+ord(d);
                    flag_done := True;
                end;
                if ((not(flag_done)) or (d<'0') or 
                (d>'9')) and (d<>' ') then
                begin
                    WriteLn('Wrong input');
                    WriteLn;
                    flag_wrong_input:= True;
                end;
                if (d=' ') then
                begin
                    Probels(d);
                    if (d<>' ') then
                    begin
                        WriteLn('Wrong input');
                        WriteLn;
                        flag_wrong_input:= True;
                    end;
                end;
            end
            else
            begin
                WriteLn('Wrong input');
                WriteLn;
                flag_wrong_input:= True;  
            end;
        end
        else
        begin
            WriteLn('Wrong input');
            WriteLn; 
            flag_wrong_input:= True;   
        end;
    end;
    if flag_wrong_input then 
    begin  
        ReadLn;
        Exit;
    end;
end;


function Index(v:integer): integer;
var s:string;
    i:integer;
begin
    s:= cities[v];
    for i :=0 to High(Usel) do
    begin
        if (Usel[i][0].c_from = s) then
        begin
            Index:= i;
            Exit;
        end;
    end;
    Index:=-1;
end;

procedure D2(c_st, c_end :string);

var a :array of integer;
    v, s :LongInt;
    d :array of Graph_t;
    way :array of City_trans_t;
    i, j, n, l :integer;

begin
    SetLength(a, Length(cities));
    SetLength(d, Length(cities));
    for i := 0 to High(cities) do
    begin
        a[i]:= 0;
        d[i].cost:= -1;
        d[i].time:= 0;
    end;
    d[Start_index(c_st)].cost:= 0;
    for j:= 0 to High(d) do
    begin
    	v:=-1;
    	for i:= 0 to High(d) do
    	begin
        	if (d[i].cost>=0) then
        	begin
            	if (v<>-1) then
            	begin
            	    if (d[v].cost>d[i].cost) and (a[i] = 0) then
            	    begin
                	    v:=i;
            	    end;
            	end
            	else if (a[i] = 0) then v:=i;
        	end;
    	end;
    	if (v = -1) then Break;
    	a[v]:=1;
    	l:=Index(v);
    	if (l<>-1) then
        begin
    	    for i:=0 to High(Usel[l]) do
    	    begin
        	    if ((Usel[l][i].c_fare + d[v].cost < d[Start_index(Usel[l][i].c_to)].cost)
        	    or (d[Start_index(Usel[l][i].c_to)].cost = -1)) and
        	    Find(Usel[l][i].tr_type, trans_want) then
        	    begin
                    d[Start_index(Usel[l][i].c_to)].cost:= Usel[l][i].c_fare + d[v].cost;
            	    d[Start_index(Usel[l][i].c_to)].time:= Usel[l][i].c_time + d[v].time;
            	    SetLength(d[Start_index(Usel[l][i].c_to)].way, 1);
            	    d[Start_index(Usel[l][i].c_to)].way[0].city:= Usel[l][i].c_from;
            	    d[Start_index(Usel[l][i].c_to)].way[0].trans:= Usel[l][i].tr_type;
        	    end;
    	    end;
    	end;
    end;
    WriteLn;
    if (d[Start_index(c_end)].cost = -1) then
    begin
        WriteLn('Данный город недостижим из точки отправления');
    end
    else
    begin
        s:= Start_index(c_end);
        n:=s;
        SetLength(way, 0);
        SetLength(way, Length(way)+1);
        for i:=High(way) downto 0 do
        begin
    	    way[High(way)].city:=d[n].way[i].city;
    	    way[High(way)].trans:=d[n].way[i].trans;
    	end;
    	while (n<>Start_index(c_st)) do
    	begin
    	    n:= Start_index(d[n].way[0].city);
    	    if (n = Start_index(c_st)) then Break;
            SetLength(way, Length(way)+1);
    	    way[High(way)].city:=d[n].way[0].city;
    	    way[High(way)].trans:=d[n].way[0].trans;
    	end;
       	WriteLn;
        Write(d[s].time);
        Write(' ');
        Write(d[s].cost);
        Write(' ');
        for i:=High(way) downto 0 do
        begin
            Write(way[i].city);
            Write(' ');
            Write('--(');
            Write(way[i].trans);
            Write(')-> ');
            Write(' ');
        end;
        Write(c_end);
        WriteLn;
    end;
    WriteLn;
end;




procedure D1(c_st, c_end :string);

var a :array of integer;
    v, s :LongInt;
    d :array of Graph_t;
    way :array of City_trans_t;
    i, j, n, l :integer;

begin
    SetLength(a, Length(cities));
    SetLength(d, Length(cities));
    for i := 0 to High(cities) do
    begin
        a[i]:= 0;
        d[i].cost:= 0;
        d[i].time:= -1;
    end;
    d[Start_index(c_st)].time:= 0;
    for j:= 0 to High(d) do
    begin
    	v:=-1;
    	for i:= 0 to High(d) do
    	begin
        	if (d[i].time>=0) then
        	begin
            	if (v<>-1) then
            	begin
            	    if (d[v].time>d[i].time) and (a[i] = 0) then
                  	begin
                    	v:=i;
                	end;
            	end
            	else if (a[i] = 0) then v:=i;
        	end;
    	end;
    	if (v = -1) then Break;
    	a[v]:=1;
    	l := Index(v);
    	if (l<>-1) then
    	begin
    	    for i:=0 to High(Usel[Index(v)]) do
    	    begin
        	    if (((Usel[l][i].c_time + d[v].time < d[Start_index(Usel[l][i].c_to)].time) or
        	    (d[Start_index(Usel[l][i].c_to)].time = -1)) or
        	    ((Usel[l][i].c_time + d[v].time = d[Start_index(Usel[l][i].c_to)].time) and 
        	    (Usel[l][i].c_fare + d[v].cost < d[Start_index(Usel[l][i].c_to)].cost))) and
        	    Find(Usel[l][i].tr_type, trans_want) then
        	    begin
                    if ((Usel[l][i].c_time + d[l].time < d[Start_index(Usel[l][i].c_to)].time) 
        	        or (d[Start_index(Usel[l][i].c_to)].time = -1)) then
                    begin
                        d[Start_index(Usel[l][i].c_to)].cost:= Usel[l][i].c_fare + d[v].cost;
            	        d[Start_index(Usel[l][i].c_to)].time:= Usel[l][i].c_time + d[v].time;
            	        SetLength(d[Start_index(Usel[l][i].c_to)].way, 1);
            	        d[Start_index(Usel[l][i].c_to)].way[0].city:= Usel[l][i].c_from;
            	        d[Start_index(Usel[l][i].c_to)].way[0].trans:= Usel[l][i].tr_type;
        	        end
        	        else
        	        begin
        	            if (Usel[l][i].c_fare + d[v].cost < d[Start_index(Usel[l][i].c_to)].cost) then
        	            begin
        	                d[Start_index(Usel[l][i].c_to)].cost:= Usel[l][i].c_fare + d[v].cost;
            	            d[Start_index(Usel[l][i].c_to)].time:= Usel[l][i].c_time + d[v].time;
            	            SetLength(d[Start_index(Usel[l][i].c_to)].way, 1);
            	            d[Start_index(Usel[l][i].c_to)].way[0].city:= Usel[l][i].c_from;
            	            d[Start_index(Usel[l][i].c_to)].way[0].trans:= Usel[l][i].tr_type;
        	            end;
        	        end;
        	    end;
    	    end;
    	end;
    end;
    WriteLn;
    if (d[Start_index(c_end)].cost = -1) then
    begin
        WriteLn('Данный город недостижим из точки отправления');
    end
    else
    begin
        s:= Start_index(c_end);
        n:=s;
        SetLength(way, 0);
        SetLength(way, Length(way)+1);
        for i:=High(way) downto 0 do
        begin
    	    way[High(way)].city:=d[n].way[i].city;
    	    way[High(way)].trans:=d[n].way[i].trans;
    	end;
    	while (n<>Start_index(c_st)) do
    	begin
    	    n:= Start_index(d[n].way[0].city);
    	    if (n = Start_index(c_st)) then Break;
            SetLength(way, Length(way)+1);
    	    way[High(way)].city:=d[n].way[0].city;
    	    way[High(way)].trans:=d[n].way[0].trans;
    	end;
        Write(d[s].time);
        Write(' ');
        Write(d[s].cost);
        Write(' ');
        for i:=High(way) downto 0 do
        begin
            Write(way[i].city);
            Write(' ');
            Write('--(');
            Write(way[i].trans);
            Write(')-> ');
            Write(' ');
        end;
        Write(c_end);
        WriteLn;
    end;
    WriteLn;
end;

procedure D3(c_start, c_end :string);
var p :array of Transportation;
    q :array of integer;
    d :array of Graph3_t;
    s, i, v, k:integer;
    way :array of Transportation;

begin
    SetLength(q, 1);
    SetLength(way, 0);
    s:= Start_index(c_start);
    q[0]:= s;
    SetLength(d, Length(cities));
    SetLength(p, Length(cities));
    for i:=0 to High(cities) do
    begin
        d[i].cost := 0;
        d[i].time := 0;
        d[i].cities := -1;
    end;
    d[s].cities:= 0;
    while (Length(q)<>0) do
    begin
        v:= q[0];
        if (Length(q)>1) then
        for i:=0 to High(q)-1 do q[i]:= q[i+1];
        SetLength(q, Length(q)-1);
        if (Index(v)<>-1) then
        begin
            for i:=0 to High(Usel[Index(v)]) do
            begin
                if (d[Start_index(Usel[Index(v)][i].c_to)].cities = -1) and
                   (Find(Usel[Index(v)][i].tr_type, trans_want)) then
                begin
                    SetLength(q, Length(q)+1);
                    q[High(q)]:= Start_index(Usel[Index(v)][i].c_to);
                    d[Start_index(Usel[Index(v)][i].c_to)].cost:= d[v].cost + Usel[Index(v)][i].c_fare;
                    d[Start_index(Usel[Index(v)][i].c_to)].time:= d[v].time + Usel[Index(v)][i].c_time;
                    d[Start_index(Usel[Index(v)][i].c_to)].cities:= d[v].cities + 1;
                    p[Start_index(Usel[Index(v)][i].c_to)].c_from:= Usel[Index(v)][i].c_from;
                    p[Start_index(Usel[Index(v)][i].c_to)].c_to:= Usel[Index(v)][i].c_to;
                    p[Start_index(Usel[Index(v)][i].c_to)].tr_type:= Usel[Index(v)][i].tr_type;
                end;
            end;
        end;
    end;
    k:=Start_index(c_end);
    if (d[k].cities = -1) then
    begin
        WriteLn;
        WriteLn('Данный город недостижим из точки отправления');
        WriteLn;
        Exit;
    end;
    while (k <> Start_index(c_start)) do
    begin
        SetLength(way, Length(way)+1);
        way[High(way)].c_from := p[k].c_from;
        way[High(way)].c_to := p[k].c_to;
        way[High(way)].tr_type := p[k].tr_type;
        k := Start_index(p[k].c_from);
    end;
    WriteLn;
    Write(d[Start_index(c_end)].time, ' ', d[Start_index(c_end)].cost, ' ');
    Write(Usel[Index(k)][0].c_from);
    for i:=High(way) downto 0 do
    begin
        Write(' --(', way[i].tr_type, ')-> ', way[i].c_to);
    end;
    WriteLn;
    WriteLn;
end;




procedure D4(c_start: string; limit :LongInt);

var a :array of integer;
    v :LongInt;
    d :array of Graph_t;
    i, j, l, k :integer;

begin
    SetLength(a, Length(cities));
    SetLength(d, Length(cities));
    for i := 0 to High(cities) do
    begin
        a[i]:= 0;
        d[i].cost:= -1;
        d[i].time:= 0;
    end;
    d[Start_index(c_start)].cost:= 0;
    for j:= 0 to High(d) do
    begin
    	v:=-1;
    	for i:= 0 to High(d) do
    	begin
        	if (d[i].cost>=0) then
        	begin
            	if (v<>-1) then
            	begin
            	    if (d[v].cost>d[i].cost) and (a[i] = 0) then
            	    begin
                	    v:=i;
            	    end;
            	end
            	else if (a[i] = 0) then v:=i;
        	end;
    	end;
    	if (v = -1) then Break;
    	a[v]:=1;
    	l:=Index(v);
    	if (l<>-1) then
        begin
    	    for i:=0 to High(Usel[l]) do
    	    begin
        	    if ((Usel[l][i].c_fare + d[v].cost < d[Start_index(Usel[l][i].c_to)].cost)
        	    or (d[Start_index(Usel[l][i].c_to)].cost = -1)) and
        	    Find(Usel[l][i].tr_type, trans_want) then
        	    begin
                    d[Start_index(Usel[l][i].c_to)].cost:= Usel[l][i].c_fare + d[v].cost;
            	    d[Start_index(Usel[l][i].c_to)].time:= Usel[l][i].c_time + d[v].time;
        	    end;
    	    end;
    	end;
    end;
    WriteLn;
    k:=0;
    for i:=0 to High(d) do
    begin
        if (d[i].cost < limit) and (d[i].cost > 0) then
        begin
            WriteLn(cities[i], ' Cost: ', d[i].cost, ' Time: ', d[i].time);
        end
        else k:= k+1;
    end;
    if (k = Length(d)) then WriteLn('Таких городов нет');
    WriteLn;
end;


procedure D5(c_start: string; limit :LongInt); 

var a :array of integer;
    v :LongInt;
    d :array of Graph_t;
    i, j, l, k :integer;

begin
    SetLength(a, Length(cities));
    SetLength(d, Length(cities));
    for i := 0 to High(cities) do
    begin
        a[i]:= 0;
        d[i].cost:= 0;
        d[i].time:= -1;
    end;
    d[Start_index(c_start)].time:= 0;
    for j:= 0 to High(d) do
    begin
    	v:=-1;
    	for i:= 0 to High(d) do
    	begin
        	if (d[i].time>=0) then
        	begin
            	if (v<>-1) then
            	begin
            	    if (d[v].time>d[i].time) and (a[i] = 0) then
            	    begin
                	    v:=i;
            	    end;
            	end
            	else if (a[i] = 0) then v:=i;
        	end;
    	end;
    	if (v = -1) then Break;
    	a[v]:=1;
    	l:=Index(v);
    	if (l<>-1) then
        begin
    	    for i:=0 to High(Usel[l]) do
    	    begin
        	    if ((Usel[l][i].c_time + d[v].time < d[Start_index(Usel[l][i].c_to)].time)
        	    or (d[Start_index(Usel[l][i].c_to)].time = -1)) and
        	    Find(Usel[l][i].tr_type, trans_want) then
        	    begin
                    d[Start_index(Usel[l][i].c_to)].cost:= Usel[l][i].c_fare + d[v].cost;
            	    d[Start_index(Usel[l][i].c_to)].time:= Usel[l][i].c_time + d[v].time;
        	    end;
    	    end;
    	end;
    end;
    WriteLn;
    k:=0;
    for i:=0 to High(d) do
    begin
        if (d[i].time < limit) and (d[i].time > 0) then
        begin
            WriteLn(cities[i], ' Cost: ', d[i].cost, ' Time: ', d[i].time);
        end
        else k:= k+1;
    end;
    if (k = Length(d)) then WriteLn('Таких городов нет');
    WriteLn;
end;

{
    Начало программы
}
begin
    {
        Получение и проверка имении файла
        с графом из параметров программы
    }
    if (ParamCount <> 1) then
    begin
        WriteLn('Not enough values to start a programm');
        Halt(0);
    end
    else name_of_file:= ParamStr(1);
    Assign(f, name_of_file);
    {$I-}
    Reset(f);
    {$I+}
    if (IOResult <> 0) then
    begin
        WriteLn('Such file doesn`t exist');
        Halt(0);
    end;
    line:=0;
    
    {
        Считывание графа из файла
    }
    SetLength(cities, 0);
    SetLength(transport, 0);
    while not(eof(f)) do
    begin
        flag_eoln:= False;
        line:= line+1;
        Probel_reset(c);
        if (flag_eof) then
        begin
            WriteLn('No data found in file');
            Halt(0);
        end;
        if not(flag_eoln) then {условие на пустую строку}
        begin
            from_city:= '';
            to_city:= '';
            trans_type:= '';
            cruise_time:= 0;
            cruise_fare:= 0;
            flag_time:= False;
            flag_fare:= False;
            case c of
                '#': line:=line; {Строка комментарий}
                '"':
                begin
                    for i:=1 to 3 do
                    begin
                        s:='';
                        m:=' ';
                        while not(eoln(f)) and (m<>chr(34)) and (Length(s) < 255) do
                        begin
                            if not(eoln(f)) then Read(f, m);
                            if (m<>chr(34)) then s:= s + m;
                        end;
                        case i of
                            1: {Находим город отправления}
                            begin
                                if not(eoln(f)) then
                                begin
                                    from_city:= s;
                                end
                                else
                                begin
                                    WriteLn('Wrong from_city', ', line ', line);
                                    Halt(0);
                                end;
                            end;
                            2: {Находим город назначения}
                            begin
                                if not(eoln(f)) then
                                begin
                                    to_city:= s;
                                end
                                else
                                begin
                                    WriteLn('Wrong to_city', ', line ', line);
                                    Halt(0);
                                end;
                            end;
                            3: {Находим тип транспорта}
                            begin
                                if not(eoln(f)) then
                                begin
                                    trans_type:= s;
                                end
                                else
                                begin
                                    WriteLn('Wrong trans_type', ', line ', line);
                                    Halt(0);
                                end;
                            end;
                        end;
                        {Условия на пробелы между данными}
                        if not(eoln(f)) then Read(f, d);
                        if (d=' ') then
                        begin
                            Probel_reset(d);
                            if (i<>3) then
                            begin {Условие на конец string данных}
                                if (flag_eoln) or (d<>chr(34)) then
                                begin
                                    WriteLn('Wrong input', ', line ', line);
                                    Halt(0);
                                end;
                            end
                            else
                            begin
                                if (flag_eoln) or (d<'0') or (d>'9') then
                                begin
                                    WriteLn('Wrong input', ', line ', line);
                                    Halt(0);
                                end;
                            end;
                        end
                        else
                        begin
                            WriteLn('Wrong input', ', line ', line);
                            Halt(0);
                        end;
                    end;
                    {Находим Cruise_time}
                    while (d<>' ') and not(eoln(f)) do
                    begin
                        flag_time:=True;
                        if (d >= '0') and (d <= '9') then
                        begin
                            cruise_time:= cruise_time*10 + (ord(d)-ord('0'))
                        end
                        else
                        begin
                            WriteLn('Wrong cruise_time', ', line ', line);
                            Halt(0);
                        end;
                        if not(eoln(f)) then Read(f, d)
                        else
                        begin
                            WriteLn('Wrong input', ', line ', line);
                            Halt(0);
                        end;
                    end;
                    if (cruise_time = 0) then
                    begin
                        WriteLn('Wrong cruise_time', ', line ', line);
                        Halt(0);
                    end;
                    Probel_reset(d);
                    {Условие на пробелы между cruise_time и cruise_fare}
                    if (flag_eoln) then
                    begin
                        WriteLn('Wrong input', ', line ', line);
                        Halt(0);
                    end;
                    {Находим cruise_fare}
                    while (d<>' ') and not(eoln(f)) do
                    begin
                        flag_fare:=True;
                        if (d >= '0') and (d <= '9') then
                        begin
                            cruise_fare:= cruise_fare*10 + (ord(d)-ord('0'))
                        end
                        else
                        begin
                            WriteLn('Wrong cruise_fare', ', line ', line);
                            Halt(0);
                        end;
                        if not(eoln(f)) then Read(f, d);
                    end;
                    if eoln(f) and (d>='0') and (d<='9') then 
                    begin
                        cruise_fare:= cruise_fare*10 + (ord(d)-ord('0'));
                        flag_fare:= True;
                    end;
                    {Проверка на правильность конца строки}
                    Probel_reset(d);
                    if not((c<>'#') or (flag_eoln)) then
                    begin
                        WriteLn('Wrong input', ', line ', line);
                        Halt(0);
                    end;
                    if not(flag_time) or not(flag_fare) then
                    begin
                        WriteLn('Wrong input', ', line ', line);
                        Halt(0);
                    end;
                    if not(Find(from_city, cities)) then
                    begin
                        SetLength(cities, Length(cities)+1);
                        cities[High(cities)]:= from_city;
                    end;
                    if not(Find(to_city, cities)) then
                    begin
                        SetLength(cities, Length(cities)+1);
                        cities[High(cities)]:= to_city;
                    end;
                    if not(Find(trans_type, transport)) then
                    begin
                        SetLength(transport, Length(transport)+1);
                        transport[High(transport)]:= trans_type;
                    end;
                    {Создание record с данными}
                    with Poesdka do
                    begin
                        c_from:= from_city;
                        c_to:= to_city;
                        tr_type:= trans_type;
                        c_time:= cruise_time;
                        c_fare:= cruise_fare;
                    end;
                    {Добавление данных в общий массив по городам}
                    Dobavit(Poesdka);
                    {данные получены}
                end;
                {Проверка на другие символы в начале строки}
                else
                begin
                    WriteLn('Wrong input', ', line ', line);
                    Halt(0);
                end;
            end;
        end;
        {Переход на новую строку}
        if not(eof(f)) then ReadLn(f);
    end;
    {Закрываем исходный файл с графом}
    Close(f);
    {
        Начало диалового интерфейса с пользователем
    }
    flag_end:= False;
    error:= False;
    repeat
        option:='';
        error:= False;
        flag_eof:= False;
        flag_eoln:= True;
        WriteLn('В каком режиме вы хотите начать работу?');
        WriteLn('Вам будет необходимо напечатать только цифру');
        WriteLn('1 - Найти из кратчайших путей путь минимальной стоимости между двумя городами');
        WriteLn('2 - Найти путь минимальной стоимости между двумя городами');
        WriteLn('3 - Найти путь между двумя городами с минимальным количеством пройденных городов');
        WriteLn('4 - Найти множество городов, достижимых менее чем за ... денег');
        WriteLn('5 - Найти множество городов, достижимых менее чем за ... времени');
        WriteLn('exit - чтобы закончить программу');
        while flag_eoln do
        begin
            flag_eoln:= False;
            Probels(d);
            if flag_eof then
            begin
                WriteLn('Команды не последовало');
                Halt(0);
            end;
            if flag_eoln then ReadLn;
        end;
        flag_eoln:= False;
        s:='';
        case d of
            'e':
            begin
                s:='e';
                for i:=1 to 3 do
                begin
                    if not(eoln) then Read(m)
                    else
                    begin
                        error:= True;
                        Break;
                    end;
                    s:= s+m; 
                end;
                if not(eoln) then
                begin
                    Read(m);
                    s:= s+m;
                end;
                if not(error) then
                begin
                    if (s='exit ') or (s='exit') then option:='end_of_programm'
                    else error:= True;
                end;
                Probels(m);
                if not(flag_eoln) then error:= True;
            end;
            '1':
            begin
                s:='1';
                if not(eoln) then
                begin
                    Read(m);
                    s:= s+m;
                end;
                if (s='1 ') or (s='1') then option:='1'
                else error:= True;
                Probels(m);
                if not(flag_eoln) then error:= True;
            end;
            '2':
            begin
                s:='2';
                if not(eoln) then
                begin
                    Read(m);
                    s:= s+m;
                end;
                if (s='2 ') or (s='2') then option:='2'
                else error:= True;
                Probels(m);
                if not(flag_eoln) then error:= True;
            end;
            '3':
            begin
                s:='3';
                if not(eoln) then
                begin
                    Read(m);
                    s:= s+m;
                end;
                if (s='3 ') or (s='3') then option:='3'
                else error:= True;
                Probels(m);
                if not(flag_eoln) then error:= True;
            end;
            '4':
            begin
                s:='4';
                if not(eoln) then
                begin
                    Read(m);
                    s:= s+m;
                end;
                if (s='4 ') or (s='4') then option:='4'
                else error:= True;
                Probels(m);
                if not(flag_eoln) then error:= True;
            end;
            '5':
            begin
                s:='5';
                if not(eoln) then
                begin
                    Read(m);
                    s:= s+m;
                end;
                if (s='5 ') or (s='5') then option:='5'
                else error:= True;
                Probels(m);
                if not(flag_eoln) then error:= True;
            end;
            else error:=True;
        end;
        if error then
        begin
            WriteLn;
            WriteLn('Ошибка при выборе режима работы. Повторите попытку');
            WriteLn;
            ReadLn;
            Continue;
        end;
        if (option<>'end_of_programm') then
        begin
            Trans_use;
            if flag_num then
            begin
                WriteLn;
                ReadLn;
                Continue;
            end;
        end;
        case option of 
            'end_of_programm':
            begin
                flag_end:= True;
                Halt(1);
            end;
            '1':
            begin
                Vvod_1;
                if flag_wrong_input then
                begin
                    Continue;
                end;
                if not(Find(city_start, cities)) then
                begin
                    WriteLn;
                    WriteLn('Не существует такого города отправления');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                if not(Find(city_end, cities)) then
                begin
                    WriteLn;
                    WriteLn('Не существует такого города назначения');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                if (city_start = city_end) then
                begin
                    WriteLn;
                    WriteLn('Вы уже в этом городе');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                D1(city_start, city_end);
            end;
            '2':
            begin
                Vvod_1;
                if flag_wrong_input then
                begin
                    Continue;
                end;
                if not(Find(city_start, cities)) then
                begin
                    WriteLn;
                    WriteLn('Не существует такого города отправления');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                if not(Find(city_end, cities)) then
                begin
                    WriteLn;
                    WriteLn('Не существует такого города назначения');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                if (city_start = city_end) then
                begin
                    WriteLn;
                    WriteLn('Вы уже в этом городе');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                D2(city_start, city_end);
            end;
            '3':
            begin
                Vvod_1;
                if flag_wrong_input then
                begin
                    Continue;
                end;
                if not(Find(city_start, cities)) then
                begin
                    WriteLn;
                    WriteLn('Не существует такого города отправления');
                    WriteLn(city_start);
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                if not(Find(city_end, cities)) then
                begin
                    WriteLn;
                    WriteLn('Не существует такого города назначения');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                if (city_start = city_end) then
                begin
                    WriteLn;
                    WriteLn('Вы уже в этом городе');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                D3(city_start, city_end);
            end;
            '4':
            begin
                Vvod_2;
                if flag_wrong_input then
                begin
                    Continue;
                end;
                if not(Find(city_start, cities)) then
                begin
                    WriteLn;
                    WriteLn('Не существует такого города отправления');
                    WriteLn(city_end);
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                D4(city_start, limit);
            end;
            '5':
            begin
                Vvod_2;
                if flag_wrong_input then
                begin
                    Continue;
                end;
                if not(Find(city_start, cities)) then
                begin
                    WriteLn;
                    WriteLn('Не существует такого города отправления');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                if (limit=0) then
                begin
                    WriteLn;
                    WriteLn('Невозможно найти такие города, т.к. телепортация еще не изобретена');
                    WriteLn;
                    ReadLn;
                    Continue;
                end;
                D5(city_start, limit);
            end;
        end;
        ReadLn;
    until flag_end;
end.
