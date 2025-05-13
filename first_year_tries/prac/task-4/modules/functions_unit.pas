unit functions_unit;

Interface
function Comparis(a1, a2, b1, b2 :Int64):integer;
function Max(a, b :double)               :double;

Implementation

function Comparis(a1, a2, b1, b2 :Int64):integer;
begin
  if ((a1 < b1) or ((a1 = b1) and (a2 < b2))) then
    Comparis := -1
  else
  begin
    if ((a1 = b1) and (a2 = b2)) then
      Comparis := 0
    else
      Comparis := 1;
  end;
end;

function Max(a, b:double):double;
begin
  if (abs(a) > abs(b)) then Max := a
  else Max := b;
end;

end.
