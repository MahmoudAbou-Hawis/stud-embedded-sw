
#Compilation variables section
C_COMPILER = gcc
COMPILATION_FLAGS = -O0 -std=c99 -Wall
C_LINKER = gcc
LINKER_FLAGS = 

#Source files section
vpath %.c ../6_Tests/
vpath %.c ../1_MCAL/
vpath %.c ../2_HWAL/
vpath %.c ../3_App/
vpath %.c ../4_Libraries/
vpath %.c ../5_Configs/

#Header files section
INCLUDE_FLAGS = -I ../5_Configs/ \
-I ../1_MCAL/ \
-I ../2_HWAL/ \
-I ../3_App/ \
-I ../4_Libraries/ \
-I ../6_Tests

#Object files section
OBJECTS_DIRECTORY = ./0_Outputs/
OBJECTS.o = main.o \
Vector.o

OBJECTS.exe = main.exe

#Targets section
.PHONY: all
all: $(OBJECTS.exe)

$(OBJECTS.exe): %.exe: $(OBJECTS.o)
	$(C_LINKER) $(LINKER_FLAGS) $(addprefix $(OBJECTS_DIRECTORY),$^) -o $(OBJECTS_DIRECTORY)$@

$(OBJECTS.o): %.o: %.c
	$(C_COMPILER) $(COMPILATION_FLAGS) $(INCLUDE_FLAGS) -c $< -o $(OBJECTS_DIRECTORY)$@

.PHONY: clean
clean:
	rm -rf $(OBJECTS_DIRECTORY)*
