#include <iostream> // Для виводу
#include <limits> // Для обробки очистки та даних вводу, якщо користувач вводить не число

#define m 11
using namespace std;

int mas[m][5], ms[m][8], n, Q_0, k;

void inputDataDeposits();
void calculateDepositProfits(int depositIndex);
void findMaxProfitsAndDeposits();
void updateDepositInBusiness(int step);

int main()
{
    cout << "Pavlo Valchevskyi, OI-11sp, LR # 7, variant 91, Doslidzhennya operatsiy" << endl;
    inputDataDeposits();
    printf("\n");
    for (int i = 0; i < n; i++) {
        calculateDepositProfits(i);
    }
    printf("\n");
    findMaxProfitsAndDeposits();
    printf("\n");
    system("pause");
}

/*
Функції:
    inputDataDeposits() - функція для введення вхідних даних, таких як кількість депозитів, початкова сума для депозиту та крок збільшення депозиту.
    updateDepositInBusiness(int step) - функція для оновлення інформації про депозити у бізнесі залежно від кроку.
    calculateDepositProfits(int depositIndex) - функція для розрахунку прибутку для кожного депозиту. Розрахунок виконується за допомогою деяких внутрішніх механізмів, і дані зберігаються у двовимірному масиві ms.
    findMaxProfitsAndDeposits() - функція для знаходження максимального прибутку та депозитів, що його забезпечують.
 Змінні, які використовуються:
    mas[m][5]: Це двовимірний масив розміром m на 5, де m визначається як 11 за допомогою макросу #define m 11. Цей масив використовується для зберігання даних про депозити. Кожен рядок у цьому масиві представляє один депозит, а кожний стовпець - певний параметр депозиту.
    ms[m][8]: Це ще один двовимірний масив, також розміром m на 8. Він використовується для зберігання додаткових даних, пов'язаних з розрахунками прибутку для кожного депозиту.
    n: Це змінна, яка визначає кількість депозитів, введених користувачем.
    Q_0: Це початкова сума для депозитів, яка введена користувачем.
    k: Це крок збільшення депозитів, також введений користувачем.
    i, j, p, dod, max, s: Змінні для ітерації та тимчасового зберігання значень (використовуються у функціях).
 */

void inputDataDeposits()
{
    int j = 0;
    cout << "Input number of deposits ( <10 )" << endl << "\tn - ";
    while (!(cin >> n) || (n <= 1 || n >= 10)) {
        cout << "\tInvalid input. Please enter number of deposits ( <10 )\tn - ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter start sum for deposit (default - 0)" << endl << "\tQ_0 - ";
    while (!(cin >> Q_0) || Q_0 < 0) {
        cout << "\tInvalid input. Please enter number start sum for deposit (default - 0)\tQ_0- ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    mas[0][0] = Q_0;

    cout << "Input step add to deposit" << endl << "\tk - ";
    while (!(cin >> k) || k <= 0) {
        cout << "\tInvalid input. Please enter number step add to deposit\tk- ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    updateDepositInBusiness(k);
    cout << "\nEnter business profits" << endl;
    cout << "f_0    f_1    f_2    f_3" << endl;
    for (int i = 0; i < n; i++) {
        cin >> mas[i][1] >> mas[i][2] >> mas[i][3] >> mas[i][4];
    }
}

void updateDepositInBusiness(int step)
{
    for (int i = 1; i < n; i++)
    {
        mas[i][0] = mas[i - 1][0] + k;
    }
}

void calculateDepositProfits(int depositIndex)
{
    int max, i, dod, j, p, s;
    max = -1;
    if (depositIndex == 0)
    {
        for (i = 0; i < n; i++)
        {
            ms[i][0] = mas[i][1];
            ms[i][1] = Q_0 + i * k;
        }
    }
    if (depositIndex == 1)
    {
        for (i = 0; i < n; i++)
            if (i == 0)
            {
                ms[i][2] = mas[0][1];
                ms[i][3] = mas[0][1];
            }
            else
            {
                p = i;
                for (j = 0; p >= 0; j++, p--)
                {
                    dod = mas[j][2] + ms[p][0];
                    if (dod > max)
                    {
                        max = dod;
                        s = j;
                    }
                }
                ms[i][2] = max;
                ms[i][3] = k * s;
                max = -1;
            }
    }
    max = -1;
    if (depositIndex == 2)
    {
        for (i = 0; i < n; i++)
            if (i == 0)
            {
                ms[i][4] = mas[0][2];
                ms[i][5] = mas[0][2];
            }
            else
            {
                p = i;
                for (j = 0; p >= 0; j++, p--)
                {
                    dod = mas[j][3] + ms[p][2];
                    if (dod > max)
                    {
                        max = dod;
                        s = j;
                    }
                }
                ms[i][4] = max;
                ms[i][5] = k * s;
                max = -1;
            }
    }
    max = -1;
    if (depositIndex == 3)
    {
        for (j = 0, p = n; j <= n; j++, p--)
        {
            dod = mas[j - 1][4] + ms[p][4];
            if (dod > max)
            {
                max = dod;
                s = j;
            }
        }
        ms[n - 1][6] = max;
        ms[n - 1][7] = k * (s - 1);
    }
    if (depositIndex == 4) {
        cout << "Final table:\n";
    }
    else cout << "Step " << depositIndex + 1 << ":\n";
    printf("L1\tx1\tL2\tx2\tL3\tx3\tL4\tx4\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 8; j++) {
            cout << ms[i][j] << "\t";
        }
        printf("\n");
    }
    cout << "\n";
}

void findMaxProfitsAndDeposits()
{
    int s, i, j, p, sum;
    sum = 0;
    s = ms[n - 1][7];
    p = mas[n - 1][0];
    if (s != 0)
    {
        sum += mas[n - 1][4];
        printf("In the fourth business, the enterprise deposits %d * 10 ^ 3 uah.\n", s);
    }
    p -= s;
    for (i = 0; i < 100; i++)

        if (i * k == p)
            break;
    s = ms[i][5];
    if (s != 0)
    {
        sum += mas[i][3];
        printf("In the third business, the enterprise deposits %d * 10 ^ 3 uah.\n", s);
    }
    p -= s;
    for (i = 0; i < 100; i++)
        if (i * k == p)
            break;
    s = ms[i][3];
    if (s != 0)
    {
        sum += mas[i][2];
        printf("In the second business, the enterprise deposits %d * 10 ^ 3 uah.\n", s);
    }
    p -= s;
    for (i = 0; i < 100; i++)
        if (i * k == p)
            break;
    s = ms[i][1];
    if (s != 0)
    {
        sum += mas[i][1];
        printf("In the first business, the enterprise deposits %d * 10 ^ 3 uah.\n", s);
    }
    printf("The maximum profit will be - %d * 10 ^ 3 uah.\n", ms[n - 1][6]);
}
