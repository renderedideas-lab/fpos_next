{*
 *
 * Copyright (C) 2017 - 2021 bzt (bztsrc@gitlab)
 * Copyright (C) 2025 achief-ws and others
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This file is part of the FPOS project.
 *
 *}

Unit main;

{$if FPC_FULLVERSION<30200}
  {$fatal At least FPC 3.2.0 is required to compile the compiler}
{$endif}

Interface

{$I main.inc}
{$I video.inc}

Implementation

{******************************************
 * Entry point, called by BOOTBOOT Loader *
 ******************************************}
Procedure _start(); stdcall; [public, alias: '_start'];
var S: integer;
Begin

    S := Integer(bootboot.fb_scanline);

    If (S > 0) Then
    Begin
        { say hello }
        Puts('Hello from a simple BOOTBOOT kernel');
        Puts('This is FPOS NEXT, version 1.0.alpha.', ColorBlue, ColorRed);
    End;
    { hang for now }
    While (True) Do;
End;

procedure Puts(s: PChar);
begin
    Puts(s, ColorWhite);
end;

procedure Puts(s: PChar; color: longint);
begin
    Puts(s, color, ColorBlack);
end;

procedure Puts(s: PChar; color: longint; background: longint);
Var
    X : Integer;
    Y : Integer;
    Kx : Integer; // the position of the current character in s
    Line : Integer;
    Mask : Byte;
    Offs : Integer;
    Bpl : Integer;
    Glyph : PByte; // glyph of the character to be rendered
    P : PDword;
    S2: integer;
Begin
    S2 := Integer(bootboot.fb_scanline);
    Bpl := (_binary_font_psf_start.width + 7) shr 3;
    
    While (s^ <> #0) Do
    Begin
        Glyph := PByte(@_binary_font_psf_start + _binary_font_psf_start.headersize +
                 Integer(s^) * _binary_font_psf_start.bytesperglyph );
        
        Offs := (CurrX * (_binary_font_psf_start.width+1) * 4) + S2 * CurrY;
        
        For Y := 0 to (_binary_font_psf_start.height-1) Do
        Begin
            Line := Offs;
            mask := 1 shl (_binary_font_psf_start.width-1);

            For X := 0 to (_binary_font_psf_start.width-1) Do
            Begin
                P := PDword(@fb + Line);

                If ((Glyph^ and Mask) <> 0) Then
                    P^ := color // <- this is the foreground, because we can
                Else
                    P^ := background; // <- and this is the background, as the statement suggests.

                Mask := Mask shr 1;
                Line := Line + 4;
            End;

            P := PDword(@fb + Line);
            P^ := background;
            
            Glyph := Glyph + Bpl;
            Offs := Offs + Integer(bootboot.fb_scanline);
        End;

        Inc(s);
        Inc(CurrX);
    End;

    Inc(CurrY,_binary_font_psf_start.height + 1);
    CurrX := 0;
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

End.
