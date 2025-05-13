unit index_unit;

Interface

uses tree_unit;
function ReadIndex(var f:text):link_t;
procedure PrintDisgraphMatrix(a:link_t; rows, columns:Int64;
                            maxlength:integer; file_name:string);
procedure PrintIndex1(a:link_t; maxlength:integer);
procedure PrintIndex3(a:link_t; maxlength, depth, height,
                      num:integer; var cntnum:integer);

Implementation
uses functions_unit;

procedure PrintDisgraphMatrix(a:link_t; rows, columns:Int64;
                            maxlength:integer; file_name:string);
var fil: text;
    number_length:integer;
procedure PrintNodes(a:link_t; maxlength:integer);
begin
  if (a <> nil) then
  begin
    PrintNodes(a^.left, maxlength);
    Write(fil, a^.node_number:trunc(ln(abs(rows * columns))/ln(10) + 2)+1);
    Write(fil, ' ');
    Write(fil, '[label="');
    Write(fil, a^.row);
    Write(fil, ' ');
    Write(fil, a^.column:maxlength+1);
    Write(fil, '\n');
    Write(fil, a^.element:0:1);
    Write(fil, '"];');
    WriteLn(fil, '');
    PrintNodes(a^.right, maxlength);
  end;
end;
procedure PrintEdges(a:link_t);
var length,i:Integer;
begin
  if (a <> nil) then
  begin
    PrintEdges(a^.left);
    length := trunc(ln(abs(Max(rows,columns)))/ln(10) + 2)+1;
    if (a^.left <> nil) or (a^.right <> nil) then
    begin
      if (a^.left <> nil) then
      begin
        Write(fil, ' ',a^.node_number:length);
        Write(fil, ' -> ');
        Write(fil, a^.left^.node_number:length);
        Write(fil, ' [label="L"];');
      end
      else for i:=1 to (2*length+4+14) do Write(fil, ' ');
      if (a^.right <> nil) then
      begin
        Write(fil, ' ',a^.node_number:length);
        Write(fil, ' -> ');
        Write(fil, a^.right^.node_number:length);
        Write(fil, ' [label="R"];');
      end;
      WriteLn(fil);
    end;
    PrintEdges(a^.right);
  end;
end;
begin
  Assign(fil, file_name);
  Rewrite(fil);
  WriteLn(fil, 'digraph');
  WriteLn(fil, '{');
  number_length := trunc(ln(abs(Max(rows, columns)))/ln(10));
  PrintNodes(a, number_length);
  WriteLn(fil, '   //edges');
  WriteLn(fil);
  PrintEdges(a);
  WriteLn(fil, '}');
  Close(fil);
end;

function ReadIndex(var f:text):link_t;
var disgraph :string;
    num :string;
    str :string;
    line        :Int64;
    h           :Int64;
    edge_pos    :Int64;
    edge_num00  :Int64;
    label_pos_l :Int64;
    label_pos_r :Int64;
    i           :integer;
    k           :integer;
    edge_num    :Int64;
    edge_num0   :Int64;
    edge_num1   :Int64;
    strel_pos   :Int64;
    edge_num2   :Int64;
    com_pos     :Int64;
    label_pos   :Int64;
    j           :integer;
    row_num     :Int64;
    col_num     :Int64;
    code        :integer;
    skob_pos    :Int64;
    c           :char;
    num_el     :double;
    flag_eof   :boolean;
    flag_eoln  :boolean;
    flag_edges :boolean;
    flag_com   :boolean;
    a          :link_t;
    index_arr :array of link_t;

function FindArr(node_num:Int64):link_t;
var i :integer;
begin
  WriteLn(Length(index_arr));
  for i := 0 to High(index_arr) do
  begin
    if (index_arr[i]^.node_number = node_num) then
    begin
      FindArr:=index_arr[i];
      SetLength(index_arr, Length(index_arr)-1);
      Exit;
    end;
  end;
  FindArr := nil;
