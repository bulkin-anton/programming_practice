unit matrixinout_unit;

Interface
uses tree_unit;
procedure PrintDenceMatrix(a:link_t; rows, columns:Int64;
                           maxlength:integer; file_name:string);
procedure PrintMatrix(a:link_t; rows, columns:Int64; maxlength:integer);
procedure PrintSparceMatrix(a:link_t; rows, columns:Int64;
                            maxlength:integer; file_name:string);
function ReadSparceMatrix(var row, column:Int64; var f:text):link_t;
function ReadDenceMatrix(var row, column:Int64; var f:text):link_t;


Implementation
uses functions_unit;
procedure PrintDenceMatrix(a:link_t; rows, columns:Int64;
                           maxlength:integer; file_name:string);

var i         :Int64;
    j         :Int64;
    k         :Int64;
    matrixRow :mas_t;
    f         :text;

begin
  Assign(f, file_name);
  Rewrite(f);
  WriteLn(f, '#');
  WriteLn(f, '# This file describes');
  WriteLn(f, '# dence matrix');
  WriteLn(f, '#');
  WriteLn(f, 'dence_matrix ', rows, ' ',columns);
  WriteLn(f);
  SetLength(matrixRow, 0);
  for i := 1 to rows do
  begin
    CollectRow(a, i, matrixRow);
    if (Length(matrixRow) <> 0) then
    begin
      if (Length(matrixRow) <> 1) then
      SortArr(matrixRow);
      k := 1;
      while (k <> matrixRow[0].column) do
      begin
        Write(f, 0.0:maxlength+2:1, ' ');
        k := k+1;
      end;
      Write(f, matrixRow[0].element:maxlength+2:1);
      if (matrixRow[0].column <> columns) then Write(f, ' ');
      for j := 1 to High(matrixRow) do
      begin
        for k := (matrixRow[j-1].column+1) to (matrixRow[j].column-1) do
        Write(f, 0.0:maxlength+2:1, ' ');
        Write(f, matrixRow[j].element:maxlength+2:1);
        if (matrixRow[j].column <> columns) then Write(f, ' ');
      end;
      if (matrixRow[High(matrixRow)].column <> columns) then
      begin
        k:=matrixRow[High(matrixRow)].column + 1;
        while (k <> columns) do
        begin
          Write(f, 0.0:maxlength+2:1, ' ');
          k := k + 1;
        end;
        Write(f, 0.0:maxlength+2:1);
      end;
    end
    else
    for j := 1 to columns do
    begin
      Write(f, 0.0:maxlength+2:1);
      if (j <> columns) then Write(f, ' ');
    end;
    WriteLn(f);
    SetLength(matrixRow, 0);
  end;
  Close(f);
end;


procedure PrintMatrix(a:link_t; rows,
                      columns:Int64; maxlength:integer);

var i         :Int64;
    j         :Int64;
    k         :Int64;
    matrixRow :mas_t;

begin
  WriteLn('#');
  WriteLn('# Output of');
  WriteLn('# matrix in console');
  WriteLn('#');
  WriteLn;
  WriteLn('matrix ', rows, ' ',columns);
  WriteLn;
  SetLength(matrixRow, 0);
  for i := 1 to rows do
  begin
    CollectRow(a, i, matrixRow);
    if (Length(matrixRow) <> 0) then
    begin
      if (Length(matrixRow) <> 1) then
      SortArr(matrixRow);
      k := 1;
      while (k <> matrixRow[0].column) do
      begin
        Write(0.0:maxlength+2:1, ' ');
        k := k + 1;
      end;
      Write(matrixRow[0].element:maxlength+2:1);
      if (matrixRow[0].column <> columns) then Write(' ');
      for j := 1 to High(matrixRow) do
      begin
        for k := (matrixRow[j-1].column+1) to (matrixRow[j].column-1) do
        Write(0.0:maxlength+2:1, ' ');
        Write(matrixRow[j].element:maxlength+2:1);
        if (matrixRow[j].column <> columns) then Write(' ');
      end;
      if (matrixRow[High(matrixRow)].column <> columns) then
      begin
        k := matrixRow[High(matrixRow)].column + 1;
        while (k <> columns) do
        begin
          Write(0.0:maxlength+2:1, ' ');
          k:=k+1;
        end;
        Write(0.0:maxlength+2:1);
      end;
    end
    else
    for j := 1 to columns do
    begin
      Write(0.0:maxlength+2:1);
      if (j <> columns) then Write(' ');
    end;
    WriteLn;
    SetLength(matrixRow, 0);
  end;
