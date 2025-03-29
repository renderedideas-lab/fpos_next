const
    ColorWhite = $00FFFFFF;
    ColorRed = $00FF0000;
    ColorGreen = $0000FF00;
    ColorBlue = $000000FF;
    ColorBlack = $00000000;
    ColorSilver = $00C0C0C0;
    ColorGray = $00808080;
    ColorMaroon = $00800000;
    ColorYellow = $00FFFF00;
    ColorOlive = $00808000;
    ColorAqua = $0000FFFF;
    ColorTeal = $00008080;
    ColorNavy = $00000080;
    ColorFuchsia = $00FF00FF;
    ColorPurple = $00800080;

var
    CurrX: Integer = 0;
    CurrY: Integer = 0;
    CurrForeground: longint = ColorWhite;
    CurrBackground: longint = ColorBlack;

procedure Puts(s: PChar); overload;
procedure Puts(s: PChar; endStr: PChar); overload;
procedure Puts(i: integer); overload;
procedure ClearScreen;

procedure GoToX(NewX: Integer);
procedure GoToY(NewY: Integer);
procedure GoToPos(NewX, NewY: Integer);

procedure SetForegroundColor(fore: longint);
procedure SetBackgroundColor(back: longint);
procedure ResetForeground;
procedure ResetBackground;
procedure ResetColors;