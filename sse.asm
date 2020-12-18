default rel

global sepia_asm

%define c11 0.393
%define c12 0.769
%define c13 0.189
%define c21 0.349
%define c22 0.686
%define c23 0.168
%define c31 0.272
%define c32 0.534
%define c33 0.131

section .rodata
    red:      dd c11, c21, c31, c11, c21, c31, c11, c21, c31, c11
    green:    dd c12, c22, c32, c12, c22, c32, c12, c22, c32, c12
    blue:     dd c13, c23, c33, c13, c23, c33, c13, c23, c33, c13

section .text
sepia_asm:
    sub rsp, 16
    pxor  xmm6, xmm6 

    mov eax, dword [rdi]
    mov dword [rsp], eax
    mov dword [rsp+4], eax
    mov dword [rsp+8], eax
    mov eax, dword [rdi+12]
    mov dword [rsp+12], eax
    movups xmm0, [rsp]  

    mov eax, dword [rdi+4]
    mov dword [rsp], eax
    mov dword [rsp+4], eax
    mov dword [rsp+8], eax
    mov eax, dword [rdi+16]
    mov dword [rsp+12], eax
    movups xmm1, [rsp]

    mov eax, dword [rdi+8]
    mov dword [rsp], eax
    mov dword [rsp+4], eax
    mov dword [rsp+8], eax
    mov eax, dword [rdi+20]
    mov dword [rsp+12], eax
    movups xmm2, [rsp]  

    movups xmm3, [red]    
    movups xmm4, [green]  
    movups xmm5, [blue]  

    mulps xmm0, xmm3   
    mulps xmm1, xmm4    
    mulps xmm2, xmm5   

    addps xmm0, xmm1
    addps xmm0, xmm2   
    
    cvtps2dq xmm0, xmm0 
    packusdw xmm0, xmm0 
    packuswb xmm0, xmm0 
    punpcklbw xmm0, xmm6
    punpcklwd xmm0, xmm6 
    cvtdq2ps xmm0, xmm0 

    movups [rsi], xmm0  

    mov eax, dword [rdi+12]
    mov dword [rsp], eax
    mov dword [rsp+4], eax
    mov eax, dword [rdi+24]
    mov dword [rsp+8], eax
    mov dword [rsp+12], eax
    movups xmm0, [rsp]  

    mov eax, dword [rdi+16]
    mov dword [rsp], eax
    mov dword [rsp+4], eax
    mov eax, dword [rdi+28]
    mov dword [rsp+8], eax
    mov dword [rsp+12], eax
    movups xmm1, [rsp]  

    mov eax, dword [rdi+20]
    mov dword [rsp], eax
    mov dword [rsp+4], eax
    mov eax, dword [rdi+32]
    mov dword [rsp+8], eax
    mov dword [rsp+12], eax
    movups xmm2, [rsp]  

    movups xmm3, [red + 4]    
    movups xmm4, [green + 4] 
    movups xmm5, [blue + 4]   

    mulps xmm0, xmm3 
    mulps xmm1, xmm4   
    mulps xmm2, xmm5   

    addps xmm0, xmm1
    addps xmm0, xmm2      

    cvtps2dq xmm0, xmm0 
    packusdw xmm0, xmm0 
    packuswb xmm0, xmm0 
    punpcklbw xmm0, xmm6 
    punpcklwd xmm0, xmm6 
    cvtdq2ps xmm0, xmm0 

    movups [rsi+16], xmm0   

    mov eax, dword [rdi+24]
    mov dword [rsp], eax
    mov eax, dword [rdi+36]
    mov dword [rsp+4], eax
    mov dword [rsp+8], eax
    mov dword [rsp+12], eax
    movups xmm0, [rsp]      

    mov eax, dword [rdi+28]
    mov dword [rsp], eax
    mov eax, dword [rdi+40]
    mov dword [rsp+4], eax
    mov dword [rsp+8], eax
    mov dword [rsp+12], eax
    movups xmm1, [rsp]    

    mov eax, dword [rdi+32]
    mov dword [rsp], eax
    mov eax, dword [rdi+44]
    mov dword [rsp+4], eax
    mov dword [rsp+8], eax
    mov dword [rsp+12], eax
    movups xmm2, [rsp]      

    movups xmm3, [red + 8]    
    movups xmm4, [green + 8]  
    movups xmm5, [blue + 8]   

    mulps xmm0, xmm3   
    mulps xmm1, xmm4   
    mulps xmm2, xmm5    

    addps xmm0, xmm1
    addps xmm0, xmm2        

    cvtps2dq xmm0, xmm0 
    packusdw xmm0, xmm0 
    packuswb xmm0, xmm0 
    punpcklbw xmm0, xmm6 
    punpcklwd xmm0, xmm6 
    cvtdq2ps xmm0, xmm0 

    movups [rsi+32], xmm0  
    add rsp, 16
    ret

