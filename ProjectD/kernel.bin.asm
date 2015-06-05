00000000  55                push bp
00000001  89E5              mov bp,sp
00000003  57                push di
00000004  56                push si
00000005  83C4FC            add sp,byte -0x4
00000008  31C0              xor ax,ax
0000000A  8946F8            mov [bp-0x8],ax
0000000D  31C0              xor ax,ax
0000000F  8946F8            mov [bp-0x8],ax
00000012  EB35              jmp short 0x49
00000014  E83501            call word 0x14c
00000017  50                push ax
00000018  8B46F8            mov ax,[bp-0x8]
0000001B  0346FA            add ax,[bp-0x6]
0000001E  89C3              mov bx,ax
00000020  8B46F6            mov ax,[bp-0xa]
00000023  8807              mov [bx],al
00000025  44                inc sp
00000026  44                inc sp
00000027  8B46F8            mov ax,[bp-0x8]
0000002A  0346FA            add ax,[bp-0x6]
0000002D  89C3              mov bx,ax
0000002F  8A07              mov al,[bx]
00000031  30E4              xor ah,ah
00000033  50                push ax
00000034  E80901            call word 0x140
00000037  44                inc sp
00000038  44                inc sp
00000039  B87C00            mov ax,0x7c
0000003C  50                push ax
0000003D  E80001            call word 0x140
00000040  44                inc sp
00000041  44                inc sp
00000042  8B46F8            mov ax,[bp-0x8]
00000045  40                inc ax
00000046  8946F8            mov [bp-0x8],ax
00000049  8B46F8            mov ax,[bp-0x8]
0000004C  3D0200            cmp ax,0x2
0000004F  7CC3              jl 0x14
00000051  83C404            add sp,byte +0x4
00000054  5E                pop si
00000055  5F                pop di
00000056  5D                pop bp
00000057  C3                ret
00000058  55                push bp
00000059  89E5              mov bp,sp
0000005B  57                push di
0000005C  56                push si
0000005D  83C4FC            add sp,byte -0x4
00000060  31C0              xor ax,ax
00000062  8946FA            mov [bp-0x6],ax
00000065  EB66              jmp short 0xcd
00000067  31C0              xor ax,ax
00000069  8946F8            mov [bp-0x8],ax
0000006C  EB50              jmp short 0xbe
0000006E  31C0              xor ax,ax
00000070  50                push ax
00000071  8B46FA            mov ax,[bp-0x6]
00000074  B95000            mov cx,0x50
00000077  F7E9              imul cx
00000079  D1E0              shl ax,1
0000007B  50                push ax
0000007C  8B46F8            mov ax,[bp-0x8]
0000007F  050080            add ax,0x8000
00000082  0346F4            add ax,[bp-0xc]
00000085  44                inc sp
00000086  44                inc sp
00000087  50                push ax
00000088  B800B0            mov ax,0xb000
0000008B  50                push ax
0000008C  E89D00            call word 0x12c
0000008F  83C406            add sp,byte +0x6
00000092  B80500            mov ax,0x5
00000095  50                push ax
00000096  8B46FA            mov ax,[bp-0x6]
00000099  B95000            mov cx,0x50
0000009C  F7E9              imul cx
0000009E  D1E0              shl ax,1
000000A0  50                push ax
000000A1  8B46F8            mov ax,[bp-0x8]
000000A4  050180            add ax,0x8001
000000A7  0346F4            add ax,[bp-0xc]
000000AA  44                inc sp
000000AB  44                inc sp
000000AC  50                push ax
000000AD  B800B0            mov ax,0xb000
000000B0  50                push ax
000000B1  E87800            call word 0x12c
000000B4  83C406            add sp,byte +0x6
000000B7  8B46F8            mov ax,[bp-0x8]
000000BA  40                inc ax
000000BB  8946F8            mov [bp-0x8],ax
000000BE  8B46F8            mov ax,[bp-0x8]
000000C1  3DA000            cmp ax,0xa0
000000C4  7CA8              jl 0x6e
000000C6  8B46FA            mov ax,[bp-0x6]
000000C9  40                inc ax
000000CA  8946FA            mov [bp-0x6],ax
000000CD  8B46FA            mov ax,[bp-0x6]
000000D0  3D1100            cmp ax,0x11
000000D3  7C92              jl 0x67
000000D5  83C404            add sp,byte +0x4
000000D8  5E                pop si
000000D9  5F                pop di
000000DA  5D                pop bp
000000DB  C3                ret
000000DC  55                push bp
000000DD  89E5              mov bp,sp
000000DF  57                push di
000000E0  56                push si
000000E1  4C                dec sp
000000E2  4C                dec sp
000000E3  31C0              xor ax,ax
000000E5  8946FA            mov [bp-0x6],ax
000000E8  31C0              xor ax,ax
000000EA  8946FA            mov [bp-0x6],ax
000000ED  EB2F              jmp short 0x11e
000000EF  8B46FA            mov ax,[bp-0x6]
000000F2  034604            add ax,[bp+0x4]
000000F5  89C3              mov bx,ax
000000F7  8A07              mov al,[bx]
000000F9  84C0              test al,al
000000FB  7508              jnz 0x105
000000FD  B85000            mov ax,0x50
00000100  8946FA            mov [bp-0x6],ax
00000103  EB12              jmp short 0x117
00000105  8B46FA            mov ax,[bp-0x6]
00000108  034604            add ax,[bp+0x4]
0000010B  89C3              mov bx,ax
0000010D  8A07              mov al,[bx]
0000010F  30E4              xor ah,ah
00000111  50                push ax
00000112  E82B00            call word 0x140
00000115  44                inc sp
00000116  44                inc sp
00000117  8B46FA            mov ax,[bp-0x6]
0000011A  40                inc ax
0000011B  8946FA            mov [bp-0x6],ax
0000011E  8B46FA            mov ax,[bp-0x6]
00000121  3D5000            cmp ax,0x50
00000124  7CC9              jl 0xef
00000126  44                inc sp
00000127  44                inc sp
00000128  5E                pop si
00000129  5F                pop di
0000012A  5D                pop bp
0000012B  C3                ret
0000012C  55                push bp
0000012D  89E5              mov bp,sp
0000012F  1E                push ds
00000130  8B4604            mov ax,[bp+0x4]
00000133  8B7606            mov si,[bp+0x6]
00000136  8A4E08            mov cl,[bp+0x8]
00000139  8ED8              mov ds,ax
0000013B  880C              mov [si],cl
0000013D  1F                pop ds
0000013E  5D                pop bp
0000013F  C3                ret
00000140  55                push bp
00000141  89E5              mov bp,sp
00000143  8A4604            mov al,[bp+0x4]
00000146  B40E              mov ah,0xe
00000148  CD10              int 0x10
0000014A  5D                pop bp
0000014B  C3                ret
0000014C  55                push bp
0000014D  B400              mov ah,0x0
0000014F  CD16              int 0x16
00000151  5D                pop bp
00000152  C3                ret
00000153  BA6801            mov dx,0x168
00000156  1E                push ds
00000157  B80000            mov ax,0x0
0000015A  8ED8              mov ds,ax
0000015C  BE8400            mov si,0x84
0000015F  8CC8              mov ax,cs
00000161  894402            mov [si+0x2],ax
00000164  8914              mov [si],dx
00000166  1F                pop ds
00000167  C3                ret
