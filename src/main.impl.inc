function BCDToDecimal(bcd: Byte): Integer;
begin
    BCDToDecimal := ((bcd shr 4) * 10) + (bcd and $0F);
end;

procedure _start(); stdcall; [public, alias: '_start'];
var S: integer;
    // I: integer;
Begin

    S := Integer(bootboot.fb_scanline);

    If (S > 0) Then
    Begin
        Puts('Screen width:', ' ');
        Puts(bootboot.fb_width);

        Puts('Screen height:', ' ');
        Puts(bootboot.fb_height);

        Puts('Maximum lines:', ' ');
        Puts(bootboot.fb_height div _binary_font_psf_start.height);

        // ClearScreen;

        Puts('Hello from a simple BOOTBOOT kernel');
        Puts('This is FPOS NEXT, version 1.0.alpha.dddddddddddddddddddddddd'+ sLineBreak +
             'Made by Le Bao Nguyen and Danilo Bleul.' + sLineBreak +
             'This isssssssssssssssssssssss a verrrrrrrrrrrrrrrrrrrryyyyyyyyyyyyyyyyyy long text just to know if text wrapping works;)');

        Puts('C', ' ');
        SetBackgroundColor(ColorAqua);
        Puts('O', ' ');
        SetBackgroundColor(ColorNavy);
        Puts('L', ' ');
        SetForegroundColor(ColorFuchsia);
        Puts('O', ' ');
        SetForegroundColor(ColorYellow);
        Puts('U', ' ');
        SetBackgroundColor(ColorRed);
        Puts('R', ' ');
        SetForegroundColor(ColorOlive);
        Puts('S');

        ResetColors;

        Puts('bootboot.datetime entries:');
        Puts('Year:', ' ');
        Puts((BCDToDecimal(bootboot.datetime[0]) * 100) + BCDToDecimal(bootboot.datetime[1]));
        Puts('Month:', ' ');
        Puts(BCDToDecimal(bootboot.datetime[2]));
        Puts('Day:', ' ');
        Puts(BCDToDecimal(bootboot.datetime[3]));
        Puts('Hour:', ' ');
        Puts(BCDToDecimal(bootboot.datetime[4]));
        Puts('Minute:', ' ');
        Puts(BCDToDecimal(bootboot.datetime[5]));
        Puts('Second:', ' ');
        Puts(BCDToDecimal(bootboot.datetime[6]));
        Puts('1/100th second precision (which is zero on many platforms):', ' ');
        Puts(BCDToDecimal(bootboot.datetime[7]));

        Puts('Type help for available commands.');
        // Puts(bootboot.fb_height div _binary_font_psf_start.height);

        // for i := 0 to (bootboot.fb_height div _binary_font_psf_start.height) - 1 do
        //     Puts(i);
        // for i := 0 to 750 do
        //     Puts(i);

        Puts('[Doing] GDT initialization...');

        GDTPtr.Limit := SizeOf(GDTList) - 1;
        
        GDTPtr.Base := PUint(@GDTList[0]);
        
        GDT.SetGate(0, 0, 0, 0, 0); // nil descriptor
        GDT.SetGate(1, 0, $FFFFFFFF, $9A, $A); // Kernel space code
        GDT.SetGate(2, 0, $FFFFFFFF, $92, $C); // Kernel space data
        GDT.SetGate(3, 0, $FFFFFFFF, $FA, $A); // User space code
        GDT.SetGate(4, 0, $FFFFFFFF, $F2, $C); // User space data
        // TODO: Task state segment (TSS) descriptor

        Puts('[Doing] Flush GDT...');
        flushGDT;

        Puts('[Done] GDT initialization.');
    End;
    
    shutdown;
End;

procedure shutdown;
begin
    Puts('It is safe to to turn your computer off now.');
    asm
        cli
        hlt
    end;
end;