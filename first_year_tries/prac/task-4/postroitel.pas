uses matrixinout_unit in 'modules/matrixinout_unit.pas',
     tree_unit        in 'modules/tree_unit.pas', 
     functions_unit   in 'modules/functions_unit.pas',
     index_unit       in 'modules/index_unit.pas';

var f   :text;
    fin :text;
    matrix :link_t;
    index  :link_t;
    matrix_name :string;
    index_name  :string;
    slovo       :string;
    row       :Int64;
    column    :Int64;
    maxlength :Int64;
    mode    :integer;
    code    :integer;

begin
  row := 0;
  column := 0;
  matrix := nil;
  index := nil;
  if (ParamCount <> 3) and (ParamCount <> 2) then
  begin
    WriteLn('Неверное количество параматров');
    WriteLn('Введите имя матрицы из папки matrix');
    WriteLn('Введите имя индекса из папки index');
    WriteLn('(Необязательно) Введите 1/0 - печать в поток вывода или нет');
    Halt(0);
  end;
  matrix_name := ParamStr(1);
  index_name := ParamStr(2);
  if (ParamCount = 3) then
  begin
    slovo := ParamStr(3);
    Val(slovo, mode, code);
    if (code <> 0) then
    begin
      WriteLn('mode error');
      Halt(0);
    end;
    if (mode <> 0) and (mode <> 1) then
    begin
      WriteLn('wrong mode number');
      Halt(0);
    end;
  end
  else mode := 0;
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
    else matrix := ReadDenceMatrix(row, column, f);
  end
  else matrix := ReadSparceMatrix(row, column, f);
  maxlength := trunc(ln(abs(MaxTreeElement(matrix)))/ln(10) + 2);
  Assign(fin, 'index/' + index_name + '.dot');
  {$I-}
  Reset(fin);
  {$I+}
  if (IOResult <> 0) then
  begin
    index := matrix;
    PrintDisgraphMatrix(index, row, column, maxlength,
                        'index/' + index_name + '.dot');
    WriteLn('Построен индекс в файле ', index_name + '.dot');
    if (mode = 1) then PrintIndex1(index, maxlength);
    DestroyTree(index);
  end
  else
  begin
    index := ReadIndex(fin);
    Close(fin);
    RewriteIndex(index, matrix);
    PrintDisgraphMatrix(matrix, row, column, maxlength, 
                        'index/' + index_name + '.dot');
    WriteLn('Перестроен индекс в файле ', index_name + '.dot');
    if (mode = 1) then PrintIndex1(index, maxlength);
    DestroyTree(index);
    DestroyTree(matrix);
  end;
end.
