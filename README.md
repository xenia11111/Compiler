# Compiler
Условие:
Необходимо реализовать программу, которая принимает на вход:
1.	набор известных фактов
2.	набор правил по выведению новых фактов на основе входных известных фактов
3.	осуществляет интерпретацию правил [2] на наборе [1] и выдает в качестве результата набор новых фактов.
Входные факты и правила вывода считываются из файла. Первая строка в файле с данными содержит набор известных фактов, а вторая - набор правил.
Факты представлены в виде строк, заключенных в кавычки и разделенных запятой. Пример: "RAINY_DAY", "GOOD_WEATHER"
Правила представлены в виде строк "ФАКТ|..|ФАКТ, ....,ФАКТ|...|ФАКТ -> ФАКТ".
Каждое правило заключено в кавычки, правила отделены друг от друга запятой.
Символ "|" между фактами означает логическую операцию ИЛИ; символ "," между фактами означает логическую операцию И, символ "->" операцию выведения нового факта, который добавляется к уже известным фактам.
Результат операции ИЛИ является истинной если один из фактов является известным. Результат операции И является истинной только если все факты являются известными.
Пример: "RAINY_DAY|WINDY -> BAD_WEATHER", "BAD_WEATHER, BAD_MOD -> NEED_GROG"
Строки фактов могут содержать только символы [A-Z] и символ подчеркивания "_". Размер одной строки не превышает 64 символов. Количество входных фактов и правил не превышает 50.
Примеры:
1.	Могут существовать вырожденные правила:

"A", "B"
"C -> D"
Результат: пустой

2.	Новый факт можно получить при помощи нескольких правил (факт D):

"A", "B"
"A -> C", "B, C -> D"
Результат: C, D

Поставка решения:
Исходный код приложения и инструкции по сборке и запуску. Программа должна быть реализована в виде консольного приложения.
Результат в виде списка новых фактов, полученных в результате интерпретации правил выводится на стандартный вывод.