end;

function FindTop:link_t;
var i :integer;
    s :Int64;
begin
  s := 0;
  for i:=High(index_arr) downto 0 do s := round(Max(CntEl(index_arr[i]), s));
  for i:=High(index_arr) downto 0 do
  begin
    if (CntEl(index_arr[i]) = s)
    then
    begin
      FindTop := index_arr[i];
      Exit;
    end;
  end;
  FindTop := nil;
end;

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
  until (c <> ' ');
end;
begin
  SetLength(index_arr, 0);
  line := 0;
  flag_eof := False;
  flag_edges := False;
  while not(eof(f)) do
  begin
    flag_eoln := False;
    line := line + 1;
    Probel_reset(c);
    if (flag_eof) then
    begin
      WriteLn('No data found in file');
      Halt(0);
    end;
    if not(flag_eoln) then
    begin
      disgraph := '';
      while (c <> ' ') and (c <> '#') do
      begin
        disgraph := disgraph + c;
        if not(eoln(f)) then Read(f, c)
        else Break;
      end;
      Probel_reset(c);
      if not(flag_eoln) and (c <> '#') then
      begin
        WriteLn('disgraph error');
        Halt(0);
      end;
      if (disgraph <> 'digraph') then
      begin
        WriteLn('disgraph error');
        Halt(0);
      end
      else Break;
    end;
    if not(eof(f)) then ReadLn(f)
    else
    begin
      WriteLn('Wrong input');
      Halt(0);
    end;
  end;
  disgraph := '';
  flag_eoln := False;
  while not(eof(f)) do
  begin
    flag_eoln := False;
    line := line + 1;
    Probel_reset(c);
    if (flag_eof) then
    begin
      WriteLn('No data found in file');
      Halt(0);
    end;
    if not(flag_eoln) then
    begin
      disgraph := '';
      while (c <> ' ') and (c <> '#') do
      begin
        disgraph := disgraph + c;
        if not(eoln(f)) then Read(f, c)
        else Break
      end;
      Probel_reset(c);
      if not(flag_eoln) and (c <> '#') then
      begin
        WriteLn('disgraph error');
        Halt(0);
      end;
      if (disgraph <> '{') then
      begin
        WriteLn('disgraph error');
        Halt(0);
      end
      else Break;
    end;
    if not(eof(f)) then ReadLn(f)
    else
    begin
      WriteLn('Wrong input');
      Halt(0);
    end;
  end;
  {$H+}
  while not(eof(f)) and not(flag_edges) do
  begin
    ReadLn(f, str);
    edge_num := 0;
    edge_pos := Pos('//edges', str);
    if (edge_pos <> 0) then
    begin
      flag_edges := True;
      {Проверка правильности строки}
    end
    else
    begin
      if (Length(str) > 0) then
      begin
      flag_com := False;
      com_pos := Pos('#', str);
      if (com_pos = 1) then flag_com := True
      else
      for i := 1 to com_pos-1 do
      begin
        if (str[i] <> ' ') then flag_com := False
        else flag_com := True;
      end;
      if flag_com then Continue;
      i := 1;
      while (str[i] = ' ') and (str[i] <> '#') and (i < Length(str)) do
      begin
        i:=i+1;
      end;
      while (str[i] <> ' ') and (str[i] <> '#') and (i < Length(str)) do
      begin
        if (str[i] >= '0') and (str[i] <= '9') then
        begin
          edge_num := edge_num*10 +ord(str[i]) - ord('0');
        end
        else
        begin
          WriteLn('edge_error');
          Halt(0);
        end;
        i:=i+1;
      end;
      if (edge_num <= 0) then
      begin
        WriteLn('edge_error');
        Halt(0);
      end;
      label_pos := Pos('[label="', str);
      if (label_pos <> 0) then
      begin
        for j := i to label_pos-1 do
        if (str[i] <> ' ') then
        begin
          WriteLn('error label');
          Halt(0);
        end;
        j := label_pos +8;
        if (j > Length(str)) then
        begin
          WriteLn('label_error');
          Halt(0);
        end;
        while (str[j] = ' ') and (j < Length(str)) do j := j+1;
        row_num := 0;
        while (str[j] <> ' ') and (j < Length(str)) do
        begin
          if (str[j] >= '0') and (str[j] <= '9') then
          begin
            row_num := row_num*10 +ord(str[j]) - ord('0');
          end
          else
          begin
            WriteLn('edge_error');
            Halt(0);
          end;
          j:=j+1;
        end;
        if (row_num <= 0) then
        begin
          WriteLn('row_number error');
          Halt(0);
        end;
        j := j+1;
        while (str[j] = ' ') and (j < Length(str)) do j := j+1;
        col_num := 0;
        while ((str[j] <> ' ') and (str[j] <> '\')) and
              (j < Length(str)) do
        begin
          if (str[j] >= '0') and (str[j] <= '9') then
          begin
            col_num := col_num*10 + ord(str[j]) - ord('0');
          end
          else
          begin
            WriteLn('edge_error');
            Halt(0);
          end;
          j:=j+1;
        end;
        if (col_num <= 0) then
        begin
          WriteLn('col_number error');
          Halt(0);
        end;
        if (j < Length(str)) then
        begin
          if (str[j + 1] <> 'n') then
          begin
            WriteLn('syntax error');
            Halt(0);
          end;  
        end
        else
        begin
          WriteLn('edge_error');
          Halt(0);
        end;
        j := j+2;
        num := '';
        while (str[j] <> '"') and (j < Length(str)) do
        begin
          num := num + str[j];
          j := j+1;
        end;
        Val(num, num_el, code);
        if (code <> 0) then
        begin
          WriteLn('element_error');
          Halt(0);
        end;
        h := Length(index_arr)+1;
        SetLength(index_arr, round(Max(Length(index_arr)+1, edge_num+1)));{получены данные}
        for k := h to High(index_arr) do
        index_arr[k]:=nil;
        new(a);
        index_arr[edge_num] := a;
        index_arr[edge_num]^.node_number := edge_num;
        index_arr[edge_num]^.row := row_num;
        index_arr[edge_num]^.column := col_num;
        index_arr[edge_num]^.element := num_el;
        index_arr[edge_num]^.right := nil;
        index_arr[edge_num]^.left := nil;
      end
      else
      begin
        WriteLn('error_label');
        Halt(0);
      end;
      end;
    end;
  end;
  if not(eof(f)) then Read(f, str)
  else
  begin
    WriteLn('Недостаточно данных для анализа');
    Halt(0);
  end;
  while not(eof(f)) do
  begin
    skob_pos := Pos('}', str);
    if (skob_pos <> 0) then
    begin
      for i:=1 to skob_pos do
      begin
        if (str[i] <> ' ') and (i <> skob_pos) then
        begin
          if (str[i] = '#') then Break;
          WriteLn('Wrong input digraph');
          Halt(0);
        end;
      end;
      if (str[i] = '#') then Continue;
      for i := skob_pos to Length(str) do
      begin
        if (str[i] <> ' ') and (i <> skob_pos) then
        begin
          if (str[i] = '#') then Break;
          WriteLn('Wrong input digraph');
          Halt(0);
        end;
      end;
      Break;
    end
    else
    begin
      edge_num0:=0;
      edge_num1:=0;
      edge_num2:=0;
      edge_num00:=0;
      if (Length(str) <> 0) then begin
      i := 1;
      while (str[i] = ' ') and (str[i] <> '#') and (i < Length(str)) do
      begin
        i:=i+1;
      end;
      while (str[i] <> ' ') and (str[i] <> '#') and (i < Length(str)) do
      begin
        if (str[i] >= '0') and (str[i] <= '9') then
        begin
          edge_num0 := edge_num0*10 +ord(str[i]) - ord('0');
        end
        else
        begin
          WriteLn('edge_error');
          Halt(0);
        end;
        i:=i+1;
      end;
      if (edge_num0 <= 0) then
      begin
        WriteLn('edge_error');
        Halt(0);
      end;
      if (str[i] <> ' ') then
      begin
        WriteLn('no probel');
        Halt(0);
      end;
      strel_pos := Pos('->', str);
      for j := i to strel_pos do
      begin
        if (str[j] <> ' ') and (j <> strel_pos) then
        begin
          WriteLn('Wrong input edges');
          Halt(0);
        end;
      end;
      if ((j+2) < Length(str)) then
      begin
        i := j+2;
        while (str[i] = ' ') and (str[i] <> '#') and
              (i < Length(str)) do
        begin
          i:=i+1;
        end;
        while (str[i] <> ' ') and (str[i] <> '#') and
              (i < Length(str)) do
        begin
          if (str[i] >= '0') and (str[i] <= '9') then
          begin
            edge_num1 := edge_num1*10 + ord(str[i]) - ord('0');
          end
          else
          begin
            WriteLn('edge_error');
            Halt(0);
          end;
          i:=i+1;
        end;
        if (edge_num1 <= 0) then
        begin
          WriteLn('edge_error');
          Halt(0);
        end;
      end
      else
      begin
        WriteLn('Wrong input');
        Halt(0);
      end;
      if (str[i] <> ' ') then
      begin
        WriteLn('no probel');
        Halt(0);
      end;
      label_pos_l := Pos('[label="L"];', str);
      label_pos_r := Pos('[label="R"];', str);
      if (label_pos_l = 0) and (label_pos_r <> 0) then
      begin
        for j:=i to label_pos_r do
        begin
          if (j <> label_pos_r) and (str[j] <> ' ') then
          begin
            WriteLn('Wrong input');
            Halt(0);
          end;
        end;
        edge_num2 := edge_num1;
      end
      else
      begin
        if (label_pos_l <> 0) and (label_pos_r = 0) then
        begin
          for j:=i to label_pos_l do
          begin
            if (j <> label_pos_l) and (str[j] <> ' ') then
            begin
              WriteLn('Wrong input');
              Halt(0);
            end;
          end;
        end
        else
        begin
          if (label_pos_r = 0) and (label_pos_l = 0) then
          begin
            WriteLn('Wrong format');
            Halt(0);
          end
          else
          begin
            for j:=i to label_pos_l do
            begin
              if (j <> label_pos_l) and (str[j] <> ' ') then
              begin
                WriteLn('Wrong input');
                Halt(0);
              end;
            end;
            {получение второй вершины}
            i := label_pos_l+12;
            if (Length(str) <= i) then
            begin
              WriteLn('Format errror');
              Halt(0);
            end;
            while (str[i] = ' ') and (str[i] <> '#') and
                  (i < Length(str)) do
            begin
              i:=i+1;
            end;
            while (str[i] <> ' ') and (str[i] <> '#') and
                  (i < Length(str)) do
            begin
            if (str[i] >= '0') and (str[i] <= '9') then
            begin
              edge_num00 := edge_num00*10 +ord(str[i]) - ord('0');
            end
            else
            begin
              WriteLn('edge_error');
              Halt(0);
            end;
            i:=i+1;
          end;
          if (edge_num00 <= 0) then
          begin
            WriteLn('edge_error');
            Halt(0);
          end;
          if (str[i] <> ' ') then
          begin
            WriteLn('no probel');
            Halt(0);
          end;
          j:=i;
          while (str[j] = ' ') and (j < Length(str)) do
          begin
            j:=j+1;
          end;
          if ((j+2) < Length(str)) then
          begin
            if ((str[j]+str[j+1]) <> '->') then
            begin
              WriteLn('strelka error');
              Halt(0);
            end;
            i := j+2;
            while (str[i] = ' ') and (str[i] <> '#') and
                  (i < Length(str)) do
            begin
              i:=i+1;
            end;
             while (str[i] <> ' ') and (str[i] <> '#') and
                   (i < Length(str)) do
            begin
              if (str[i] >= '0') and (str[i] <= '9') then
              begin
                edge_num2 := edge_num2*10 + ord(str[i]) - ord('0');
              end
              else
              begin
                WriteLn('edge_error1');
                Halt(0);
              end;
              i:=i+1;
              end;
              if (edge_num2 <= 0) then
              begin
                WriteLn('edge_error');
                Halt(0);
              end;
            end
            else
            begin
              WriteLn('Wrong input');
              Halt(0);
            end;
            if (str[i] <> ' ') then
            begin
              WriteLn('no probel');
              Halt(0);
            end;
          end;
        end;
      end;
    end;
    end;
    if (edge_num0 <> 0) then
    begin
      if (edge_num0 <> edge_num00) and (edge_num00 <> 0) then
      begin
        WriteLn('Wrong start edge');
        Halt(0);
      end;
      if (edge_num2 = 0) then
      begin
      if (index_arr[edge_num0] <> nil) then 
        index_arr[edge_num0]^.left := index_arr[edge_num1];
      end
      else
      begin
        if (edge_num2 = edge_num1) then
        begin
         if (index_arr[edge_num0] <> nil) then
          index_arr[edge_num0]^.right := index_arr[edge_num2];
        end
        else
        begin
         if (index_arr[edge_num0] <> nil) then
          index_arr[edge_num0]^.left := index_arr[edge_num1];
          index_arr[edge_num0]^.right := index_arr[edge_num2];
        end;
      end;
    end;
    if not(eof(f)) then ReadLn(f, str)
    else
    begin
      WriteLn('no end');
      Halt(0);
    end;
  end;
  ReadIndex := FindTop;
  SetLength(index_arr, 0);
  {$H-}
end;

procedure PrintIndex3(a:link_t; maxlength, depth, height,
                      num:integer; var cntnum:integer);
begin
  if (a<>nil) then
  begin
    if (depth = height) then
    begin
      Write('(node_num:', a^.node_number, ', ',
            a^.row, ', ', a^.column, ' ');
      Write(a^.element:maxlength:1, ' L:');
      if (a^.left <> nil) then Write(a^.left^.node_number)
      else Write('NULL');
      Write(' R:');
      if (a^.right = nil) then Write('+');
      if (a^.right <> nil) then Write(a^.right^.node_number)
      else Write('NULL');
      Write(') ');
      cntnum := cntnum + 1;
      if (cntnum = num) then WriteLn;
    end
    else 
    if (depth < height) then
    begin
      PrintIndex3(a^.left, maxlength, depth+1, height, num, cntnum);
      PrintIndex3(a^.right, maxlength, depth+1, height, num, cntnum);
    end
    else Exit;
  end;
end;

procedure PrintIndex1(a:link_t; maxlength:integer);
begin
  if (a <> nil) then
  begin
    Write('(node_num:', a^.node_number, ', ',
          a^.row, ', ', a^.column, ' ');
    Write(a^.element:maxlength:1, ' L:');
    if (a^.left <> nil) then Write(a^.left^.node_number)
    else Write('NULL');
    Write(' R:');
    if (a^.right <> nil) then Write(a^.right^.node_number)
    else Write('NULL');
    Write(')');
    WriteLn;
    if (a^.left <> nil) then begin Write(a^.node_number, '-(L)->');
    PrintIndex1(a^.left, maxlength); end;
    if (a^.right <> nil) then begin Write(a^.node_number, '-(R)->');
    PrintIndex1(a^.right, maxlength); end;
  end;
end;

end.
