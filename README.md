Пароль привязывается к названию файла, при этом необязательно существование этого файла.
Алгоритм шифрования: 
1. Если в пароле присутствует буква, все буквы заменяются на цифры
2. Перестановка цифр в случайном порядке: сначала через xor суммируются все цифры пароля (seed = seed + (seed ^ pass[i]))
и полученное значение используется для seed рандома. Полученный порядок записывается в database. 
рандома цифр от 0 до 4. 
3. (Полученное число в пункте 2) XOR (случайное число)
4. Полученное число в пункте 3 и есть зашифрованный пароль

В database хранится название файла, индексы замены букв, рандомное число и зашифрованный пароль

Алгоритм расшифровки: 
1. (Зашифрованный пароль) XOR (случайное число)
2. Обратная перестановка цифр
3. Используя массив индексов замены букв восстанавливаем буквы
4. Полученное число сравниваем с введенным значением пользователя

Пароль не должен начинаться с символов A,a,0. Длина пароля 5 символов. Пароль состоит из цифр и букв a, b, c, d, e, f, g, h, i, j.
Утилита игнорирует нижний и верхний регистры.