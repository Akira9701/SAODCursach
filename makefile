# Компилятор
CC = g++

# Опции компиляции
CFLAGS = -Wall -Wextra

# Имя исполняемого файла
TARGET = app

# Список исходных файлов
SOURCES = main.cpp

# Список объектных файлов
OBJECTS = $(SOURCES:.c=.o)

# Правило по умолчанию
all: $(TARGET)

# Правило для компиляции исполняемого файла
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)
	clear
	./app

# Правило для компиляции объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка сгенерированных файлов
clean:
	rm -f $(OBJECTS) $(TARGET)