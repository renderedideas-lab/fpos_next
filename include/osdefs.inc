{ Make FPC 3.2.0 happy by defining dummy types }

Const
    FPC_EXCEPTION = 0;

    LineEnding = #13#10;
    sLineBreak = LineEnding;

    DirectorySeparator = '/';
    DriveSeparator = '';
    ExtensionSeparator = '.';
    PathSeparator = ':';

Type
    Cardinal = 0..$FFFFFFFF;
    
    Int8 = ShortInt;
    Int16 = SmallInt;
    Int32 = LongInt;
    Integer = Int32;
    
    UInt8 = Byte;
    UInt16 = Word;
    UInt32 = Cardinal;
    Uint64 = QWord;

    DWord = UInt32;
    PDWord = ^DWord;
    HRESULT = QWord;
    TTypeKind = QWord;
    
    PChar = ^Char;
    PByte = ^Byte;

    TExceptAddr = Record
    End;

    jmp_buf = Record
    End;

    PGuid = ^TGuid;
    TGuid = Record
        case Integer of
        1: (
            Data1: DWord;
            Data2: word;
            Data3: word;
            Data4: array [0 .. 7] of byte;
        );
        2: (
            D1: DWord;
            D2: word;
            D3: word;
            D4: array [0 .. 7] of byte;
        );
        3:
        ( { uuid fields according to RFC4122 }
            time_low: DWord; // The low field of the timestamp
            time_mid: word; // The middle field of the timestamp
            time_hi_and_version: word;
            // The high field of the timestamp multiplexed with the version number
            clock_seq_hi_and_reserved: byte;
            // The high field of the clock sequence multiplexed with the variant
            clock_seq_low: byte; // The low field of the clock sequence
            node: array [0 .. 5] of byte; // The spatially unique node identifier
        );
    End;

    Ppsf = ^Tpsf;
    Tpsf = Packed Record
        magic : UInt32;
        version : UInt32;
        headersize : UInt32;
        flags : UInt32;
        numglyph : UInt32;
        bytesperglyph : UInt32;
        height : UInt32;
        width : UInt32;
    End;

var
    ExitCode: HRESULT = 0; export name 'operatingsystem_result';