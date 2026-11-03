#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// 1. Формування динамічного масиву випадковими числами
void Create(double* a, const int size, const double Low, const double High)
{
    for (int i = 0; i < size; i++)
    {
        a[i] = Low + (double)rand() / RAND_MAX * (High - Low);
    }
}

// 2. Виведення динамічного масиву
void Print(const double* a, const int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << setw(8) << fixed << setprecision(2) << a[i];
    }
    cout << endl;
}

// 1.1. Кількість елементів масиву, більших за C
int CountGreaterThanC(const double* a, const int size, const double C)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] > C)
        {
            count++;
        }
    }
    return count;
}

// Допоміжна функція: індекс максимального за модулем елемента
int FindMaxAbsIndex(const double* a, const int size)
{
    if (size <= 0) return -1;
    int maxIndex = 0;
    double maxAbs = fabs(a[0]);
    for (int i = 1; i < size; i++)
    {
        if (fabs(a[i]) > maxAbs)
        {
            maxAbs = fabs(a[i]);
            maxIndex = i;
        }
    }
    return maxIndex;
}

// 1.2. Добуток елементів, розташованих після максимального за модулем елементу
double ProductAfterMaxAbs(const double* a, const int size)
{
    int maxIndex = FindMaxAbsIndex(a, size);
    // Якщо максимальний елемент останній або масив замалий
    if (maxIndex == -1 || maxIndex >= size - 1)
    {
        return 0; // Або можна повертати 1 / сигнальне значення, якщо таких елементів немає
    }

    double product = 1.0;
    bool found = false;
    for (int i = maxIndex + 1; i < size; i++)
    {
        product *= a[i];
        found = true;
    }

    return found ? product : 0;
}

// 2. Перетворення масиву: спочатку від'ємні, потім додатні/нулі (зі збереженням відносного порядку)
void TransformArray(double* a, const int size)
{
    double* temp = new double[size];
    int index = 0;

    // Спочатку копіюємо всі від'ємні елементи
    for (int i = 0; i < size; i++)
    {
        if (a[i] < 0)
        {
            temp[index++] = a[i];
        }
    }

    // Потім копіюємо всі невід'ємні (додатні та нулі)
    for (int i = 0; i < size; i++)
    {
        if (a[i] >= 0)
        {
            temp[index++] = a[i];
        }
    }

    // Переносимо назад у масив a
    for (int i = 0; i < size; i++)
    {
        a[i] = temp[i];
    }

    delete[] temp;
}

int main()
{
    srand((unsigned)time(NULL));

    int n;
    cout << "Enter n: ";
    cin >> n;

    double C;
    cout << "Enter C: ";
    cin >> C;

    // Виділення пам'яті під динамічний масив
    double* a = new double[n];

    double Low = -10.0;
    double High = 10.0;

    Create(a, n, Low, High);
    cout << "\nInitial array:" << endl;
    Print(a, n);

    int countC = CountGreaterThanC(a, n, C);
    cout << "1.1. Count of elements > " << C << " = " << countC << endl;

    int maxAbsIdx = FindMaxAbsIndex(a, n);
    cout << "Max absolute element = " << a[maxAbsIdx] << " at index " << maxAbsIdx << endl;

    double prod = ProductAfterMaxAbs(a, n);
    cout << "1.2. Product after max abs element = " << prod << endl;

    TransformArray(a, n);
    cout << "\nModified array (negative first, then positive/zero):" << endl;
    Print(a, n);

    // Звільнення пам'яті динамічного масиву
    delete[] a;

    return 0;
}
