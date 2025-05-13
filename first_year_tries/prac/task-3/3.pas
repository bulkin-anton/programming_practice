uses cthreads, ptcCrt, ptcGraph;

type Function_t = function(x:double):double;
     Mas_t = record
       x:double;
       n:integer;
     end;

var a   :double;
    b   :double;
    x1  :double;
    x2  :double;
    x3  :double;
    eps :double;
    s   :double;
    s1  :double;
    s2  :double;
    otl :boolean;
    i   :integer;
    k   :integer;
    n   :integer;
    m   :integer;
    n1  :integer;
    n2  :integer;
    n3  :integer;
    otl_number :integer;
    tochnost   :integer;
    mas :array[1..3] of Mas_t;
    driver :SmallInt;
    mode   :SmallInt;
    t      :Mas_t;



{
  Фунции, первые и вторые производные функций из условия
}

function F1(x:double):double;
begin
  F1 := 0.6*x + 3;
end;

function F2(x:double):double;
begin
  x := x-2;
  F2 := x*x*x -1;
end;

function F3(x:double):double;
begin
  F3 := 3/x;
end;

function Proisv11(x:double):double;
begin
  Proisv11 := 0.6;
end;

function Proisv12(x:double):double;
begin
  Proisv12 := 0;
end;

function Proisv21(x:double):double;
begin
  Proisv21 := 3*x*x - 12*x + 12;
end;

function Proisv22(x:double):double;
begin
  Proisv22 := 6*x - 12;
end;

function Proisv31(x:double):double;
begin
  Proisv31 := (-3)*(1/x)*(1/x);
end;

function Proisv32(x:double):double;
begin
  Proisv32 := (6)*(1/x)*(1/x)*(1/x);
end;

{
  Процедура нахождения точек пересечения графиков
}
procedure Root (Func1, Func2, Proisv_1, Proisv_2:Function_t; 
                a, b, eps:double; var x:double; var n:integer);
var c, c1, d1: double;
    d: double;
{
  Вспомогательные функции, определяющие
  новую фунцию и ее производную
}
function Func(x:double):double;
begin
  Func := Func1(x) - Func2(x);
end;

function Proisv(x:double):double;
begin
  Proisv := Proisv_1(x) - Proisv_2(x);
end;

begin
  if otl then
  Writeln('Границы: ', a:tochnost+3:tochnost, ' ', b:tochnost+3:tochnost);
  repeat
  if (((Func(a) < 0) and (Func((a+b)/2) < ((Func(a) + Func(b))/2))) or 
     ((Func(a) > 0) and (Func((a+b)/2) > ((Func(a) + Func(b))/2)))) then
  begin
    d := b;
    c := d - Func(d)/Proisv(d);
    d1 := c;
    c1 := d - Func(d1)/Proisv(d1);
    if otl then
    Writeln('Границы: ', c1:tochnost+3:tochnost, ' ', c:tochnost+3:tochnost);
    if (abs(c-c1) < eps) then
    begin
      x := (c+c1)/2;
      Exit;
    end
    else
    begin
      n := n+1;
      b:=c; a:=c1;
    end;
  end
  else
  begin 
    d := a;
    c := d - Func(d)/Proisv(d);
    d1 := c;
    c1 := d1 - Func(d1)/Proisv(d1);
    if otl then
    Writeln('Границы: ', c1:tochnost+3:tochnost, ' ', c:tochnost+3:tochnost);
    if (abs(c1-c) < eps) then
    begin
      x := (c+c1)/2;
      Exit;
    end
    else
    begin
      n := n+1;
      a := c;
      b:=c1;
    end;
  end;
  until False;
end;

{
  Процедура нахождения отрезка,
  на котором лежит точка пересечения
}
procedure Find(Func1, Func2, Proisv_11, Proisv_21, 
               Proisv_12, Proisv_22:Function_t; 
               var a, b:double);

var i :integer;
    j :integer;
    k :integer;
    error :boolean;
    l :double;
    m :double;

function Func(x:double):double;
begin
  Func := Func1(x) - Func2(x);
end;

function Proisv_1(x:double):double;
begin
  Proisv_1 := Proisv_11(x) - Proisv_21(x);
end;

function Proisv_2(x:double):double;
begin
  Proisv_2 := Proisv_12(x) - Proisv_22(x);
end;

begin
  error := False;
  for i := -100 to 100 do
  begin
    for j := 100 downto -100 do
    begin
      l := i/5;
      m := j/5;
      if (l < m) and (l <> 0) and (m <> 0) then
      begin
        if (Func(l)*Func(m) < 0) and (Proisv_1(l) <> 0) and 
           (Proisv_1(m) <> 0) and (Proisv_2(l) <> 0) and
           (Proisv_2(m) <> 0) then
        begin
          for k:=i to j do
          begin
            if (k <> 0) then
            if (Proisv_1(k/10)*Proisv_1(l) < 0) or
               (Proisv_2(k/10)*Proisv_2(l) < 0)then
            begin
              error := True;
              break;
            end;
          end;
          if (error = True) then
          begin
            error := False;
            Continue;
          end
          else
          begin
            a := l;
            b := m;
            Exit;
          end;
        end;
      end;
    end;
  end;
