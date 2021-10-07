#MACROS

AOUTS =   main.c basicfun.c bg.c builtincommand.c baywatch.c builtls.c signalkill.c control.c cdcom.c display.c  pinfo.c history.c pwd.c fg.c echo.c redirection.c piping.c repeat.c mergesort.c job.c 

a.out : $(AOUTS)
	$(CC) $(CFLAGS) ${AOUTS} $(LDFLAGS) -o $@