end;



procedure PrintSparceMatrix(a:link_t; rows, columns:Int64;
                            maxlength:integer; file_name:string);
var fil: text;

procedure PrintSparceHelp(a:link_t; rows, columns:Int64; var f:text);
var row_length    :Int64;
    column_length :Int64;
begin
  if (a <> nil) then
  begin
    row_length := trunc(ln(abs(rows))/ln(10) + 1);
    column_length := trunc(ln(abs(columns))/ln(10) + 1);
    WriteLn(f, a^.row:row_length, ' ',
            a^.column:column_length, ' ', a^.element:0:16);
    PrintSparceHelp(a^.left, rows, columns, f);
    PrintSparceHelp(a^.right, rows, columns, f);
  end;
end;

begin
  Assign(fil, file_name);
  Rewrite(fil);
  WriteLn(fil, '#');
  WriteLn(fil, '# This file describes');
  WriteLn(fil, '# sparce matrix');
  WriteLn(fil, '#');
  WriteLn(fil, 'sparce_matrix ', rows, ' ',columns);
  WriteLn(fil);
  PrintSparceHelp(a, rows, columns, fil);
  Close(fil);
end;



function ReadDenceMatrix(var row, column:Int64; var f:text):link_t;

var flag_end    :boolean;
    flag_row    :boolean;
    flag_column :boolean;
    flag_eof    :boolean;
    flag_eoln   :boolean;
    flag_com    :boolean;
    new_node    :boolean;
    flag_line   :boolean;
    flag_otr   :boolean;
    row_number    :Int64;
    column_number :Int64;
    dot           :Int64;
    i             :Int64;
    k             :Int64;
    node_number   :Int64;
    row_num       :Int64;
    c             :char;
    d             :char;
    matrix_type :string;
    s           :string;
    number_str  :string;
    element     :double;
    row_mas :array of double;
    res_tree :link_t;

procedure Probel_reset(var c:char);
begin
  repeat 
  if not(eof(f)) then 
  begin
    if not(eoln(f)) then Read(f, c)
    else 
    begin
      if eoln(f) then
      begin
        flag_eoln:=True;
        Break;
      end;
    end;
  end
  else
  begin
    flag_eof:=True;
    Break;
  end;
  until c<>' ';
end;