end;


{
  Функция, вычисляющая площадь между графиками,
  вычисляя значение определенного интеграла
}
function Integral(Func1, Func2:Function_t; a, b, eps:double;
                  var n :integer):double;
                  
var I  :double;
    I1 :double;
    I2 :double;
    I3 :double;
    h  :double;
    x  :double;
    par :integer;

function F(x:double):double;
begin
  F := Func1(x) - Func2(x);
end;
begin
  n := 1;
  I2 := 0;
  par := 1;
  h := b-a;
  I := F(a)+F(b);
  repeat
    n := n + 1;
    I3 := I2;
    h := h/2;
    I1 := 0;
    x := a+h;
    repeat
      I1 := I1+2*F(x);
      x := x+2*h;
    until not (x < b);
    I := I+I1;
    I2 := (I+I1)*h/3;
    x := Abs(I3-I2)/15;
    par := par*2;
    if otl then
    begin
      Write('Значение: ');
      Write(I2:tochnost+2:tochnost);
      Write(' парабол: ', par);
      WriteLn;
    end;
  until  not (x > eps);
  Integral := I2;
end;

{
  Процедура, отвечающая за создание графического окна
}
procedure Graphics(Func1, Func2, Func3:Function_t);

var otstupMinX :integer;
    otstupMinY :integer;
    otstupMaxX :integer;
    otstupMaxY :integer;
    x0 :integer;
    y0 :integer;
    x  :integer;
    xMin :integer;
    xMax :integer;
    yMin :integer;
    yMax :integer;
    dx :double;
    dy :double;
    l :double;
    mashtabX :double;
    mashtabY :double;
    slovo :string;
    sl :string;

{
  Вспомогательная процедура, рисующая графики функций
}
procedure Draw(F:Function_t; a:word);
var c_x :integer;
    c_y :integer;
    x :double;
    y :double;
begin
  SetColor(a);
  x := xMin;
  while (x <= xMax) do
  begin
  	if (abs(x) > 0.002) then 
  	begin
  		y := F(x);
  		c_x := x0 + round(x*mashtabX);
  		c_y := y0 - round(y*mashtabY);
  		if ((c_y >= otstupMinY) and
  		   (c_y <= otstupMaxY)) then
  		begin
  		  PutPixel(c_x, c_y, a);
  		  PutPixel(c_x-1, c_y-1, a);
  		end;
  	end;
  	x := x + 0.0001;
  end;
end;


begin
  {
    Инициализация окна
  }
  driver := 10;
  mode := 260;
  InitGraph(driver, mode, '');
  SetBkColor(LightGray);
  {
    Создание отступов
  }
  otstupMinX := 10;
  otstupMinY := 10;
  otstupMaxX := GetMaxX -10;
  otstupMaxY := GetMaxY -10;
  {
    Границы графиков
  }
  xMin := -6;
  xMax := 6;
  yMin := -13;
  yMax := 6;
  dx := 0.1;
  dy := 0.5;
  {
    Вычисления масштаба
  }
  mashtabX := (otstupMaxX - otstupMinX) / (xMax - xMin);
  mashtabY := (otstupMaxY - otstupMinY) / (yMax - yMin);
  {
    Создание осей координат
  }
  x0 := otstupMaxX - trunc(xMax*mashtabX);
  y0 := otstupMinY + trunc(yMax*mashtabY);
  Line(x0, otstupMinY, x0, otstupMaxY);
  Line(otstupMinX, y0, otstupMaxX, y0);
  {
    Создание масштаба в окне и
    создание штрихов
  }
  k := round((xMax-xMin)/dx) + 1;
  x := x0;
  i := 0;
  while (x < otstupMaxX) do
  begin
    i := i + 1;
    if ((i mod 10) = 0) then
    begin
      str(round(i*dx), slovo);
      Line(x, y0 + 2, x, y0 - 2);
      OutTextXY(x + 10 - TextWidth(slovo) div 2, y0 + 6, slovo);
    end;
    Line(x, y0 + 2, x, y0 - 2);
    x := x + trunc(dx*mashtabX);
  end;
  x := x0;
  i := 0;
  while (x > otstupMinX) do
  begin
    i := i + 1;
    if ((i mod 10) = 0) then
    begin
      str(round(-i*dx), slovo);
      Line(x, y0 + 2, x, y0 - 2);
      OutTextXY(x - 10 - TextWidth(slovo) div 2, y0 + 6, slovo);
    end;
    Line(x, y0 + 2, x, y0 - 2);
    x := x - trunc(dx*mashtabX);
  end;
  x := y0;
  i := 0;
  while (x > otstupMinY) do
  begin
    i:= i + 1;
    if ((i mod 2) = 0) then
    begin
      str(round(-i*dy), slovo);
      OutTextXY(x0 - TextWidth(slovo) - 3, x + 16, slovo);
    end;
    Line(x0 + 2, x, x0 - 2, x);
    x := x + trunc(dy*mashtabY);
  end;
  x := y0;
  i := 0;
  while (x < otstupMaxY) do
  begin
    i := i + 1;
    if ((i mod 2) = 0) then
    begin
      str(round(i*dy), slovo);
      OutTextXY(x0 - TextWidth(slovo) - 3, x - 3, slovo);
    end;
    Line(x0 + 2, x, x0 - 2, x);
    x := x - trunc(dy*mashtabY);
  end;
  {
    Создание графиков функций
  }
  Draw(Func1, Green);
  Draw(Func2, Blue);
  Draw(Func3, Red);
  {
    Вывод значения, получившейся площади
  }
  l := s;
  slovo := '';
  Str(trunc(l), sl);
  slovo := sl + '.';
  l:= l - trunc(l);
  for i := abs(round(ln(eps))) downto 0 do
  begin
    l := l*10;
    Str((trunc(l) mod 10), sl);
    slovo := slovo + sl;
  end;
  slovo := 'S = ' + slovo; 
  OutTextXY(x0 - TextWidth(slovo) div 2, y0 - 10, slovo);
