// LR.9.2.A.cpp
// Татарський Василь Петрович
// Лабораторна робота №.9.2.A
// Впорядкування та бінарний пошук в масиві структур
// Варіант 26

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialty { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, LABOR_EDUCATION };
string specialtyStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка",
                          "Фізика та інформатика", "Трудове навчання" };

struct Student
{
    string    surname;
    int       course;
    Specialty specialty;
    int       physics;
    int       math;
    int       informatics;
};

void   Create(Student* p, const int N);
void   Print(Student* p, const int N);
void   Sort(Student* p, const int N);
int    BinSearch(Student* p, const int N, const string surname, const int course, const int math);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів N: "; cin >> N;

    Student* p = new Student[N];

    string surname;
    int    icourse, imath, found;
    int    menuItem;

    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << "  [1] - введення даних з клавіатури" << endl;
        cout << "  [2] - вивід даних на екран" << endl;
        cout << "  [3] - фізичне впорядкування даних" << endl;
        cout << "  [4] - бінарний пошук студента за прізвищем, курсом та оцінкою з математики" << endl;
        cout << "  [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "Масив впорядковано." << endl;
            Print(p, N);
            break;
        case 4:
            cout << "Введіть ключі пошуку:" << endl;
            cout << "  курс: "; cin >> icourse;
            cout << "  оцінка з математики: "; cin >> imath;
            cin.get();
            cin.sync();
            cout << "  прізвище: "; getline(cin, surname);
            cout << endl;
            if ((found = BinSearch(p, N, surname, icourse, imath)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Student* p, const int N)
{
    int ispec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.get();
        cin.sync();

        cout << "  прізвище: "; getline(cin, p[i].surname);
        cout << "  курс: ";     cin >> p[i].course;

        cout << "  спеціальність" << endl;
        cout << "    (0 - Комп'ютерні науки," << endl;
        cout << "     1 - Інформатика," << endl;
        cout << "     2 - Математика та економіка," << endl;
        cout << "     3 - Фізика та інформатика," << endl;
        cout << "     4 - Трудове навчання): ";
        cin >> ispec;
        p[i].specialty = (Specialty)ispec;

        cout << "  оцінка з фізики:      "; cin >> p[i].physics;
        cout << "  оцінка з математики:  "; cin >> p[i].math;
        cout << "  оцінка з інформатики: "; cin >> p[i].informatics;

        cout << endl;
    }
}

void Print(Student* p, const int N)
{
    cout << "=============================================================================" << endl;
    cout << "| №  |   Прізвище    | Курс |      Спеціальність       | Фіз. | Мат. | Інф.|" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[i].surname;
        cout << "| " << setw(4) << right << p[i].course << " ";
        cout << "| " << setw(24) << left << specialtyStr[p[i].specialty];
        cout << "| " << setw(4) << right << p[i].physics << " ";
        cout << "| " << setw(4) << right << p[i].math << " ";
        cout << "| " << setw(3) << right << p[i].informatics << " |" << endl;
    }
    cout << "=============================================================================" << endl;
    cout << endl;
}

void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].course > p[i1 + 1].course)
                || (p[i1].course == p[i1 + 1].course && p[i1].math > p[i1 + 1].math)
                || (p[i1].course == p[i1 + 1].course && p[i1].math == p[i1 + 1].math
                    && p[i1].surname < p[i1 + 1].surname))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int BinSearch(Student* p, const int N, const string surname, const int course, const int math)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].course == course && p[m].math == math && p[m].surname == surname)
            return m;
        if ((p[m].course < course)
            || (p[m].course == course && p[m].math < math)
            || (p[m].course == course && p[m].math == math && p[m].surname > surname))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}