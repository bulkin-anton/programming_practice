uses matrixinout_unit in 'modules/matrixinout_unit.pas',
     tree_unit        in 'modules/tree_unit.pas', 
     functions_unit   in 'modules/functions_unit.pas',
     index_unit       in 'modules/index_unit.pas';

var row            :Int64;
    column         :Int64;
    change_row     :Int64;
    change_column  :Int64;
    change_element :double;
    matrix_name    :string;
    slovo          :string;
    format         :string;
    f              :text;
    fin            :text;
    matrix         :link_t;
    index          :link_t;
    code           :integer;
    maxlength      :integer;
    
begin
  row := 0;
  column := 0;
  matrix := nil;
  index := nil;
  if (ParamCount <> 4) then
  begin
    WriteLn('Неверное количество параматров');
    WriteLn('Введите имя матрицы из папки matrix');
    WriteLn('Введите номер строки');
    WriteLn('Введите номер столбца');
    WriteLn('Введите значение элемента');
    WriteLn('Имя индекса из папки index считается таким же как у матрицы');
    Halt(0);
  end;
  matrix_name := ParamStr(1);
  {parametrs}
  slovo := ParamStr(2);
  Val(slovo, change_row, code);
  if (code <> 0) then
  begin
    WriteLn('Ошибка в строке');
    Halt(0);
  end;
  if (change_row <= 0) then
  begin
    WriteLn('Ошибка в строке');
    Halt(0);
  end;
  slovo := ParamStr(3);
  Val(slovo, change_column, code);
  if (code <> 0) then
  begin
    WriteLn('Ошибка в столбце');
    Halt(0);
  end;
  if (change_column <= 0) then
  begin
    WriteLn('Ошибка в столбце');
    Halt(0);
  end;
  slovo := ParamStr(4);
  Val(slovo, change_element, code);
  if (code <> 0) then
  begin
    WriteLn('Ошибка в элементе');
    Halt(0);
  end;
  Assign(f, 'matrix/'+matrix_name+'.smtr');
  {$I-}
  Reset(f);
  {$I+}
  if (IOResult <> 0) then
  begin
    Assign(f, 'matrix/'+matrix_name+'.dmtr');
    {$I-}
    Reset(f);
    {$I+}
    if (IOResult <> 0) then
    begin
      WriteLn('file ', matrix_name, ' doesn`t exist');
      Halt(0);
    end
    else
    begin
      matrix := ReadDenceMatrix(row, column, f);
      format := 'dence';
    end;
  end
  else
  begin
    matrix := ReadSparceMatrix(row, column, f);
    format := 'sparce';
  end;
  if (change_element <> 0) then
  AddNode(change_element, change_row, change_column,
          matrix, CntEl(matrix) + 1)
  else DeleteNode(matrix, change_row, change_column);
  maxlength := trunc(ln(abs(MaxTreeElement(matrix)))/ln(10) + 2);
  Assign(fin, 'index/' + matrix_name + '.dot');
  {$I-}
  Reset(fin);
  {$I+}
  if (IOResult <> 0) then
  begin
    PrintDisgraphMatrix(matrix, row, column, maxlength,
                        'index/' + matrix_name + '.dot');
    WriteLn('Построен индекс в файле ', matrix_name + '.dot');
  end
  else
  begin
    index := ReadIndex(fin);
    RewriteIndex(index, matrix);
    PrintDisgraphMatrix(index, row, column, maxlength,
                        'index/' + matrix_name + '.dot');
    WriteLn('Перестроен индекс в файле ', matrix_name + '.dot');
  end;
  if (format = 'sparce') then
    PrintSparceMatrix(matrix, row, column, maxlength,
                      'matrix/'+matrix_name+'.smtr')
  else PrintDenceMatrix(matrix, row, column, maxlength,
                        'matrix/'+matrix_name+'.dmtr');
  WriteLn('Перестроена матрица в файле ', matrix_name);
  DestroyTree(index);
  DestroyTree(matrix);
end.
