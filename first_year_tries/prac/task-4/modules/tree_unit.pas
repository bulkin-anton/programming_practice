unit tree_unit;

Interface

type
  link_t = ^tree_node_t;
  tree_node_t = record
    node_number :Int64;
    row, column :Int64;
    element     :double;
    left, right :link_t;
  end;
  rowEl_t = record
    row     :Int64;
    column  :Int64;
    element :double;
  end;
  mas_t = array of rowEl_t;


procedure DestroyTree(a :link_t);
function  Find(row, column :Int64; a :link_t) :link_t;
function  AddNode(number :double; row, column :Int64; 
                  var a :link_t; node_number :Int64) :boolean;
procedure PrintTree(a :link_t; num :integer);
procedure CollectRow(b :link_t; rw :Int64; var MatrixRowCollect :mas_t);
procedure SortArr(var Matrix :mas_t);
procedure InverseMatrix(a:link_t; var res:link_t);
function MaxTreeElement(a:link_t):double;
procedure RewriteIndex(var index, matrix :link_t);
function CntEl(a:link_t):int64;
function Height(a:link_t):Int64;
function CntDepth(a:link_t; depth, height:Int64):Int64;
procedure DeleteNode(var a:link_t; rows, columns:Int64);

Implementation
uses functions_unit in 'modules/functions_unit.pas';

procedure DestroyTree(a:link_t);
begin
  if (a <> nil) then
  begin
    DestroyTree(a^.left);
    DestroyTree(a^.right);
    Dispose(a);
    a := nil;
  end else Exit;
end;

function Height(a:link_t):Int64;
var l :Int64;
    r :Int64;
begin
  Height := 0;
  if (a <> nil) then
  begin
    l:=0;
    r:=0;
    if (a^.right <> nil) then r := Height(a^.right);
    if (a^.left <> nil) then l := Height(a^.left);
    if (l < r) then l := r;
    Height := 1 + l;
  end;
end;

procedure InverseMatrix(a:link_t; var res:link_t);
begin
   if (a<>nil) then
   begin
     AddNode(a^.element, a^.column, a^.row,
             res, a^.node_number);
     InverseMatrix(a^.left, res);
     InverseMatrix(a^.right, res);
   end;
end;

procedure SortArr(var Matrix :mas_t);
var k   :Int64;
    max :Int64;
    nom :Int64;
    i   :Int64;
    b   :rowEl_t;
begin
  k := Length(Matrix)-1;
  repeat
    max := Matrix[0].column;
    nom:=0;
    i := 1;
    while (i <> Length(Matrix)) do
    begin
      if (max < Matrix[i].column) then
      begin
        max := Matrix[i].column;
        nom := i;
      end;
      i := i + 1;
    end;
    b.column := Matrix[nom].column;
    b.row := Matrix[nom].row;
    b.element := Matrix[nom].element;
    Matrix[nom].column := Matrix[k].column;
    Matrix[nom].row := Matrix[k].row;
    Matrix[nom].element := Matrix[k].element;
    Matrix[k].column := b.column;
    Matrix[k].row := b.row;
    Matrix[k].element := b.element;
    k := k - 1;
  until (k = 0);
end;

function Find(row, column :Int64; a:link_t):link_t;
begin
  if (a <> nil) then
  begin
    if (a^.row = row) and (a^.column = column)
    then Find := a
    else
    begin
    if (Find(row, column, a^.left) <> nil) then
    Find := Find(row, column, a^.left)
    else if (Find(row, column, a^.right) <> nil) then
    Find := Find(row, column, a^.right)
    else Find := nil;
    end;
  end
  else Find := nil;
end;

function AddNode(number :double; row, column :Int64;
                 var a :link_t; node_number :Int64):boolean;
begin
  if (a <> nil) then
  begin
    if (Comparis(a^.row, a^.column, row, column) = -1) then
      AddNode := AddNode(number, row, column,
                         a^.right, node_number)
    else 
    if (Comparis(a^.row, a^.column, row, column) = 1) then
      AddNode := AddNode(number, row, column,
                         a^.left, node_number)
    else
    begin
      AddNode := False;
      a^.element := number;
    end;
  end
  else
  begin
    new(a);
    a^.row := row;
    a^.column := column;
    a^.left := nil;
    a^.right := nil;
    a^.node_number := node_number;
    a^.element := number;
    AddNode := True;
  end;
end;

