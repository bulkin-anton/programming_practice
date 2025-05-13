uses matrixinout_unit in 'modules/matrixinout_unit.pas',
     tree_unit        in 'modules/tree_unit.pas',
     functions_unit   in 'modules/functions_unit.pas', crt;

const MaxInt = 9223372036854775807;

var rows_number    :Int64;
    columns_number :Int64;
    row            :Int64;
    column         :Int64;
    element_number :Int64;
    i              :Int64;
    c              :Int64;
    number_length  :Int64;
    razryad        :double;
    number         :double;
    d              :double;
    mode_number    :integer;
    znak           :integer;
    print_mode     :integer;
    code           :integer;
    max_length     :integer;
    file_name      :string;
    slovo          :string;
    tree           :link_t;
    newnode        :boolean;

begin
  Randomize;
  TextColor(Green);
  {
    Проверяем количество параметров
  }
  if ((ParamCount < 5) or (ParamCount > 6)) then
  begin
    WriteLn('Not enough values to start a programme');
    WriteLn;
    WriteLn('Формат параметров:');
    Write('кол-во_строк кол-во_стобцов степень_разряженности ');
    WriteLn('режим_работы имя_файла {печать_в_поток_вывода}');
    WriteLn;
    WriteLn('кол-во_строк            - натуральное число');
    WriteLn('кол-во_стобцов          - натуральное число');
    WriteLn('степень_разряженности   - число с плавающей точкой (0, 1]');
    WriteLn('режим_работы            - 1 - единицы в случ. позициях');
    WriteLn('                        - 2 - случайные значения');
    WriteLn('                        - 3 - единицы в случ. позициях на диаг.');
    WriteLn('имя_файла               - имя файла для хранения матрицы');
    WriteLn('{печать_в_поток_вывода} - 1 или 0(необяз. параметр, отвеч. за печать)');
    Halt(0);
  end;
  {
    Получаем количество строк
  }
  slovo := ParamStr(1);
  Val(slovo, rows_number, code);
  if (code <> 0) then
  begin
    WriteLn('Ошибка в количестве рядов');
    Halt(0);
  end
  else
  begin
    if (rows_number < 1) then
    begin
      WriteLn('Ошибка в количестве рядов');
      Halt(0);
    end;
  end;
  {
    Получаем количество столбцов
  }
  slovo := ParamStr(2);
  Val(slovo, columns_number, code);
  if (code <> 0) then
  begin
    WriteLn('Ошибка в количестве строк');
    Halt(0);
  end
  else
  begin
    if (columns_number < 1) then
    begin
      WriteLn('Ошибка в количестве строк');
      Halt(0);
    end;
  end;
  {
    Получаем степень разряженности матрицы
  }
  slovo := ParamStr(3);
  Val(slovo, razryad, code);
  if (code <> 0) then
  begin
    WriteLn('Ошибка в степени разряженности');
    Halt(0);
  end
  else
  begin
    if ((razryad > 1) or (razryad <= 0)) then
    begin
      WriteLn('Ошибка в степени разряженности');
      Halt(0);
    end;
  end;
  {
    Получаем режим работы
  }
  slovo := ParamStr(4);
  Val(slovo, mode_number, code);
  if (code <> 0) then
  begin
    WriteLn('Ошибка в режиме работе');
    Halt(0);
  end
  else
  begin
    if ((mode_number > 3) or (mode_number <= 0)) then
    begin
      WriteLn('Ошибка в режиме работе');
      Halt(0);
    end;
  end;
  {
    Получаем название файла
  }
  file_name := 'matrix/'+ParamStr(5);
  print_mode := 0;
  if (ParamCount > 5) then
  begin
    slovo := ParamStr(6);
    Val(slovo, print_mode, code);
    if (code <> 0) then
    begin
      WriteLn('Ошибка в режиме печати');
      Halt(0);
    end
    else
    begin
      if ((print_mode < 0) or (print_mode > 1)) then
      begin
        WriteLn('Ошибка в режиме печати');
        Halt(0);
      end;
    end;
  end;
  {
    Получены значения из параметров строки
  }
  tree := nil;
  max_length := 1;
  {
    Вычилем количество элементов для генерации
  }
  if (mode_number = 3) then
  begin
    if (rows_number < columns_number) then
      c := rows_number
    else c := columns_number;
    element_number := trunc(c * razryad);
  end
  else element_number := trunc(rows_number * columns_number * razryad);
  if (element_number = 0) then element_number := 1;
  {
    Генерируем элементы
  }
  i:=1;
  repeat
    {
      Генерируем позицию элемента
    }
    if (mode_number <> 3) then
    begin
      row := 0;
      while (row = 0) do
      begin
        row := Random(rows_number + 1);
      end;
      column := 0;
      while (column = 0) do
      begin
        column := Random(columns_number + 1);
      end;
    end
    else
    begin
      row := 0;
      while (row = 0) do
      begin
        row := Random(c + 1);
      end;
      column := row;
    end;
    {
      Генерируем сам элемент
    }
    if (mode_number = 2) then
    begin
      number := 0;
      while (number = 0) do
      begin
        d:= Random;
        number := Random(1000)*d;
        d:= Random;
        number := number + d;
        znak := Random(2);
        if (znak = 1) then number := -number;
      end;
    end
    else number := 1;
    {
      Добовляем в дерево
    }
    newnode := AddNode(number, row, column, tree, i);
    if newnode then
    begin
      i := i + 1;
      number_length := trunc(ln(abs(number))/ln(10) + 2);
      if (max_length < number_length) then max_length := number_length;
    end;
  until (i = element_number+1);
  {PrintTree(tree, 0);}
  {
    Производим сохранение в файл и печать
  }
  if (razryad = 1) and (mode_number <> 3) then
  PrintDenceMatrix(tree, rows_number, columns_number,
                   max_length, file_name+'.dmtr')
  else PrintSparceMatrix(tree, rows_number, columns_number,
                         max_length, file_name+'.smtr');
  {PrintDisgraphMatrix(tree, rows_number, columns_number,
                       max_length, file_name+'.dot');}
  if (print_mode = 1) then
  begin
    PrintMatrix(tree, rows_number, columns_number, max_length);
  end;
  {
    Уничтожаем дерево
  }
  DestroyTree(tree);
end.
