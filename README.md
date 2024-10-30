# Task Description
## asnohup
Напишите программу, запускающую другую программу и отвязывающую ее от управляющего терминала (аналог nohup). Ввод-вывод запускаемой программы должен быть перенаправлен в /dev/null. Максимальный балл - 5.

# How to Use the Code
1. Склонируйте asnohup.cpp.
2. Вставьте следующую команду в терминал для компиляции:
```bash
g++ asnohup.cpp -o asnohup
```
3. Выполните следующую команду, чтобы переместить исполняемый файл в директорию /usr/local/bin/:
```bash
sudo mv asnohup /usr/local/bin/
```
4. Теперь вы можете запускать программу из любого места в терминале, введя:
```bash
asnohup <command> [args...]
```
Например, чтобы запустить программу example, выполните:
```bash
asnohup example
```

# Requirements
- Компилятор для C++17
- Linux-система
  
# Output
Программа запускает указанную команду в фоновом режиме и отвязывает её от управляющего терминала. Если команда успешно запущена, вы увидите сообщение о PID запущенного процесса:
```Started process <pid> in the background.```
Если возникла ошибка при запуске команды, программа выведет сообщение об ошибке, например:
```Failed to start <command>: <error message>```

# Note
- Убедитесь, что у вас есть права на запуск указанной команды и что она доступна в PATH.
- Вывод и ошибки выполняемой программы не будут отображаться в терминале, так как они перенаправляются в `/dev/null`.

# Example
1. Запуск фоновой программы `sleep` на 60 секунд:
```bash
asnohup sleep 60
```
3. Вывод будет:
```bash
Started process <pid> in the background.
```
5. Проверка процесса в фоновом режиме:
```bash
ps aux | grep sleep
```
