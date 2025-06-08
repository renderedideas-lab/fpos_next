unit gdt;

interface

{$I gdt.inc}

implementation

uses video;

procedure SetGate(Num: Byte; Base, Limit: LongWord; Acc, Gran: Byte);
begin
	with GDTList[Num] do begin
		LowBase := (Base and $FFFF);
		MiddleBase := (Base shr 16) and $FF;
		HighBase := (Base shr 24) and $FF;

		LowLimit := (Limit and $FFFF);
		Granularity := ((Limit shr 16) and $0F) or (Gran and $F0);
		Access := Acc;
	end;
end;

end.