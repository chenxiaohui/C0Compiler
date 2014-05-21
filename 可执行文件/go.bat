@echo off
masm\ml /c /coff %1.asm 
masm\link /subsystem:console %1.obj
