Procedure _start(); stdcall; [public, alias: '_start'];
var S: integer;
Begin

    S := Integer(bootboot.fb_scanline);

    If (S > 0) Then
    Begin
        Puts('Screen width:', ' ');
        Puts(bootboot.fb_width);

        Puts('Screen height:', ' ');
        Puts(bootboot.fb_height);

        ClearScreen;

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

        Puts('Type help for available commands.');
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