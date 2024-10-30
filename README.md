# Task Description
## filestat
Напишите программу, выводящую в стандартный поток вывода информацию о количестве файлов каждого типа в текущей директории. Максимальный балл - 5.

# How to Use the Code
1. Склонируйте `filestat.cpp`.
2. Вставьте следующую команду в терминал для компиляции:
   ```bash
   g++ filestat.cpp -o filestat
   ```
3. Выполните следующую команду, чтобы переместить исполняемый файл в директорию `/usr/local/bin/`:
   ```bash
   sudo mv filestat /usr/local/bin/
   ```
4. Теперь вы можете запускать программу из любого места в терминале, введя:
   ```bash
   filestat
   ```

# Requirements
- Компилятор для C++17
- Linux-система

# Output
Программа выводит количество файлов каждого типа, найденных в текущей директории, в формате:
```
Regular file: X
Directory: Y
Symbolic link: Z
Block device: A
Character device: B
FIFO: C
Socket: D
Unknown: E
```