begin
  res_tree := nil;
  flag_end := False;
  flag_eof := False;
  node_number := 1;
  while not(eof(f)) and not(flag_end) do
  begin
    flag_eoln := False;
    Probel_reset(c);
    if (flag_eof) then
    begin
      WriteLn('No data found in file');
      Halt(0);
    end;
    if not(flag_eoln) then {условие на пустую строку}
    begin
      matrix_type := '';
      row_number := 0;
      column_number := 0;
      flag_row := False;
      flag_column := False;
      case c of
        '#': ; {Строка комментарий}
        'd':
        begin
          s := 'd';
          d := '.';
          while (not(eoln(f)) and (d<>' ') and
                (Length(s) < 255)) do
          begin
            if not(eoln(f)) then Read(f, d);
            if (d <> ' ') then s := s + d;
          end;
          matrix_type := s;
          if (matrix_type <> 'dence_matrix') then
          begin
            WriteLn('Wrong matrix_type');
            Halt(0);
          end;
          {Условия на пробелы между данными}
          if (d = ' ') then
          begin
            Probel_reset(d);
            if ((flag_eoln) or (d < '0') or (d > '9')) then
            begin
              WriteLn('Wrong input');
              Halt(0);
            end;             
          end
          else
          begin
            WriteLn('Wrong input1');
            Halt(0);
          end;
          {Находим row_number}
          while (d <> ' ') and not(eoln(f)) do
          begin
            flag_row := True;
            if (d >= '0') and (d <= '9') then
            begin
              row_number := row_number*10 + (ord(d) - ord('0'))
            end
            else
            begin
              WriteLn('Wrong row_number');
              Halt(0);
            end;
            if not(eoln(f)) then Read(f, d)
            else
            begin
              WriteLn('Wrong input');
              Halt(0);
            end;
          end;
          if (row_number = 0) then
          begin
            WriteLn('Wrong row_number');
            Halt(0);
          end;
          Probel_reset(d);
          {Условие на пробелы}
          if (flag_eoln) then
          begin
            WriteLn('Wrong input');
            Halt(0);
          end;
          {Находим column_number}
          while (d <> ' ') and not(eoln(f)) do
          begin
            flag_column := True;
            if (d >= '0') and (d <= '9') then
            begin
              column_number := column_number*10 + (ord(d) - ord('0'))
            end
            else
            begin
              WriteLn('Wrong column_number');
              Halt(0);
            end;
            if not(eoln(f)) then Read(f, d);
          end;
          if eoln(f) and (d >= '0') and (d <= '9') then 
          begin
            column_number := column_number*10 + (ord(d) - ord('0'));
            flag_column := True;
          end;
          {Проверка на правильность конца строки}
          Probel_reset(d);
          if not((c <> '#') or (flag_eoln)) then
          begin
            WriteLn('Wrong input');
            Halt(0);
          end;
          if not(flag_row) or not(flag_column) then
          begin
            WriteLn('Wrong input');
            Halt(0);
          end;
          if (matrix_type = 'dence_matrix')
          then flag_end := True;
          {данные получены}
        end;
        {Проверка на другие символы в начале строки}
        else
        begin
          WriteLn('Wrong input');
          Halt(0);
        end;
      end;
    end;
    {Переход на новую строку}
    if not(eof(f)) then ReadLn(f);
  end;
  row := row_number;
  row_num := 0;
  column := column_number;
  while not(eof(f)) do
  begin
    SetLength(row_mas, 0);
    flag_eoln := False;
    flag_com := False;
    flag_line := False;
    while not(flag_eoln) and not(flag_com) do
    begin
      Probel_reset(c);
      number_str := '';
      element:=0.0;
      flag_otr := False;
      if (c = '-') then
      begin
        flag_otr := True;
        if not(eoln(f)) then Read(f, c)
        else
        begin
          WriteLn('minus error');
          Halt(0);
        end;
      end;
      if not(flag_eoln) then
      begin
        while (c <> ' ') and (c <> '#') do
        begin
          if ((c >= '0') and (c <= '9')) or (c ='.') then
          number_str := number_str + c
          else
          begin
            WriteLn('data error');
            Halt(0);
          end;
          if not(eoln(f)) then Read(f, c)
          else Break;
        end;
        if (c = '#') then flag_com := True;
        if (number_str <> '') then
        begin
          dot := 0;
          for i := 1 to Length(number_str)-1 do
          begin
            if (number_str[i] = '.') then dot := dot +1;
          end;
          if (dot <> 1) then
          begin
            WriteLn('data dot error');
            Halt(0);
          end
          else
          begin
            i := 1;
            c := number_str[i];
            while (c <> '.') do
            begin
              element := element*10 + ord(c) - ord('0');
              i:= i + 1;
              c := number_str[i];
            end;
            i := i + 1;
            c := number_str[i];
            k := 10;
            while (i<=Length(number_str)) do
            begin
              c := number_str[i];
              element := element + (ord(c) - ord('0'))/k;
              i := i + 1;
              k := k * 10;
            end;
          end;
          if flag_otr then element := 0 - element;
          SetLength(row_mas, Length(row_mas)+1);
          row_mas[High(row_mas)] := element;
        end;
      end
      else flag_line := True;
      c := '#';
    end;
    if (Length(row_mas) <> column) and (flag_line) and
       (Length(row_mas) <> 0) then
    begin
      WriteLn('not enough columns');
      Halt(0);
    end
    else
    begin
      if (Length(row_mas) <> 0) then
      begin
        row_num := row_num + 1;
        for i := 0 to High(row_mas) do
        begin
          if (row_mas[i] <> 0.0) then
          begin
            new_node := AddNode(row_mas[i], row_num, i+1, res_tree, node_number);
            if new_node then node_number:= node_number + 1;
          end;
        end;
      end;
    end;
   if not(eof(f)) then ReadLn(f)
   else Break;
  end;
  if (row_num <> row) then
  begin
    WriteLn('not enough rows');
    Halt(0);
  end;
  Close(f);
  ReadDenceMatrix := res_tree;
