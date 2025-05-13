uses matrixinout_unit  in 'modules/matrixinout_unit.pas',
     tree_unit         in 'modules/tree_unit.pas', 
     functions_unit     in 'modules/functions_unit.pas', 
     index_unit     in 'modules/index_unit.pas';

var slovo, result_name, format:string;
    epsilon :double;
    code, i:integer;
    f, fil :text;
    row2, column2,row1, column1, j :Int64;
    result_tree, tree, somn :link_t;
    maxlength :integer;
    file_name :string;

function Multiply(tree1, tree2 :link_t; rows, columns :Int64):link_t;

var res_tree :link_t;
    i :Int64;
    j :Int64;
    k :Int64;
    l :Int64;
    node_num :Int64;
    number   :double;
    matrixrow1 :mas_t;
    matrixrow2 :mas_t;

begin
  node_num := 1;
  res_tree := nil;
  for i := 1 to rows do
  begin
    SetLength(matrixrow1, 0);
    CollectRow(tree1, i, matrixrow1);
    for j := 1 to columns do
    begin
      SetLength(matrixrow2, 0);
      CollectRow(tree2, j, matrixrow2);
      if (Length(matrixrow1) <> 0) and (Length(matrixrow2) <> 0) then
      begin
        if (Length(matrixrow1) <> 1) then SortArr(matrixrow1);
        if (Length(matrixrow2) <> 1) then SortArr(matrixrow2);
        number := 0;
        for k := 0 to High(matrixrow1) do
        begin
          for l := 0 to High(matrixrow2) do
          begin
            if (matrixrow1[k].column = matrixrow2[l].column) then
            number := number + matrixrow1[k].element * matrixrow2[l].element
            else if (matrixrow1[k].column < matrixrow2[l].column) then Break;
          end;
        end;
      end
      else number := 0;
      if (abs(number) >= epsilon) then
      begin
        AddNode(number, i, j, res_tree, node_num);
        node_num := node_num + 1;
      end;
    end;
  end;
  Multiply := res_tree;
end;


begin
  if (ParamCount < 4) then
  begin
    WriteLn('Not enough values to start a programme');
    WriteLn;
    WriteLn('Формат параметров:');
    Write('epsilon формат_результат имя_резултата');
    WriteLn('имена_файлов_матриц');
    WriteLn;
    WriteLn('epsilon                   - число, показ. точность');
    WriteLn('формат_результат          - dence/sparce matrix');
    WriteLn('имя_резултата             - имя файла для хранения матрицы');
    WriteLn('имена_файлов_матриц       - имена файлов матриц для умножения');
    Halt(0);
  end;
  row2:=0;
  column2:=0;
  slovo := ParamStr(1);
  Val(slovo, epsilon, code);
  if (code <> 0) then
  begin
    WriteLn('Ошибка в точности');
    Halt(0);
  end
  else
  begin
    if (epsilon < 0) then
    begin
      WriteLn('Ошибка в точности');
      Halt(0);
    end;
  end;
  format := ParamStr(2);
  if (format <> 'dence') and (format <> 'sparce') then
  begin
    WriteLn('Ошибка в формате результата');
  end;
  somn := nil;
  result_name := ParamStr(3);
  for i := 4 to ParamCount do
  begin
    DestroyTree(somn);
    somn := nil;
    file_name := ParamStr(i);
    Assign(f, 'matrix/'+file_name+'.smtr');
    {$I-}
    Reset(f);
    {$I+}
    if (IOResult <> 0) then
    begin
      Assign(f, 'matrix/'+file_name+'.dmtr');
      {$I-}
      Reset(f);
      {$I+}
      if (IOResult <> 0) then
      begin
        WriteLn('file ', file_name, ' doesn`t exist');
        Halt(0);
      end
      else somn := ReadDenceMatrix(row2, column2, f);
    end
    else somn := ReadSparceMatrix(row2, column2, f);
    Assign(fil, 'index/'+file_name+'.dot');
    {$I-}
    Reset(fil);
    {$I+}
    if (IOResult <> 0) then
    begin
      maxlength := trunc(ln(abs(MaxTreeElement(somn)))/ln(10) + 2);
      PrintDisgraphMatrix(somn, row2, column2, maxlength, 'index/'+file_name+'.dot');
    end
    else Close(fil);
    if (i = 4) then
    begin
      result_tree := nil;
      for j := 1 to row2 do
      begin
        AddNode(1.0, j, j, result_tree, j);
      end;
      row1:=row2;
      column1:=row2;
    end;
    if (column1 <> row2) then
    begin
      WriteLn('impossible to multiply on ', file_name, ' matrix');
      Halt(0);
    end;
    tree := nil;
    InverseMatrix(somn, tree);
    result_tree := Multiply(result_tree, tree, row1, column2);
    column1 := column2;
  end;
  if (result_tree <> nil) then
  maxlength := trunc(ln(abs(MaxTreeElement(result_tree)))/ln(10) + 2);
  if (format = 'dence') then
  begin
    PrintDenceMatrix(result_tree, row1, column1, maxlength,
                     'matrix/' + result_name + '.dmtr');
    WriteLn('Результат сохранен в файл ', result_name, '.dmtr');
  end
  else
  begin
    PrintSparceMatrix(result_tree, row1, column1, maxlength,
                      'matrix/' + result_name + '.smtr');
    WriteLn('Результат сохранен в файл ', result_name, '.smtr');
  end;
  WriteLn('Умножение выполнено');
  DestroyTree(result_tree);
  DestroyTree(somn);
end.
