type
    TGDTEntry = packed record
        LowLimit: Word;
        LowBase: Word;
        MiddleBase: Byte;
        Access: Byte;
        Granularity: Byte;
        HighBase: Byte;
    end;

    TGDTPtr = packed record
        Limit: Word;
        Base: LongWord;
    end;

var
	GDTList: array [0..4] of TGDTEntry;
	GDTPtr: TGDTPtr; export name 'GDTPtr';

procedure SetGate(Num: Byte; Base, Limit: LongWord; Acc, Gran: Byte);
procedure flushGDT; external name 'flushGDT';