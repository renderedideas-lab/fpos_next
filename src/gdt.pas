unit gdt;

interface

var
	GDTList: array [0..4] of TGDTEntry;
	GDTPtr: TGDTPtr; export name 'GDTPtr';

procedure SetGate(Num: Byte; Base, Limit: LongWord; Acc, Gran: Byte);
procedure flushGDT; external name 'flushGDT';

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