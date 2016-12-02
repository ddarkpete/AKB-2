#include <iostream>
#include <fstream>
#include <cstdlib>


using namespace std;

int V = 1,E = 1;//liczba krawêdzi
int x=0;
int tab[100];





int main()
{
    bool pentelka=true;
    bool liniowy=true;

    string nazwa;

    fstream plik;
    cout<<"Podaj nazwe pliku zrodlowego:";
    cin>>nazwa;
    string nazwa2= nazwa + ".txt";

    plik.open(nazwa2.c_str(), ios::in);
    while( !plik.eof() )
    {
        plik >> tab[ x ];
        x++;
    }
    plik.close();



    V=tab[0];//dwa pierwsze elementy wczytanej tablicy to liczba krawedzi i wierzcholkow
    E=tab[1];
    int l_izolowanych = tab[2];
    int izolowane[l_izolowanych];



    cout<<"********************"<<endl;
    cout<<"Liczba wierzcholkow:"<<V<<endl;
    cout<<"Liczba krawedzi:"<<E<<endl;
    cout<<"********************"<<endl;


    int kraw[2][E];

    int c=0;
    int d=0;
    int e=0;
    for(int j=3; j<E*2+3; j++)
    {
        if(j%2==0)
        {
            kraw[1][c]=tab[j];
            c++;
        }
        else
        {
            kraw[0][d]=tab[j];
            d++;
        }

    }
    if(l_izolowanych > 0 )
    {
        cout<<"Wierzcholki izolowane bez krawedzi :"<<endl;
        for(int w = E*2+3; w < x   ; w++)
        {
            izolowane[e] = tab[w];
            cout<<tab[w]<< " ";
            e++;
        }
        cout<<endl;
    }

    int pom,pom1;

   /* for(int i=0; i<E; i++)
        for(int j=0; j<E-i-1; j++) //pętla wewnętrzna
            if(kraw[0][j]>kraw[0][j+1])
            {
                //zamiana miejscami
                pom = kraw[0][j];
                pom1 = kraw[1][j];
                kraw[0][j] = kraw[0][j+1];
                kraw[1][j] = kraw[1][j+1];
                kraw[0][j+1] = pom;
                kraw[1][j+1] = pom1;
            }
*/





    cout<<endl<<"Luki: "<<endl;
    for(int l=0; l<E; l++)
    {
        cout<<kraw[0][l]<<" -> "<<kraw[1][l]<<endl;
    }

    for (int p=0; p<E; p++)//sprawdzamy czy nie ma krawedzi wielokrotnych
    {



        for (int m=p+1; m<E; m++)//sprawdzamy czy nasz graf jest 1 grafem
        {

            if(kraw[0][p]==kraw[0][m]&&kraw[1][p]==kraw[1][m])
            {
                cout<<"Ten graf nie jest sprzezony, poniewaz nie jest 1-grafem"<<endl;
                exit(0);
            }

        }
    }

    int hel=0;//pomocnicza dotakich samych

    int og_counter=0;
    int licznikliniowego=0;

    for(int z=0; z<E; z++)//for sprawdzający nasz drugi warunek sprzezonego(jesli takie same nastepniki to tylko te i brak wsplnego poprzednika)
    {
        int prwk=0;//zmienna liczaca prawidlowosci warunku nr 2

        int kunt=0;


        hel=kraw[0][z];


        for(int x=0; x<E; x++)//zliczamy nastepniki
        {
            if(kraw[0][x]==hel)kunt++;
        }
        int * tesame=new int [kunt];//dynamiczna tablica do przechowania nastepnikow "takich samych"


        int cz=0;//pomocnicza zmienna do wpisywania następnikow do tablicy


        for(int o=0; o<E; o++)//wprowadzamy nastepniki do tablicy
        {
            if(kraw[0][o]==hel)
            {
                tesame[cz]=kraw[1][o];
                cz++;
            }
        }


        int leh;
        for(int q=0; q<E; q++)//szukamy poprzednikow do porownania
        {

            int lts=0;//licznik takich samych nastepnikow
            if(kraw[0][q]==hel)//"nie sprawdzamy tego samego"
            {

                continue;


            }
            else//porownujemy do innych wirzcholkow
            {

                //tak samo jak wyzej , zliczenie nastepnikow powrownywanego
                leh = kraw[0][q];


                int tnuk=0;
                for(int y=0; y<E; y++)//zliczamy nastepniki
                {
                    if(kraw[0][y]==leh)tnuk++;
                }


                int * emaset=new int[tnuk];//druga tablica wielkosci ilosci zliczanych
                int llehpom=0;
                for(int b=0; b<E; b++)//wpisujemy nastepniki do porownania
                {
                    if(kraw[0][b]==leh)
                    {
                        emaset[llehpom]=kraw[1][b];
                        llehpom++;
                    }
                }




                for(int r=0; r<kunt; r++)//zliczamy ile jest takich samych nastepnikow
                {
                    for(int t=0; t<tnuk; t++)
                    {
                        if(tesame[r]==emaset[t])
                        {

                            lts++;
                        }


                    }
                }
            }






            if(lts==kunt||lts==0)//wszystkie lub zadnie nie sa zgodne
            {
                prwk++;

            }

            if(lts==kunt)//jesli wszystkie sa zgodne to sprawdzamy czy nie maja wspolnego poprzednika
            {
                int tabliniowego=0;//liczba poprzedników hel
                int tabliniowego2=0;//liczba poprzednikow leh
                for(int i=0; i<E; i++)
                {
                    if(kraw[1][i]==hel)tabliniowego++;
                    if(kraw[1][i]==leh)tabliniowego2++;
                }
                if(tabliniowego!=0||tabliniowego2!=0)
                {
                    int * pnaliniowy=new int [tabliniowego];
                    int * pnaliniowy2=new int [tabliniowego2];

                    int pomocniczek=0;
                    int pomocniczek2=0;

                    for(int i=0; i<E; i++)
                    {
                        if(kraw[1][i]==hel)
                        {
                            pnaliniowy[pomocniczek]=kraw[0][i];
                            pomocniczek++;
                        }
                        if(kraw[1][i]==leh)
                        {
                            pnaliniowy2[pomocniczek2]=kraw[0][i];
                            pomocniczek2++;
                        }
                    }

                    int lik=0;

                    for(int p=0; p<tabliniowego; p++)//zliczamy liczbe tych samych poprzednikow
                    {
                        for(int u=0; u<tabliniowego2; u++)
                        {
                            if(pnaliniowy[p]==pnaliniowy2[u])lik++;
                        }
                    }

                    if(lik>0)liniowy=false;//jesli wystepuje wspolny poprzednik to graf nie jest liniowy

                }
            }



        }

        if(kunt>1)prwk=prwk+kunt-1;//zliczamy "prawdilowosc" dla naszego wierzcholka w stosunku do pozostalych
                                    //wylaczajac jego samego

        if(prwk==E-1)og_counter++;//E-1 bo nie porownujemy z samym sobą


    }


    if(og_counter==E)//sprawdzenie czy prawidlowosc zachodzi dla wszystkich wierzcholkow
    {
        cout<<endl;
        cout<<"Ten graf jest sprzezony"<<endl;
        cout<<endl;
    }
    else
    {
        cout<<endl;
        cout<<"Ten graf nie jest grafem sprzezonym ,poniewaz nie spelnia warunku dotyczacego nastepnikow"<<endl;
        cout<<endl;
        exit(0);
    }


	if(liniowy==true)
    {
        cout<<endl;
        cout<<"Ten graf jest liniowy"<<endl;
        cout<<endl;
    }

    else
    {
        cout<<endl;
        cout<<"Ten graf nie jest liniowy"<<endl;
        cout<<endl;
    }


    int kraw_2[3][V];//tabela na graf org

    int ednew=1;//kolejne wirzecholki w kraw[3][x]


    for(int i=0; i<V; i++)
    {

        kraw_2[2][i]=ednew;
        kraw_2[1][i]=0;
        kraw_2[0][i]=0;
        ednew++;

    }


    int vert=1;//zmienna do przydzielania nowych wierzchołków

    for(int j=1; j<=V; j++)
    {


        for(int k=0; k<E; k++)
        {
            if(kraw[0][k]==j)
            {
                if(kraw_2[0][j-1]!=0)//jesli nasz ma juz nadane
                {
                    int nastepnik2 = kraw[1][k];//nastepnik
                    if(kraw_2[0][nastepnik2-1]==0)//jesli nastepnik ma jeszcze nie nadane jako wyjsciowy
                    {
                        if(kraw_2[1][j-1]==0)//jesli nastepnik nie ma nadane
                        {
                            kraw_2[1][j-1]=vert;
                            kraw_2[0][nastepnik2-1]=kraw_2[1][j-1];

                            vert++;
                        }
                        else if (kraw_2[1][j-1]!=0)//jesli nastepnik ma juz nadany wierzchołek ale tylko jako nastepnik
                        {
                            kraw_2[0][nastepnik2-1]=kraw_2[1][j-1];
                        }

                    }
                    else if(kraw_2[0][nastepnik2-1]!=0)//jesli nastepnik ma nadane jako wyjsciowy
                    {
                        kraw_2[1][j-1]= kraw_2[0][nastepnik2-1];
                    }


                }



                else if(kraw_2[0][j-1]==0)//jesli nasz nie ma jeszcze nadane
                {
                    int nastepnik = kraw[1][k];
                    if(kraw_2[0][nastepnik-1]==0)//jesli nastepnik pusty
                    {
                        kraw_2[0][j-1]=vert;
                        kraw_2[1][j-1]=vert+1;
                        kraw_2[0][nastepnik-1]=kraw_2[1][j-1];
                        vert+=2;
                    }
                    else if(kraw_2[0][nastepnik-1]!=0)//jesli nastepnik ma juz nadane
                    {
                        kraw_2[0][j-1]=vert;
                        kraw_2[1][j-1]=kraw_2[0][nastepnik-1];
                        vert++;

                    }
                }
            }

        }










    }



    for(int n=1; n<=V; n++)//obsluga wierzcholkow bez nastepnikow
    {
        for(int s=0; s<E; s++)
        {
            if (kraw[1][s]==n)
            {
                if(kraw_2[0][n-1]==0)
                {
                    kraw_2[0][n-1]=vert;
                    vert++;
                    if(kraw_2[1][n-1]==0)
                    {
                        kraw_2[1][n-1]=vert;
                        vert++;
                    }

                }
                else if(kraw_2[0][n-1]!=0)
                {
                    if(kraw_2[1][n-1]==0)
                    {
                        kraw_2[1][n-1]=vert;
                        vert++;
                    }

                }

            }
        }
    }
    for(int a = 1;a <= V;a++)
    {
        for(int b = 0 ;b < l_izolowanych;b++)
        {
            if(a == izolowane[b] && kraw_2[0][a-1] == 0)
            {
                kraw_2[0][a-1] = vert;
                vert++;
                kraw_2[1][a-1] = vert;
                vert++;
            }
        }
    }


   /* for(int l=0; l<V; l++)
    {
        cout<<kraw_2[0][l]<<"'->"<<kraw_2[1][l]<<"' KRAWEDZ Z WIERZCHOLKA "<<kraw_2[2][l]<<endl;
    }*/

for(int t=0;t<E;t++)//korekta przypadku
{
    int asdf=kraw[0][t];
    int fdsa=kraw[1][t];
    if(kraw_2[1][asdf-1]!=kraw_2[0][fdsa-1])
    {
        kraw_2[0][fdsa-1]=kraw_2[1][asdf-1];
    }

}


    for(int l=0; l<V; l++)
    {
        cout<<kraw_2[0][l]<<"'->"<<kraw_2[1][l]<<"' KRAWEDZ Z WIERZCHOLKA "<<kraw_2[2][l]<<endl;
    }

    int E_org=V;
    int V_org=vert-1;
    int izol_org= 0;

    cout<<endl;
    cout<<"Prosze podac nazwe pliku do zapisu:"<<endl;
    cout<<endl;
    string dozapisu;
    cin>>dozapisu;
    dozapisu=dozapisu + ".txt";


    fstream plikzapisowy;
    plikzapisowy.open(dozapisu.c_str(),ios::out);
    if( plikzapisowy.good() )
    {
        plikzapisowy<<V_org<<" "<<E_org<<" "<<izol_org<<endl;

        for( int i=0; i<V; i++)
        {
            plikzapisowy<<kraw_2[0][i]<<" "<<kraw_2[1][i]<<endl;

        }
        plikzapisowy.close();
    }







    return 0;

}
