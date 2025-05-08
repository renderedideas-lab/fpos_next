procedure Puts(s: PChar); inline;
begin
    Puts(s, nil);
end;

procedure Puts(s: PChar; endStr: PChar);
Var
    X : Integer;
    Y : Integer;
    Line : Integer;
    Mask : Byte;
    Offs : Integer;
    BytesPerRow : Integer;
    Glyph : PByte; // glyph of the character to be rendered
    P : PDword;
    S2: integer;
    YPos: integer;

    procedure NewLine;
    begin
        Inc(YPos, (_binary_font_psf_start.height + 1));
        
        // Puts(CurrY, ' ');
        
        if (CurrY >= (bootboot.fb_height div (_binary_font_psf_start.height + 1))) or
           (CurrX >= (bootboot.fb_width  div (_binary_font_psf_start.width  + 1))) then
        begin
            Scroll;
            YPos := (Integer(bootboot.fb_height) - 1) * ((_binary_font_psf_start.height + 1));
        end
        else
            Inc(CurrY);
        
        CurrX := 0;
    end;

begin
    YPos := CurrY * (_binary_font_psf_start.height + 1);

    // Needs comments about how this works.
    // But basically: find the right glyph for the character,
    // calculate character width & height then print the character.

    // Number of bytes per row.
    S2 := Integer(bootboot.fb_scanline);

    // This should partially help:
    // https://en.wikipedia.org/wiki/PC_Screen_Font#File_bitmaps
    BytesPerRow := (_binary_font_psf_start.width + 7) shr 3;
    
    while (s^ <> #0) do
    begin
        // Check for new line characters
        // New vocabulary addition: carriage return (#10)
        // moves, in this function, CurrX, to zero.
        // TLDR: jumps to the start of the line.
        if (s^ = #13) then begin
            NewLine;
            Inc(s);
            Continue;
        end;

        if (s^ = #10) then begin
            Inc(s);
            CurrX := 0;
            Continue;
        end;

        // Get the glyph address for the character we're going to render
        Glyph := PByte(
            @_binary_font_psf_start + _binary_font_psf_start.headersize +
            Integer(s^) * _binary_font_psf_start.bytesperglyph // location of the character in the font
        );
        
        Offs := (CurrX * (_binary_font_psf_start.width  + 1)* 4) + S2 * YPos;
        //               ^^ glyph width + 0 spacing bonus
        //                                              ^ Pixels are stored as 32-bit/4 byte values
        
        for Y := 0 to (_binary_font_psf_start.height - 1) do
        begin
            Line := Offs;
            Mask := 1 shl (_binary_font_psf_start.width - 1);

            for X := 0 to (_binary_font_psf_start.width - 1) do
            begin
                // Locate where to draw
                P := PDword(@fb + Line);

                // Set the fore/background.
                If ((Glyph^ and Mask) <> 0) Then
                    P^ := Currforeground
                Else
                    P^ := CurrBackground;

                Mask := Mask shr 1;
                Inc(Line, 4);
            End;
        
            Inc(Glyph, BytesPerRow);
            Inc(Offs, Integer(bootboot.fb_scanline));
        End;

        if CurrX < bootboot.fb_width then
            Inc(CurrX)
        else
            NewLine;

        Inc(s);
    End;

    // Now handle the "suffix"
    if (endStr = nil) or (endStr = PChar(sLineBreak)) then
        NewLine
    else if (endStr <> PChar('')) then
        Puts(endStr, '');
end;

procedure Puts(i: integer); inline;
begin
    Puts(i, nil);
end;

// Taken from OSDev wiki
procedure Puts(i: integer; endStr: PChar);
var
    buffer: array [0..11] of Char;
    str: PChar;
    digit: DWORD;
    minus: Boolean;
begin
    str := @buffer[11];
    str^ := #0;

    if (i < 0) then
    begin
        digit := -i;
        minus := True;
    end
    else begin
        digit := i;
        minus := False;
    end;

    repeat
        Dec(str);
        str^ := Char((digit mod 10) + Byte('0'));
        digit := digit div 10;
    until (digit = 0);

    if (minus) then
    begin
        Dec(str);
        str^ := '-';
    end;

    Puts(str, endStr);
end;

procedure GoToX(NewX: Integer); inline;
begin
    // FIXME: This is not the right way to do this.
    Assert(NewX <= Integer(bootboot.fb_width));
    Assert(NewX >= 0);
    // End FIXME
    CurrX := NewX;
end;

procedure GoToY(NewY: Integer); inline;
begin
    // FIXME: Same reason as GoToX
    Assert(NewY <= Integer(bootboot.fb_height));
    Assert(NewY >= 0);
    // End FIXME
    CurrY := NewY;
end;

procedure GoToPos(NewX, NewY: Integer); inline;
begin
    GoToX(NewX);
    GoToY(NewY);
end;

procedure ClearScreen;
var X, Y, S: integer;
    P: PDWord;
begin
    S := integer(bootboot.fb_scanline);

    for Y := 0 to Integer(bootboot.fb_height) do
    begin
        for X := 0 to integer(bootboot.fb_width) do
        begin
            P := PDWord(@fb + (X * (_binary_font_psf_start.width+1) * 4) + S * Y);
            P^ := ColorBlack;
        end;
    end;

    GoToPos(0, 0);
end;

procedure SetforegroundColor(fore: longint); inline;
begin
    Currforeground := fore;
end;

procedure SetBackgroundColor(back: longint); inline;
begin
    CurrBackground := back;
end;

procedure Resetforeground; inline;
begin
    Currforeground := ColorWhite;
end;

procedure ResetBackground; inline;
begin
    CurrBackground := ColorBlack;
end;

procedure ResetColors;
begin
    Resetforeground;
    ResetBackground;
end;

procedure Scroll;
begin
end;

end.