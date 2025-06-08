unit interr;

interface

type
    TInterruptHandler = procedure;
    PInterruptHandler = ^TInterruptHandler;

    TInterruptDes = packed record
        AddressLow: uint16;
        Selector: uint16;
        Ist: uint8;
        Flags: uint8;
        AddressMid: uint16;
        AddressHigh: uint32;
        Reserved: uint32;
    end;

    PInterruptDes = ^TInterruptDes;

    TInterruptReistry = packed record
        Limit: uint16;
        Base: uint64;
    end;

    PInterruptRegistry = ^TInterruptReistry;

    TInterruptArr = array[0..255] of PInterruptDes;

var
    IDT: TInterruptArr;

procedure SetIDTEntry(vect: uint8; handler: PInterruptHandler; dpl: uint8);
procedure LoadIDT(address: PInterruptReistry);

implementation

procedure SetIDTEntry(vect: uint8; handler: PInterruptHandler; dpl: uint8);
var
    address: uint64;
    entry: PInterruptDes;

begin
    address := PUint64(handler);
    with IDT[vector] do begin
        AddressLow := address and $FFFF;
        AddressMid := (address shr 16) and $FFFF;
        AddressHigh := address shr 32;
        //...
    end;
end;