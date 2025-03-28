{ imported virtual addresses, see linker script }
Var
    bootboot : Tbootboot; external;                 { see bootboot.inc }
    environment : Array[0..4095] of Char; external; { configuration, UTF-8 text key=value pairs }
    fb : Byte; external;                            { linear framebuffer mapped }
    _binary_font_psf_start : Tpsf; external;

Procedure _start(); stdcall;