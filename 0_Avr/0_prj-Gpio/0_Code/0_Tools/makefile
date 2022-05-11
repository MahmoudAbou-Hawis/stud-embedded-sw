
#Compilation variables section
C_COMPILER = avr-gcc
COMPILATION_FLAGS = -O0 -DF_CPU=16000000UL -mmcu=atmega328p
C_LINKER = avr-gcc
LINKER_FLAGS = -mmcu=atmega328p
C_OBJ_COPY = avr-objcopy
OBJ_COPY_FLAGS = -O ihex -R .eeprom

#Source files section
vpath %.c ../1_MCAL/
vpath %.c ../2_HWAL/
vpath %.c ../3_App/
vpath %.c ../4_Libraries/
vpath %.c ../5_Configs/
vpath %.c ../6_Tests/

#Header files section
INCLUDE_FLAGS = -I ../1_MCAL/ \
-I ../2_HWAL/ \
-I ../3_App/ \
-I ../4_Libraries/ \
-I ../5_Configs/ \
-I ../6_Tests/

#Object files section
OBJECTS_DIRECTORY = ./0_Outputs/
OBJECTS.o = main.o \
GPIO.o
OBJECTS.elf = FW.elf
OBJECTS.hex = FW.hex

#Targets section
.PHONY: all
all: $(OBJECTS.hex)

$(OBJECTS.hex): %.hex: %.elf
	$(C_OBJ_COPY) $(OBJ_COPY_FLAGS) $(addprefix $(OBJECTS_DIRECTORY),$<) $(OBJECTS_DIRECTORY)$@

$(OBJECTS.elf): %.elf: $(OBJECTS.o)
	$(C_LINKER) $(LINKER_FLAGS) $(addprefix $(OBJECTS_DIRECTORY),$^) -o $(OBJECTS_DIRECTORY)$@

$(OBJECTS.o): %.o: %.c
	$(C_COMPILER) $(COMPILATION_FLAGS) $(INCLUDE_FLAGS) -c $< -o $(OBJECTS_DIRECTORY)$@

.PHONY: clean
clean:
	rm $(OBJECTS_DIRECTORY)*