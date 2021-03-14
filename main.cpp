#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <math.h>

using namespace std;

ifstream in("date");

void Generator(vector<int> &v, size_t interval, size_t range)
{
    srand((unsigned)time(NULL));
    for(size_t i=0; i<interval; i++)
        v.push_back(rand() % range);
}

bool Verificare(vector<int> v)
{
    for(size_t i=1; i < v.size(); i++)
        if(v[i] < v[i-1])
            return false;
    return true;
}

void Count_Sort(vector<int> &v)
{
    int maxim = *max_element(v.begin(), v.end())+1, aparitii[maxim], j = 0;

    for(int i = 0; i < maxim + 1; i++)
        aparitii[i] = 0;

    for(size_t i = 0; i < v.size(); i++)
        aparitii[v[i]]++;

    for(int i = 0; i < maxim + 1; i++)
        while(aparitii[i]--)
            v[j++] = i;
}

void Bubble_Sort(vector<int> &v)
{
    size_t i,j;
    for(i=0; i < v.size(); i++)
        for(j=0; j < v.size()-i; j++)
            if(v[j] > v[j+1])
            {
                int aux = v[j+1];
                v[j+1] = v[j];
                v[j] = aux;
            }
}

void Quick_Sort(vector<int> &v, int st, int dr)
{
    if(st < dr)
    {
        int pivot = v[dr], i = st-1, aux, m;
        for(int j = st; j < dr; j++)
            if(v[j] < pivot)
            {
                i++;
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        aux = v[i+1];
        v[i+1] = v[dr];
        v[dr] = aux;

        m = i + 1;
        Quick_Sort(v, st, m - 1);
        Quick_Sort(v, m + 1, dr);
    }
}

void Merge_Sort(vector<int> &v, int st = 0, int dr = -1)
{
    if(dr == -1)
        dr = v.size() - 1;
    if(st < dr)
    {
        int m = (st + dr)/2;
        Merge_Sort(v, st, m);
        Merge_Sort(v, m+1, dr);
        int poz=st, poz1=0, poz2=0, v1[m-st+1], v2[dr-m];

        for(int i = st; i <= m; i++)
            v1[i-st] = v[i];

        for(int i = m+1; i <= dr; i++)
            v2[i-m-1] = v[i];

        while(poz1 < m-st+1 && poz2 < dr-m)
        {
            if(v1[poz1] <= v2[poz2])
                v[poz++] = v1[poz1++];
            else
                v[poz++] = v2[poz2++];
        }

        while(poz1 < m-st+1)
            v[poz++] = v1[poz1++];

        while(poz2 < dr-m)
            v[poz++] = v2[poz2++];
    }
}

vector<int> R(vector<int> v, int nr_cifre_ramase, size_t baza)
{
    size_t i;
    if(nr_cifre_ramase == -1)
        return v;

    vector<int> v1[baza], rezultat;
    for(i=0; i<v.size(); i++)
    {
        int z = int(v[i]/ceil(pow(baza, nr_cifre_ramase)));
        v1[z % baza].push_back(v[i]);
    }

    for(i=0; i < baza; i++)
        if(v1[i].size() != 0)
        {
            vector<int> v3 = R(v1[i], nr_cifre_ramase - 1, baza);
            rezultat.insert(rezultat.end(), v3.begin(), v3.end());
            v3.clear();
        }
    return rezultat;
}

void Radix_Sort(vector<int> &v, size_t baza=10)
{
    if(v.size() == 0)
        return;
    int nr_cifre = -1, maxim = *max_element(v.begin(), v.end());
    while(maxim)
    {
        maxim /= baza;
        nr_cifre++;
    }
    v = R(v, nr_cifre, baza);
    return;
}


int main()
{
    vector<int> v, copie;
    size_t timp_initial, timp_final, nr_elem, maxim, i=1;
    while(in >> nr_elem >> maxim)
    {
        cout<<"Testul "<< i++ <<" cu nr de elemente "<<nr_elem<<" si maximul posibil " << maxim << ":\n";
        Generator(v, nr_elem, maxim);

        copie = v;
        timp_initial = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout<<"STD sort: ";
        sort(copie.begin(), copie.end());
        timp_final = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << timp_final - timp_initial <<" milisecunde\n";

        copie = v;
        timp_initial = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << "Count sort: ";
        Count_Sort(copie);
        timp_final = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << timp_final - timp_initial << " milisecunde\n";

        copie = v;
        timp_initial = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout<<"Quick sort: ";
        Quick_Sort(copie, 0, copie.size());
        timp_final = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << timp_final - timp_initial << " milisecunde\n";

        copie = v;
        timp_initial = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << "Merge sort: ";
        Merge_Sort(copie);
        timp_final = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << timp_final - timp_initial<<" milisecunde\n";


        copie = v;
        timp_initial = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout<<"Radix sort: ";
        Radix_Sort(copie);
        timp_final = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << timp_final- timp_initial <<" milisecunde\n";

        copie = v;
        timp_initial = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << "Bubble sort: ";
        Bubble_Sort(copie);
        timp_final = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        cout << timp_final - timp_initial << " milisecunde\n";

        cout << "\n";
    }
    return 0;
}
