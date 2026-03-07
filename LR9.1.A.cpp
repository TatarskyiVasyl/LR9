#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialty { COMP_SCIENCE, INFORMATICS, MATH_ECON, PHYS_INFO, LABOR_EDU };

string specialtyStr[] = {
    "Комп'ютерні науки",
    "Інформатика",
    "Математика та економіка",
    "Фізика та інформатика",
    "Трудове навчання"
};

struct Student
{
    string  prizv;
    int     kurs;
    Specialty specialty;
    int     phys;
    int     math;
    int     info;
};

void   Create(Student* s, const int N);
void   Print(Student* s, const int N);
double Task1(Student* s, const int N);
void   Task2(Student* s, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    double proc = Task1(s, N);
    cout << "Процент студентів, які вчаться без трійок: "
        << fixed << setprecision(2) << proc << "%" << endl;

    cout << "\nПрізвища студентів, які отримали з фізики оцінку 5 або 4:" << endl;
    Task2(s, N);

    delete[] s;
    return 0;
}

void Create(Student* s, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "\nСтудент № " << i + 1 << ":" << endl;

        cin.get();
        cin.sync();

        cout << "   прізвище    : "; getline(cin, s[i].prizv);
        cout << "   курс        : "; cin >> s[i].kurs;

        cout << "   спеціальність (0 - Комп'ютерні науки, 1 - Інформатика,\n"
            "                   2 - Математика та економіка, 3 - Фізика та інформатика,\n"
            "                   4 - Трудове навчання): ";
        int sp; cin >> sp;
        s[i].specialty = (Specialty)sp;

        cout << "   оцінка з фізики      : "; cin >> s[i].phys;
        cout << "   оцінка з математики  : "; cin >> s[i].math;
        cout << "   оцінка з інформатики : "; cin >> s[i].info;

        cout << endl;
    }
}

void Print(Student* s, const int N)
{
    cout << "\n=================================================================="
        "====================" << endl;
    cout << "| №  | Прізвище             | Курс | Спеціальність              "
        "| Фіз | Мат | Інф |" << endl;
    cout << "------------------------------------------------------------------"
        "--------------------" << endl;

    for (int i = 0; i < N; i++)
    {

        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(20) << left << s[i].prizv << " ";
        cout << "| " << setw(4) << right << s[i].kurs << " ";
        cout << "| " << setw(26) << left << specialtyStr[s[i].specialty] << " ";
        cout << "| " << setw(3) << right << s[i].phys << " ";
        cout << "| " << setw(3) << right << s[i].math << " ";
        cout << "| " << setw(3) << right << s[i].info << " |" << endl;
    }

    cout << "=================================================================="
        "====================" << endl;
}

double Task1(Student* s, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        if (s[i].phys >= 4 && s[i].math >= 4 && s[i].info >= 4)
            k++;
    }
    return 100.0 * k / N;
}

void Task2(Student* s, const int N)
{
    for (int i = 0; i < N; i++)
    {
        if (s[i].phys == 5 || s[i].phys == 4)
        {
            cout << setw(3) << right << i + 1
                << " " << s[i].prizv << endl;
        }
    }
}