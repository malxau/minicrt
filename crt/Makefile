

all: minicrt.lib

clean:
	if exist *.obj erase *.obj
	if exist *.lib erase *.lib
	if exist *.pdb erase *.pdb
	if exist *~ erase *~
	if exist *.manifest erase *.manifest


DEBUG=0

OBJS=env.obj      \
     envw.obj     \
     file.obj     \
     filew.obj    \
     mem.obj      \
     printf.obj   \
     printfw.obj  \
     printfsz.obj \
     rand.obj     \
     string.obj   \
     stringw.obj  \
     ep_cons.obj  \
     ep_consw.obj \
     ep_dll.obj   \
     ep_gui.obj   \
     ep_guiw.obj  \

BIGMATH_OBJS=bigdiv.obj \
			 bigdvrm.obj \
			 bigmul.obj \
			 bigrem.obj \
			 bigshl.obj \
			 bigshr.obj \

ML=ml.exe
LIB=link.exe -lib
LIB_NOLOGO=-nologo

CFLAGS=-nologo -W3 -MT
LDFLAGS=

!IF $(DEBUG)==1
CFLAGS=$(CFLAGS) -Zi -Od
!ELSE
CFLAGS=$(CFLAGS) -O1syi -Gy -Gs9999
!ENDIF

#
# Probe for more esoteric aspects of compiler behavior.
# Apparently pragma doesn't cut it for -GS-, and this is
# the most critical one for Minicrt.  MP is a perf
# optimization that only exists on newer compilers, so
# skip the probe on old ones.
#

!IF [$(CC) -GS- 2>&1 | find "unknown" >NUL]>0
CFLAGS=$(CFLAGS) -GS-
!IF [$(CC) -? 2>&1 | find "/MP" >NUL]==0
CFLAGS=$(CFLAGS) -MP
!ENDIF
!ENDIF

#
# Really old compiler support, when link.exe was
# link32.exe and didn't support -nologo
#

!IF [$(LIB) 2>&1 | find "Microsoft" >NUL]>0
!IF [link32.exe 2>&1 | find "Microsoft" >NUL]==0
LIB=link32.exe -lib
LIB_NOLOGO=
!ENDIF
!ENDIF

# 
# Check is ml.exe is present.  If so, the bigmath objects can be
# rebuilt, otherwise use prebuilt ones.
#

!IF [$(ML) 2>&1 | find "Microsoft" >NUL]>0
ML=
!ENDIF

#
# Check if we're compiling for x86 and if so include bigmath. This isn't
# needed on 64 bit systems and for non-x86 32 bit systems we don't have
# an implementation anyway.  This check is correct for Visual C++ 2 and
# newer; older systems don't have 64 bit math anyway.
#

!IF [$(CC) 2>&1 | find "x86" >NUL]==0
OBJS=$(OBJS) $(BIGMATH_OBJS)
!ENDIF

#
# If the compiler does read only string pooling, use that.  If it does
# unconditional string pooling, use that.
#

!IF [$(CC) -GF 2>&1 | find "unknown" >NUL]>0
CFLAGS=$(CFLAGS) -GF
!ELSE
CFLAGS=$(CFLAGS) -Gf
!ENDIF

minicrt.lib: $(OBJS)
	@$(LIB) $(LIB_NOLOGO) $(LDFLAGS) $(OBJS) /out:minicrt.lib

!IFDEF _NMAKE_VER
.c.obj::
!ELSE
.c.obj:
!ENDIF
	@$(CC) $(CFLAGS) -c $<


!IF "$(ML)"!=""
.asm.obj:
	@$(ML) /nologo /coff /c $<
!ELSE
.asm.obj:
	@echo i386\$@ (copy binary)
	@copy i386\$@ .
!ENDIF