end;

function ReadSparceMatrix(var row, column:Int64; var f:text):link_t;

var flag_end    :boolean;
    flag_row    :boolean;
    flag_column :boolean;
    flag_eof    :boolean;
    flag_eoln   :boolean;
    new_node    :boolean;
    flag_otr   :boolean;
    row_number    :Int64;
    column_number :Int64;
    dot           :Int64;
    i             :Int64;
    k             :Int64;
    node_number   :Int64;
    c             :char;
    d             :char;
    matrix_type :string;
    s           :string;
    number_str  :string;
    element     :double;
    res_tree :link_t;

procedure Probel_reset(var c:char);
begin
  repeat 
  if not(eof(f)) then 
  begin
    if not(eoln(f)) then Read(f, c)
    else 
    begin
      if eoln(f) then
      begin
        flag_eoln:=True;
        Break;
      end;
    end;
  end
  else
  begin
    flag_eof:=True;
    Break;
  end;
  until c<>' ';
end;

begin
  res_tree := nil;
  flag_end := False;
  flag_eof := False;
  node_number := 1;
  while not(eof(f)) and not(flag_end) do
  begin
    flag_eoln := False;
    Probel_reset(c);
    if (flag_eof) then
    begin
      WriteLn('No data found in file');
      Halt(0);
    end;
    if not(flag_eoln) then {условие на пустую строку}
    begin
      matrix_type := '';
      row_number := 0;
      column_number := 0;
      flag_row := False;
      flag_column := False;
      case c of
        '#': ; {Строка комментарий}
        's':
        begin
          s := 's';
          d := '.';
          while (not(eoln(f)) and (d<>' ') and
                (Length(s) < 255)) do
          begin
            if not(eoln(f)) then Read(f, d);
            if (d <> ' ') then s := s + d;
          end;
          matrix_type := s;
          if (matrix_type <> 'sparce_matrix') then
          begin
            WriteLn('Wrong matrix_type');
            Halt(0);
          end;
          {Условия на пробелы между данными}
          if (d = ' ') then
          begin
            Probel_reset(d);
            if ((flag_eoln) or (d < '0') or (d > '9')) then
            begin
              WriteLn('Wrong input');
              Halt(0);
            end;             
          end
          else
          begin
            WriteLn('Wrong input1');
            Halt(0);
          end;
          {Находим row_number}
          while (d <> ' ') and not(eoln(f)) do
          begin
            flag_row := True;
            if (d >= '0') and (d <= '9') then
            begin
              row_number := row_number*10 + (ord(d) - ord('0'))
            end
            else
            begin
              WriteLn('Wrong row_number');
              Halt(0);
            end;
            if not(eoln(f)) then Read(f, d)
            else
            begin
              WriteLn('Wrong input');
              Halt(0);
            end;
          end;
          if (row_number = 0) then
          begin
            WriteLn('Wrong row_number');
            Halt(0);
          end;
          Probel_reset(d);
          {Условие на пробелы}
          if (flag_eoln) then
          begin
            WriteLn('Wrong input');
            Halt(0);
          end;
          {Находим column_number}
          while (d <> ' ') and not(eoln(f)) do
          begin
            flag_column := True;
            if (d >= '0') and (d <= '9') then
            begin
              column_number := column_number*10 + (ord(d) - ord('0'))
            end
            else
            begin
              WriteLn('Wrong column_number');
              Halt(0);
            end;
            if not(eoln(f)) then Read(f, d);
          end;
          if eoln(f) and (d >= '0') and (d <= '9') then 
          begin
            column_number := column_number*10 + (ord(d) - ord('0'));
            flag_column := True;
          end;
          {Проверка на правильность конца строки}
          Probel_reset(d);
          if not((c <> '#') or (flag_eoln)) then
          begin
            WriteLn('Wrong input');
            Halt(0);
          end;
          if not(flag_row) or not(flag_column) then
          begin
            WriteLn('Wrong input');
            Halt(0);
          end;
          if (matrix_type = 'sparce_matrix')
          then flag_end := True;
          {данные получены}
        end;
        {Проверка на другие символы в начале строки}
        else
        begin
          WriteLn('Wrong input');
          Halt(0);
        end;
      end;
    end;
    {Переход на новую строку}
    if not(eof(f)) then ReadLn(f);
  end;
  row := row_number;
  column := column_number;
  while not(eof(f)) do
  begin
    row_number := 0;
    column_number := 0;
    number_str:= '';
    flag_eoln := False;
    flag_otr := False;
    Probel_reset(c);
    if not(flag_eoln or (c = '#')) then
    begin
      while (c <> ' ') do
      begin
        if (c >= '0') and (c <= '9') then
        row_number := row_number*10 + ord(c) - ord('0')
        else
        begin
          WriteLn('error in a row');
          Halt(0);
        end;
        if not(eoln(f)) then Read(f, c)
        else
        begin
          WriteLn('error in a row');
          Halt(0);
        end;
      end;
      Probel_reset(c);
      if not(flag_eoln or (c = '#')) then
      begin
        while (c <> ' ') do
        begin
          if (c >= '0') and (c <= '9') then
          column_number := column_number*10 + ord(c) - ord('0')
          else
          begin
            WriteLn('error in a column', c);
            Halt(0);
          end;
          if not(eoln(f)) then Read(f, c)
          else
          begin
            WriteLn('error in a column');
            Halt(0);
          end;
        end;
        Probel_reset(c);
        element:=0.0;
        if (c = '-') then
        begin
          flag_otr := True;
          if not(eoln(f)) then Read(f, c)
          else
          begin
            WriteLn('minus error');
            Halt(0);
          end;
        end;
        if not(flag_eoln) then
        begin
          while (c <> ' ') and (c <> '#') do
          begin
            if ((c >= '0') and (c <= '9')) or (c ='.') then
            number_str := number_str + c
            else
            begin
              WriteLn('data error');
              Halt(0);
            end;
            if not(eoln(f)) then Read(f, c)
            else Break;
          end;
          if (number_str <> '') then
          begin
            dot := 0;
            for i := 1 to Length(number_str)-1 do
            begin
              if (number_str[i] = '.') then dot := dot +1;
            end;
            if (dot <> 1) then
            begin
              WriteLn('data dot error');
              Halt(0);
            end
            else
            begin
              i := 1;
              c := number_str[i];
              while (c <> '.') do
              begin
                element := element*10 + ord(c) - ord('0');
                i:= i + 1;
                c := number_str[i];
              end;
              i := i + 1;
              c := number_str[i];
              k := 10;
              while (i<=Length(number_str)) do
              begin
                c := number_str[i];
                element := element + (ord(c) - ord('0'))/k;
                i := i + 1;
                k := k * 10;
              end;
            end;
          end;
        end
        else
        begin
           WriteLn('error in element');
        Halt(0);
        end;
      end
      else
      begin
        WriteLn('error in a column');
        Halt(0);
      end;
      if (row_number <= 0) or (column_number <= 0) then
      begin
        WriteLn('error in row or column');
        Halt(0);
      end;
      if flag_otr then element := 0 - element;
      if (row_number <= row) and (column_number <= column) then
      begin
        new_node := AddNode(element, row_number, column_number,
                            res_tree, node_number);
        if new_node then node_number:= node_number + 1;
      end
      else
      begin
        WriteLn('too large row or column');
        Halt(0);
      end;
    end;
    if not(eof(f)) then ReadLn(f)
    else Break;
  end;
  Close(f);
  ReadSparceMatrix := res_tree;
end;

end.
