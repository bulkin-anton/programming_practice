-- This is Readme file for tests for task-1 --

-- Это файл Readme для тестирования задания-1 --

Перед выполнением выполнить следующие команды в терминале:

cd <путь к каталогу с программой и тестами>
fpc ./task

Для запуска тестов выполнить следующую команду:
./task<tests/имя_теста.txt ограничение_битности_ответа системы_счисления_для_вывода_через_пробел

В каждом файле для удобства в последнем комметарии(обозн. ';') будет написан ответ в 10-й системе счисления в формате 'ans = ' <правильный ответ>[(ограничение битности в параметрах программы)].
Если ограничение битности отсутствует - подразумевается 64 бита.

Далее будет приведен правильный вывод после выполнения программы для тестов(с ограничением битности в 64 бита и выводом ответа в 10-й системе счисления):

values_after_number.txt   Wrong value of a number 
                          10 0
probels.txt                          
                          10 95
impossible_operation.txt
                          impossible operation
                          10 -123
easy_check.txt
                          10 0
check_operacia.txt
                          Wrong input
                          10 25
check_number_basis.txt
                          Wrong value of a number
                          10 -2748
check_example.txt
                          10 -9394
check_bit_width.txt
                          The value is overflowing
                          10 -43695
check_number.txt
                          Wrong value of a number
                          10 -556765

Для следующих файлов будет приведен правильный вывод при задании ограничения в 16 бит:

perep_add.txt
                          The value is overflowing
                          10 10000
perep_otr.txt
                          The value is overflowing
                          10 1000
perep_mult.txt
                          The value is overflowing
                          10 256                   
