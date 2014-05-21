NAME = invoke
OBJS = $(NAME).obj
RES = $(NAME).res
$(NAME).exe: $(OBJS) $(RES)
Link /DEBUG /SUBSYSTEM:WINDOWS $(OBJS) $(RES)
$(RES): $(NAME).rc
Rc $(NAME).rc
.asm.obj:
Ml /c /coff $(NAME).asm