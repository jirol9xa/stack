#include <iostream>
using namespace std;

int xuy(int god);
void printMonth(int ostatok, int mounth, int god);
void printMounth(int mounth);

int main(void)
{
    int mounth, god, year, sum = 0;
    cin >> mounth;
    cin >> god;

    year = god - 1;                          
    for (int end = 1919; year >= end; year--) {
            sum += 365 + xuy(year);
    }
    mounth = mounth - 1;
    switch (mounth)
    {
    case 1:
        sum += 31;
        break;
    case 2:
        sum += 59 + xuy(year);
        break;
    case 3:
        sum += 90 + xuy(year);
        break;
    case 4:
        sum += 120 + xuy(year);
        break;
    case 5:
        sum += 151 + xuy(year);
        break;
    case 6:
        sum += 181 + xuy(year);
        break;
    case 7:
        sum += 212 + xuy(year);
        break;
    case 8:
        sum += 243 + xuy(year);
        break;
    case 9:
        sum += 273 + xuy(year);
        break;
    case 10:
        sum += 304 + xuy(year); 
        break;
    case 11:
        sum += 334 + xuy(year); 
        break; 
    }
    cout << sum % 7 << "\n";
    printMounth (mounth);
       cout << god << endl;

    printMonth(sum % 7, mounth + 1, god);
 
    return 0;
}


int xuy(int year) 
{
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? 1 : 0;
}

void printMonth(int ostatok, int mounth, int god) 
{
    cout << "  ПН  ВТ  СР  ЧТ  ПТ  СБ  ВС\n";
    if (ostatok > 4) {
        for (int i = 0; i < ostatok - 5 ; i++) {
            cout << "    ";
        }
    }
    else {
        for (int i = 0; i < ostatok + 2; i++) {
            cout << "    ";
        }
    }
    if ( mounth == 1 || mounth == 3 || mounth == 5 || mounth == 7 || mounth == 8 || mounth == 10 || mounth == 12 ){
        for (int i = 1; i <= 31; i++){
        if (i < 10) {
            cout << "   ";
        }
        else{
            cout << "  ";
        }

        cout << i;
        ostatok ++;

        if (ostatok == 5) {
            cout << "\n";
        }
        if (ostatok == 7) {
            ostatok = 0;
        }
        }
    }
    else if ( mounth == 4 || mounth == 6 || mounth == 9 || mounth == 11 ) {
        for (int i = 1; i <= 30; i++){
        if (i < 10) {
            cout << "   ";
        }
        else{
            cout << "  ";
        }

        cout << i;
        ostatok ++;

        if (ostatok == 5) {
            cout << "\n";
        }
        if (ostatok == 7) {
            ostatok = 0;
        }
        }
    }
    else{
        for (int i = 1; i <= 28 + xuy(god); i++){
        if (i < 10) {
            cout << "   ";
        }
        else{
            cout << "  ";
        }

        cout << i;
        ostatok ++;

        if (ostatok == 5) {
            cout << "\n";
        }
        if (ostatok == 7) {
            ostatok = 0;
        }
        }
    }
  
    cout << " \n ";
}  
void printMounth (int mounth){
    switch (mounth)
    {
    case 1:
        cout << "ФЕВРАЛЬ ";
        break;
    case 2:
        cout << "МАРТ ";
        break;
    case 3:
        cout << "АПРЕЛЬ ";
        break;
    case 4:
        cout << "МАЙ ";
        break;
    case 5:
        cout << "ИЮНЬ ";
        break;
    case 6:
        cout << "ИЮЛЬ ";
        break;
    case 7:
        cout << "АВГУСТ ";
        break;
    case 8:
        cout << "СЕНТЯБРЬ ";
        break;
    case 9:
        cout << "ОКТЯБРЬ ";
        break;
    case 10:
        cout << "НОЯБРЬ "; 
        break;
    case 11:
        cout << "ДЕКАБРЬ "; 
        break; 
    case 0:
        cout << "ЯНВАРЬ ";
    }

}