procedure PrintTree(a:link_t; num:integer);
var i :integer;
begin
  if (a <> nil) then
  begin
    if (a^.right <> nil) then Printtree(a^.right, num + 1);
    if (num <> 0) then for i := 1 to num do Write('*');
    WriteLn('(', a^.row, ' ', a^.column, ' ',
            a^.element, ' ', a^.node_number, ')');
    if (a^.left <> nil) then Printtree(a^.left, num + 1);
  end
  else WriteLn('no_tree');
end;

function CntDepth(a:link_t; depth, height:Int64):Int64;
begin
  if (a<>nil) then
  begin
    if (depth = height) then CntDepth := 1
    else if (depth < height) then
      CntDepth := CntDepth(a^.left, depth+1, height) +
                  CntDepth(a^.right, depth+1, height)
    else CntDepth := 0;
    end
    else CntDepth := 0;
end;


procedure CollectRow(b:link_t; rw :Int64; var matrixRowCollect :mas_t);
begin
  if (b <> nil) then
  begin
    if (b^.row = rw) then
    begin
      SetLength(matrixRowCollect, Length(matrixRowCollect) + 1);
      MatrixRowCollect[Length(matrixRowCollect)-1].row := rw;
      MatrixRowCollect[Length(matrixRowCollect)-1].column := b^.column;
      MatrixRowCollect[Length(matrixRowCollect)-1].element := b^.element;
      CollectRow(b^.right, rw, matrixRowCollect);
      CollectRow(b^.left, rw, matrixRowCollect);
    end
    else
    begin
      if (b^.row > rw) then CollectRow(b^.left, rw, matrixRowCollect);
      if (b^.row < rw) then CollectRow(b^.right, rw, matrixRowCollect);
    end;
  end;
end;

function MaxTreeElement(a:link_t):double;
begin
  if (a <> nil) then
    MaxTreeElement := Max(Max(MaxTreeElement(a^.left),
                      MaxTreeElement(a^.right)), a^.element)
  else MaxTreeElement := 0.0;
end;

procedure DeleteNode(var a:link_t; rows, columns:Int64);

var q :link_t;

procedure Case1;
begin
  q^.row := a^.left^.row;
  q^.column := a^.left^.column;
  q^.element := a^.left^.element;
  q := a^.left;
  a^.left := a^.left^.left;
end;

procedure Ki(var a:link_t);
begin
  with a^ do
  if (right <> nil) then Ki(right)
  else
  begin
    q^.row := a^.row;
    q^.column := a^.column;
    q^.element := a^.element;
    q := a;
    a := a^.left;
  end;
end;

begin
  if (a = nil) then Exit;
  with a^ do
    if (Comparis(row, column, rows, columns) = -1) then
      DeleteNode(right, rows, columns)
    else if (Comparis(row, column, rows, columns) = 1) then
      DeleteNode(left, rows, columns)
    else
    begin
      q:=a;
      if (left = nil) and (right = nil) then a := nil
      else if (left = nil) then a := right
      else if (right = nil) then a := left
      else if (left^.right = nil) then Case1
      else Ki(left);
      Dispose(q);
    end;
end;

function CntEl(a:link_t):int64;
var s :int64;
begin
  if (a <> nil) then
  begin
    s:= 1;
    if (a^.right <> nil) then s := s + CntEl(a^.right);
    if (a^.left <> nil) then s := s + CntEl(a^.left);
    CntEl := s;
  end
  else CntEl := 0;
end;

procedure RewriteIndex(var index, matrix :link_t);
{var a:link_t;
procedure MatrixChange(a:link_t);
begin
  if (a<>nil) then
  begin
    MatrixChange(a^.right);
    MatrixChange(a^.left);
    AddNode(a^.element, a^.row, a^.column, index, 1);
  end;
end;}
begin
  {a := nil;
  if (matrix <> nil) then
  begin
    a := Find(matrix^.row, matrix^.column, index);
    if (a <> nil) then
    begin
      a^.element := matrix^.element;
      RewriteIndex(index, matrix^.right);
      if (index^.left <> nil) then
      RewriteIndex(index^.left, matrix^.left)
      else RewriteIndex(index, matrix^.left);
      if (index^.right <> nil) then
      RewriteIndex(index^.right, matrix^.right)
      else RewriteIndex(index, matrix^.right);
    end
    else
    begin
      AddNode(matrix^.element, matrix^.row, matrix^.column, index, CntEl(index) + 1);
      RewriteIndex(index, matrix^.right);
      RewriteIndex(index, matrix^.left);
    end;
  end;}
end;

end.
