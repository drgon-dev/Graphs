#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int matrixSize = 10;
const string letters = "ABCDEFGHIJKL";

inline string DeleteChar(string input, char avoid) {
    string result;
    for (char item : input) {
        if (!item == avoid)
            result += item;
    }
}

inline void ShowMatrix(bool** array) {
    cout << "  A B C D E F G H I J\n";
    for (int i = 0; i < matrixSize; i++) {
        cout << letters[i] << " ";
        for (int j = 0; j < matrixSize; j++)
            cout << array[i][j] << " ";
        cout << "\n";
    }
}

int StringConv(string input) {
    if (input == "help") {
        return 0;
    }
    if (input == "read") {
        return 1;
    }
    if (input == "byhand") {
        return 2;
    }
    if (input == "components") {
        return 3;
    }
    if (input == "show") {
        return 4;
    }
    return -1;
}

bool ReadFile(bool** result, string input) {
    string fileName = input.substr(input.find(" ") + 1);
    if (fileName == "") {
        cout << "Укажите название файла!";
        return false;
    }
    string temp;
    fstream file;
    file.open(fileName);
    if (!file.is_open()){
        cout << "Файл " << fileName << " не доступен!\n";
        return false;
    }
    else {
        for (int i = 0; i < matrixSize; i++) {
            getline(file, temp);
            for (int j = 0; j < matrixSize; j++) {
                if (temp[j] == '1')
                    result[i][j] = true;
                else
                    result[i][j] = false;
            }
        }
        file.close();
    }
    return true;
}

void InputByHand(bool** origin) {
    string temp;
    cout << "#ABCDEFGHIJ\n";
    for (int i = 0; i < matrixSize; i++) {
        cout << letters[i];
        getline(cin, temp);
        for (int j = 0; j < temp.size(); j++) {
            if (temp[j] == '1')
                origin[i][j] = true;
            else
                origin[i][j] = false;
        }
    }
}

inline void ShowHelp() {
    cout << "help - вывести меню помощи\n";
    cout << "show - показать матрицу\n";
    cout << "byhand - заполнить матрицу вручную\n";
    cout << "read <имя файла.txt> - прочитать матрицу из файла\n";
    cout << "component - найти компоненты связности\n";
}

void SearchConnections(bool** array, string& nodes, int row) {
    for (int i = 0; i < matrixSize; i++) {
        if (array[row][i] && nodes.find(letters[i]) == -1)
        {
            nodes += letters[i];
            SearchConnections(array, nodes, i);
        }
    }
}

bool CheckClones(vector<string> nodes, char key) {
    for (string item : nodes) {
        if (item.find(key) != -1)
            return true;
    }
    return false;
}

bool FindComponents(bool** origin) {
    vector<string> vec;
    for (int i = 0; i < matrixSize; i++) {
        if (!CheckClones(vec, letters[i])) {
            vec.push_back("");
            SearchConnections(origin, vec.back(), i);
        }
    }
    cout << "\n" << "Компоненты связности" << "\n";
    for (int j = 0; j < vec.size(); j++) {
        cout << j + 1 << ": " << vec[j];
        cout << "\n";
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string input;
    bool** origin = new bool*[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        origin[i] = new bool[matrixSize];
        for (int j = 0; j < matrixSize; j++)
            origin[i][j] = 0;
    }
        
    do{
        cout << ">";
        getline(cin, input);
        switch (StringConv(input.substr(0, input.find(" ")))) {
        case 0:
            ShowHelp();
            break;
        case 1:
            ReadFile(origin, input);
            break;
        case 2:
            InputByHand(origin);
            break;
        case 3:
            FindComponents(origin);
            break;
        case 4:
            ShowMatrix(origin);
            break;
        default:
            break;
        }
    } while (input != "exit");
    delete[] origin;
    return 0;
}