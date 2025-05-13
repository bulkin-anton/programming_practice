uses tree_unit      in 'modules/tree_unit.pas', 
     functions_unit in 'modules/functions_unit.pas',
     index_unit     in 'modules/index_unit.pas';

var index_name :string;
    slovo      :string;
    format     :Int64;
    code       :integer;
    maxlength  :Int64;
    i          :integer;
    h          :Int64;
    cntnum     :integer;
    index      :link_t;
    f          :text;

{
  Процедура обхода дерева на ассемблере
}

{$L ./otobr.obj}
function PrintIndexAsm(a:link_t):longword; stdcall; external name 'movtr';

{
  Печать путей в левое и правое поддеревья из корня
}

procedure Point(a:link_t; b:longint); stdcall; Public;
begin
    if (b<>0) then Write(a^.node_number, '-(L)->')
    else Write(a^.node_number, '-(R)->');
end;

{
  Печать элементов дерева
}

procedure PrintL(a:link_t); stdcall; Public;
begin
    Write('(node_num:', a^.node_number, ', ',
          a^.row, ', ', a^.column, ' ');
    Write(a^.element:4:1, ' L:');
    if (a^.left <> nil) then Write(a^.left^.node_number)
    else Write('NULL');
    Write(' R:');
    if (a^.right <> nil) then Write(a^.right^.node_number)
    else Write('NULL');
    Write(')');
    WriteLn;
end;
    
begin
  if (ParamCount <> 2) then
  begin
    WriteLn('Wrong number of parametrs');
    WriteLn('Enter name from /index respository of index');
    WriteLn('Enter type mode');
    WriteLn('1 - root, after - left subtree, then - right one');
    WriteLn('2 - ASM: root, after - left subtree, then - right one');
    WriteLn('3 - print from leaves to roots');
    Halt(0);
  end;
  index := nil;
  index_name := ParamStr(1);
  Assign(f, 'index/'+index_name+'.dot');
  {$I-}
  Reset(f);
  {$I+}
  if (IOResult <> 0) then
  begin
    WriteLn('file ', index_name, ' doesn`t exist');
    Halt(0);
  end;
  index := ReadIndex(f);
  Close(f);
  slovo := ParamStr(2);
  Val(slovo, format, code);
  if (code <> 0) then
  begin
    WriteLn('mode error');
    Halt(0);
  end;
  if (format <> 1) and (format <> 3) and (format <> 2) then
  begin
    WriteLn('mode error');
     Halt(0);
  end;
  if (index = nil) then begin WriteLn('no index'); Halt(0); end;
  maxlength := trunc(ln(abs(MaxTreeElement(index)))/ln(10) + 2);
  if (format = 1) then PrintIndex1(index, maxlength)
  else
  begin
    if (format = 3) then
    begin
      if (index <> nil) then
      begin
        h := Height(index);
        for i := h downto 1 do
        begin
          cntnum := 0;
          PrintIndex3(index, maxlength, 1, i, CntDepth(index,1,i), cntnum);
        end;
      end;
    end
    else
      if (index <> nil) then
      begin
        h := PrintIndexAsm(index);
        WriteLn('Height of the tree is - ', h);  
      end
      else WriteLn('Empty tree');
  end;
  DestroyTree(index);
end.
