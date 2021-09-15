#include <iostream>
#include <fstream>
#include <string>
#include <cctype>   // для функции isdigit
#include <math.h> //для функции pow
#include <algorithm> //для перевода строки в нижний регистр
#include <filesystem>

#define SIZEOFPASS 5 //длина пароля
using namespace std;

fstream database("database.txt", ios::in | ios::out | ios::app); //хранится название файла, индексы замены букв, рандомное число и зашифрованный пароль


int checkKey(int key) {
    if (key == 0 || key == 1)
    {
        return 0;
    }
    else
    {
        cout << "Incorrect key. Bye" << endl;
        return 1;
    }
        
}

int checkPass(string pass, int key) {
    if (pass.size() != SIZEOFPASS)
    {
        if (key == 0)
            cout << "Wrong lenght of password. Bye" << endl;
        else
            cout << "Wrong password!" << endl;
        return 1;
    }
    
    bool flag;

    for (int i = 0; i < SIZEOFPASS; i++)
    {
        if (!isdigit(pass[i]))
        {

            if (i == 0 && (pass[i] == 65 || pass[i] == 65 + 32))
            {
                cout << "password shouldn't start with symbol A,a,0" << endl;
                return 1;
            }

            flag = 0;
            for (int j = 65; j < 75; j++) 
            {
                if (pass[i] == j || pass[i] == j + 32) //ascii код заглавных и строчных букв a - g
                {
                    flag = 1;
                    continue;
                }
            }

            if (flag == 0)
            {
                if (key == 0)
                    cout << "password contains wrong symbols" << endl;
                else 
                    cout << "Wrong password!" << endl;
                return 1;
            }
        }
        else
        {
            if (i == 0 && pass[i] == '0')
            {
                cout << "password shouldn't start with symbol A,a,0" << endl;
                return 1;
            }
            continue;
        }
    }

    return 0;
}

//заменяет буквы на цифры, a-0 , b-1, ... g-9
int* changeLetter(string pass) {
    static int newPass[SIZEOFPASS];
    char temp;
    int* ptr;

    int count;
    char index_db;

    for (int i = 0; i < SIZEOFPASS; i++)
    {
        index_db = '0';
        if (isdigit(pass[i]))
        {
            temp = pass[i];
            newPass[i] = atoi(&temp);
        }
        else
        {
            count = 0;
            for (int j = 65; j < 75; j++)
            {              
                if (pass[i] == j || pass[i] == j + 32) //ascii код заглавных и строчных букв a - g
                {
                    newPass[i] = count;
                    index_db = '1';
                }
                count++;
            }
        }

        database << index_db << " ";
    }

    ptr = newPass;
    return ptr;
}




//перестановка
int* transPosition(int* pass)
{
    int changePos[5] = { 2, 0, 3, 4, 1 }; //меняем положение символов в пароле
    static int tempPass[SIZEOFPASS];
    int j;
    for (int i = 0; i < 5; i++)
    {
        j = changePos[i];
        tempPass[i] = pass[j];
    }

    return tempPass;
}

//обратная перестановка
int* transPositionDecode(int* pass)
{
    int changePos[5] = { 1, 4, 0, 2, 3 }; //меняем положение символов в пароле
    static int tempPass[SIZEOFPASS];
    int j;
    for (int i = 0; i < 5; i++)
    {
        j = changePos[i];
        tempPass[i] = pass[j];
    }

    return tempPass;
}

//из массива получаем одно число
int charToNumber(int* pass)
{
    int number = 0;
    int j = 0;

    for (int i = SIZEOFPASS - 1; i >= 0; i--)
    {
        number += pass[j] * pow(10, i);
        j++;
    }
    return number;
}

//из числа получаем массив цифр
int* numberToArray(int number)
{
    static int pass[SIZEOFPASS];
    int* ptr;
    int j = 0;
    int temp;
    string tempString;
    char tempChar;
    tempString = to_string(number);

    for (int i = 0; i < SIZEOFPASS; i++)
    {
        tempChar = tempString[i];
        pass[i] = (int)tempChar - '0';
    }
    ptr = pass;
    return ptr;
}

//замена с помощью XOR
int replacePass(int* pass)
{
    int randPass[SIZEOFPASS];
    
    int passNumber;
    int randNumber; //рандомное пятизначное число

    int result;

    passNumber = charToNumber(pass);
   
    srand(time(NULL));

    for (int i = 0; i < SIZEOFPASS; i++)
        {
            randPass[i] = rand() % 10;
        }

        randNumber = charToNumber(randPass);
        result = passNumber ^ randNumber;
        database << to_string(randNumber) << " ";

    return result;
}

//обратная замена цифр на буквы
string changeLetterDecode(int* pass, char* cinPtrArray) {
    int tempInt = charToNumber(pass);
    string result = to_string(tempInt);
    char tempChar;

        for (int i = 0; i < SIZEOFPASS; i++)
        {
            if (cinPtrArray[i] == '1')
            {
                tempChar = (char)result[i];
                tempInt = (int)tempChar - '0';;
                tempChar = 97 + tempInt; //меняем на маленькие буквы
                result[i] = tempChar;
            }
        }

        return result;
}



int main()
{
    char keychar;
    int key;
    string fileName;
    string pass;
    
    int* digitPass;
    int result;
    int cinResult = 0;

    cout << "0 - Encode file, 1 - Decode file: " << endl;
    cin >> keychar;
    key = keychar - '0';

    if (!checkKey(key))
    {
        cout << "txt file name: " << endl;
        cin >> fileName;

       
    }
    else
        return 1;


    if (key == 0)
    {            
        cout << "password (" << SIZEOFPASS << " symbols including any digits and/or letters a, b, c, d, e, f, g, h, i, j): " << endl;
    }
    else
    {
        cout << "password: " << endl;

    }

    cin >> pass;

    if (!checkPass(pass, key))
    {

        if (key == 0)
        {
            database << fileName << " ";
            digitPass = changeLetter(pass);
            digitPass = transPosition(digitPass);
            result = replacePass(digitPass);
            database << result << endl;
            cout << "File is encoded!" << endl;;
        }
        else
        {
            int fileFound = 0;
            string cinFileName;
            static char cinArray[SIZEOFPASS];
            char* cinPtrArray = cinArray;
            int cinRandNumber;
            int cinResult;
            int result;
            int* numberArray;

            while (!database.eof())
            {
                database >> cinFileName;
                if (cinFileName == fileName)
                {
                    fileFound = 1;
                    
                    for (int i = 0; i < SIZEOFPASS; i++)
                    {
                        database >> cinArray[i];
                    }

                    cinPtrArray = cinArray;
                    database >> cinRandNumber;
                    database >> cinResult;
                }

                if (fileFound == 1)
                    break;
            }

            if (fileFound == 1)
            {
                string countedResult;
                result = cinResult ^ cinRandNumber;
                numberArray = numberToArray(result);
                numberArray = transPositionDecode(numberArray);
                countedResult = changeLetterDecode(numberArray, cinPtrArray);

                transform(pass.begin(), pass.end(), pass.begin(), ::tolower);

                if (pass == countedResult)
                    cout << "File is decoded! Password is true" << endl;
            }
            else
            {
                cout << "File is not found" << endl;
            }

        }
    }
    else
        return 1;

   

    return 0;
}
