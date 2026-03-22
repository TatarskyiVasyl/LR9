// LR.9.3.cpp
// Татарський Василь Петрович
// Лабораторна робота №.9.3
// Опрацювання масивів структур
// Варіант 26

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct Tovar {
    string nazva;
    double vartist;
    int    kilkist;
    string odyn_vym;
};

Tovar* Create(int& N);
void   Print(Tovar* arr, const int N);
void   AddTovar(Tovar*& arr, int& N);
void   DeleteTovar(Tovar*& arr, int& N);
void   EditTovar(Tovar* arr, const int N);
void   SortByNazva(Tovar* arr, const int N);
void   SortByVartist(Tovar* arr, const int N);
int    FindByNazva(Tovar* arr, const int N, const string& nazva);
int    CountInRange(Tovar* arr, const int N, double vMin, double vMax);
void   SearchByNazva(Tovar* arr, const int N);
void   SearchByRange(Tovar* arr, const int N);
bool   SaveToFile(Tovar* arr, const int N, const string& fname);
bool   LoadFromFile(Tovar*& arr, int& N, const string& fname);
double GetTotalCost(const Tovar& t);

double GetTotalCost(const Tovar& t) {
    return t.vartist * t.kilkist;
}

int FindByNazva(Tovar* arr, const int N, const string& nazva) {
    for (int i = 0; i < N; i++)
        if (arr[i].nazva == nazva)
            return i;
    return -1;
}

int CountInRange(Tovar* arr, const int N, double vMin, double vMax) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        double z = GetTotalCost(arr[i]);
        if (z >= vMin && z <= vMax) count++;
    }
    return count;
}

void InputTovar(Tovar& t) {
    cin.get();
    cin.sync();
    cout << "   Назва: ";         getline(cin, t.nazva);
    cout << "   Вартість (грн): "; cin >> t.vartist;
    cout << "   Кількість: ";     cin >> t.kilkist;
    cin.get(); cin.sync();
    cout << "   Одиниця вим.: ";  getline(cin, t.odyn_vym);
}

Tovar* Create(int& N) {
    cout << "Введіть кількість товарів: "; cin >> N;
    Tovar* arr = new Tovar[N];
    for (int i = 0; i < N; i++) {
        cout << "Товар №" << i + 1 << ":\n";
        InputTovar(arr[i]);
    }
    return arr;
}

void Print(Tovar* arr, const int N) {
    if (N == 0) { cout << "Список порожній.\n"; return; }
    cout << "\n" << string(78, '=') << "\n";
    cout << "| " << setw(3) << right << "№"
        << " | " << setw(20) << left << "Назва"
        << " | " << setw(10) << right << "Вартість"
        << " | " << setw(9) << right << "Кількість"
        << " | " << setw(12) << left << "Од.вим."
        << " | " << setw(12) << right << "Заг.варт." << " |\n";
    cout << string(78, '-') << "\n";
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1
            << " | " << setw(20) << left << arr[i].nazva
            << " | " << setw(10) << right << fixed << setprecision(2) << arr[i].vartist
            << " | " << setw(9) << right << arr[i].kilkist
            << " | " << setw(12) << left << arr[i].odyn_vym
            << " | " << setw(12) << right << GetTotalCost(arr[i]) << " |\n";
    }
    cout << string(78, '=') << "\n\n";
}

void AddTovar(Tovar*& arr, int& N) {
    Tovar* newArr = new Tovar[N + 1];
    for (int i = 0; i < N; i++) newArr[i] = arr[i];
    delete[] arr;
    arr = newArr;
    cout << "Новий товар №" << N + 1 << ":\n";
    InputTovar(arr[N]);
    N++;
    cout << "Товар додано.\n";
}

void DeleteTovar(Tovar*& arr, int& N) {
    if (N == 0) { cout << "Список порожній.\n"; return; }
    Print(arr, N);
    int idx;
    cout << "Введіть номер товару для вилучення: "; cin >> idx;
    if (idx < 1 || idx > N) { cout << "Невірний номер!\n"; return; }
    Tovar* newArr = new Tovar[N - 1];
    for (int i = 0, j = 0; i < N; i++)
        if (i != idx - 1) newArr[j++] = arr[i];
    delete[] arr;
    arr = newArr;
    N--;
    cout << "Товар вилучено.\n";
}

void EditTovar(Tovar* arr, const int N) {
    if (N == 0) { cout << "Список порожній.\n"; return; }
    Print(arr, N);
    int idx;
    cout << "Введіть номер товару для редагування: "; cin >> idx;
    if (idx < 1 || idx > N) { cout << "Невірний номер!\n"; return; }
    cout << "Нові дані для товару №" << idx << ":\n";
    InputTovar(arr[idx - 1]);
    cout << "Товар відредаговано.\n";
}

void SortByNazva(Tovar* arr, const int N) {
    Tovar tmp;
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - i - 1; j++)
            if (arr[j].nazva > arr[j + 1].nazva) {
                tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
            }
}

