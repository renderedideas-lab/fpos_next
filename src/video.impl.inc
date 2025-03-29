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

Begin
    // Needs comments about how this works.
    // But basically: find the right glyph for the character,
    // calculate character width & height then print the character.

    // Number of bytes per row.
    S2 := Integer(bootboot.fb_scanline);

    // Someone explain this.
    // This should partially help:
    // https://en.wikipedia.org/wiki/PC_Screen_Font#File_bitmaps
    BytesPerRow := (_binary_font_psf_start.width + 7) shr 3;
    
    While (s^ <> #0) Do
    Begin

        // Check for new line characters
        // New vocabulary addition: carriage return (#10)
        // moves, in this function, CurrX, to zero.
        // TLDR: jumps to the start of the line.
        if (s^ = #13) or (s^ = #10) then
        begin
            CurrX := 0;
            Inc(s);

            if (s^ = #13) then
                Inc(CurrY, _binary_font_psf_start.height + 1);
            continue;
        end;

        // Get the glyph address for the character we're going to render
        Glyph := PByte(
            @_binary_font_psf_start + _binary_font_psf_start.headersize +
            Integer(s^) * _binary_font_psf_start.bytesperglyph // location of the character in the font
        );
        
        Offs := (CurrX * _binary_font_psf_start.width * 4) + S2 * CurrY;
        //               ^^ glyph width + 0 spacing bonus
        //                                              ^ Pixels are stored as 32-bit/4 byte values
        
        For Y := 0 to (_binary_font_psf_start.height-1) Do
        Begin
            Line := Offs;
            Mask := 1 shl (_binary_font_psf_start.width - 1);

            For X := 0 to (_binary_font_psf_start.width - 1) Do
            Begin
                // Locate where to draw
                P := PDword(@fb + Line);

                // Set the fore/background.
                If ((Glyph^ and Mask) <> 0) Then
                    P^ := CurrForeground
                Else
                    P^ := CurrBackground;

                Mask := Mask shr 1;
                Line := Line + 4;
            End;
        
            Glyph := Glyph + BytesPerRow;
            Offs := Offs + Integer(bootboot.fb_scanline);
        End;

        Inc(s);

        if (CurrX < bootboot.fb_width Div (_binary_font_psf_start.width+1)) then
            Inc(CurrX)
        else begin
            Inc(CurrY, _binary_font_psf_start.height + 1);
            CurrX := 0;
        end;
    End;

    // Now handle the "suffix"
    if (endStr = nil) then
    begin
        Inc(CurrY, _binary_font_psf_start.height + 1);
        CurrX := 0;
    end
    else if (endStr <> PChar('')) then
        Puts(endStr, '');
End;

procedure GoToX(NewX: Integer);
begin
    Assert(NewX <= Integer(bootboot.fb_width));
    Assert(NewX >= 0);
    CurrX := NewX;
end;

procedure GoToY(NewY: Integer);
begin
    Assert(NewY <= Integer(bootboot.fb_height));
    Assert(NewY >= 0);
    CurrY := NewY;
end;

procedure GoToPos(NewX, NewY: Integer);
begin
    GoToX(NewX);
    GoToY(NewY);
end;

// Taken from OSDev wiki
procedure Puts(i: integer);
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
    else
    begin
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

    Puts(str);
end;

procedure ClearScreen;
var W, H, X, Y, S: integer;
    P: PDWord;
begin
    S := integer(bootboot.fb_scanline);
    W := Integer(bootboot.fb_width);
    H := Integer(bootboot.fb_height);

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

procedure SetForegroundColor(fore: longint);
begin
    CurrForeground := fore;
end;

procedure SetBackgroundColor(back: longint);
begin
    CurrBackground := back;
end;

procedure ResetForeground; inline;
begin
    CurrForeground := ColorWhite;
end;

procedure ResetBackground; inline;
begin
    CurrBackground := ColorBlack;
end;

procedure ResetColors;
begin
    ResetForeground;
    ResetBackground;
end;