end;


{
  Тело программы
}
begin
  WriteLn('Нужна отладка?');
  WriteLn('1 - да');
  WriteLn('0 - нет');
  ReadLn(otl_number);
  if (otl_number = 1) then otl := True
  else if (otl_number = 0) then otl := False
  else
  begin
    WriteLn('Wrong number');
    Halt(0);
  end;
  a := -10;
  b := 10;
  eps := 0.0001;
  n1 := 0;
  n2 := 0;
  n3 := 0;
  if otl then
  begin
    WriteLn('Введите epsilon');
    Readln(eps);
  end;
  tochnost := trunc(abs(ln(abs(eps))/ln(10)) + 1);
  if otl then WriteLn('Корень номер 1:');
  Find(@F1, @F2, @Proisv11, @Proisv21, @Proisv12, @Proisv22, a, b);
  Root(@F1, @F2, @Proisv11, @Proisv21, a, b, eps/6, x1, n1);
  if otl then
  begin
    WriteLn;
    WriteLn('Корень номер 2:');
  end;
  Find(@F1, @F3, @Proisv11, @Proisv31, @Proisv12, @Proisv32, a, b);
  Root(@F1, @F3, @Proisv11, @Proisv31, a, b, eps/6, x2, n2);
  if otl then
  begin
    WriteLn;
    WriteLn('Корень номер 3:');
  end;
  Find(@F3, @F2, @Proisv31, @Proisv21, @Proisv32, @Proisv22, a, b);
  Root(@F3, @F2, @Proisv31, @Proisv21, a, b, eps/6, x3, n3);
  if otl then WriteLn;
  mas[1].x := x1;
  mas[2].x := x2;
  mas[3].x := x3;
  mas[1].n := n1;
  mas[2].n := n2;
  mas[3].n := n3;
  for k := 1 to 2 do
    for i := 1 to (3-k) do
      if mas[i].x > mas[i+1].x then
      begin
        t.x := mas[i].x;
        t.n := mas[i].n;
        mas[i].x := mas[i+1].x;
        mas[i].n := mas[i+1].n;
        mas[i+1].x := t.x;
        mas[i+1].n := t.n;
      end;
   x1 := mas[1].x;
   x2 := mas[2].x;
   x3 := mas[3].x;
   n1 := mas[1].n;
   n2 := mas[2].n;
   n3 := mas[3].n;
   WriteLn('x1: ', x1:tochnost+3:tochnost, ' за ',n1, ' steps');
   WriteLn('x2: ', x2:tochnost+3:tochnost, ' за ',n2, ' steps');
   WriteLn('x3: ', x3:tochnost+3:tochnost, ' за ',n3, ' steps');
   WriteLn;
   n :=1; m:=1;
   if otl then WriteLn('Интеграл s1:');
   s1 := Integral(@F1, @F3, x1, x2, eps/4, n);
   if otl then
   begin
     WriteLn;
     WriteLn('Интеграл s2:');
   end;
   s2 := Integral(@F1, @F2, x2, x3, eps/4, m);
   if otl then WriteLn;
   s := s1 + s2;
   Graphics(@F1, @F2, @F3);
   WriteLn('s1: ', s1:tochnost+3:tochnost, ' за ', n, ' steps');
   WriteLn('s2: ', s2:tochnost+3:tochnost, ' за ', m, ' steps');
   WriteLn('s : ', s:tochnost+3:tochnost, ' за ', n+m, ' steps');
   ReadLn;
end.