void SortByVartist(Tovar* arr, const int N) {
    Tovar tmp;
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - i - 1; j++)
            if (GetTotalCost(arr[j]) > GetTotalCost(arr[j + 1])) {
                tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
            }
}

void SearchByNazva(Tovar* arr, const int N) {
    cin.get(); cin.sync();
    string nazva;
    cout << "Введіть назву товару: "; getline(cin, nazva);
    int idx = FindByNazva(arr, N, nazva);
    if (idx == -1) {
        cout << "Товар \"" << nazva << "\" не знайдено.\n";
        return;
    }
    cout << "\nЗнайдено:\n";
    cout << "  Назва:        " << arr[idx].nazva << "\n";
    cout << "  Вартість:     " << fixed << setprecision(2) << arr[idx].vartist << " грн\n";
    cout << "  Кількість:    " << arr[idx].kilkist << " " << arr[idx].odyn_vym << "\n";
    cout << "  Заг.вартість: " << GetTotalCost(arr[idx]) << " грн\n";
}

void SearchByRange(Tovar* arr, const int N) {
    double vMin, vMax;
    cout << "Мінімальна загальна вартість: "; cin >> vMin;
    cout << "Максимальна загальна вартість: "; cin >> vMax;
    int count = CountInRange(arr, N, vMin, vMax);
    if (count == 0) { cout << "Товарів у діапазоні не знайдено.\n"; return; }
    cout << "\nТовари від " << vMin << " до " << vMax << " грн:\n";
    for (int i = 0; i < N; i++) {
        double z = GetTotalCost(arr[i]);
        if (z >= vMin && z <= vMax)
            cout << "  " << arr[i].nazva << " — " << fixed << setprecision(2)
            << z << " грн (" << arr[i].kilkist << " " << arr[i].odyn_vym << ")\n";
    }
}

bool SaveToFile(Tovar* arr, const int N, const string& fname) {
    ofstream f(fname);
    if (!f.is_open()) return false;
    f << N << "\n";
    for (int i = 0; i < N; i++)
        f << arr[i].nazva << "\n"
        << arr[i].vartist << "\n"
        << arr[i].kilkist << "\n"
        << arr[i].odyn_vym << "\n";
    f.close();
    return true;
}

bool LoadFromFile(Tovar*& arr, int& N, const string& fname) {
    ifstream f(fname);
    if (!f.is_open()) return false;
    f >> N;
    f.ignore();
    delete[] arr;
    arr = new Tovar[N];
    for (int i = 0; i < N; i++) {
        getline(f, arr[i].nazva);
        f >> arr[i].vartist >> arr[i].kilkist;
        f.ignore();
        getline(f, arr[i].odyn_vym);
    }
    f.close();
    return true;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N = 0;
    Tovar* arr = nullptr;
    int menuItem;

    do {
        cout << "\n========== МЕНЮ ==========\n";
        cout << " [1]  - Введення даних з клавіатури\n";
        cout << " [2]  - Вивід даних на екран\n";
        cout << " [3]  - Додати товар\n";
        cout << " [4]  - Вилучити товар\n";
        cout << " [5]  - Редагувати товар\n";
        cout << " [6]  - Сортування за назвою\n";
        cout << " [7]  - Сортування за загальною вартістю\n";
        cout << " [8]  - Пошук за назвою\n";
        cout << " [9]  - Пошук за діапазоном вартості\n";
        cout << " [10] - Зберегти у файл\n";
        cout << " [11] - Завантажити з файлу\n";
        cout << " [0]  - Вихід\n";
        cout << "Введіть значення: "; cin >> menuItem;
        cout << "\n";

        string fname;
        switch (menuItem) {
        case 1:
            delete[] arr;
            arr = Create(N);
            break;
        case 2:  Print(arr, N);         break;
        case 3:  AddTovar(arr, N);      break;
        case 4:  DeleteTovar(arr, N);   break;
        case 5:  EditTovar(arr, N);     break;
        case 6:
            SortByNazva(arr, N);
            cout << "Відсортовано за назвою.\n";
            break;
        case 7:
            SortByVartist(arr, N);
            cout << "Відсортовано за загальною вартістю.\n";
            break;
        case 8:  SearchByNazva(arr, N); break;
        case 9:  SearchByRange(arr, N); break;
        case 10:
            cin.get(); cin.sync();
            cout << "Ім'я файлу: "; getline(cin, fname);
            if (!SaveToFile(arr, N, fname))
                cout << "Помилка збереження!\n";
            else
                cout << "Збережено у \"" << fname << "\".\n";
            break;
        case 11:
            cin.get(); cin.sync();
            cout << "Ім'я файлу: "; getline(cin, fname);
            if (!LoadFromFile(arr, N, fname))
                cout << "Помилка завантаження!\n";
            else
                cout << "Завантажено з \"" << fname << "\".\n";
            break;
        case 0: break;
        default: cout << "Помилкове значення!\n";
        }
    } while (menuItem != 0);

    delete[] arr;
    return 0;
}