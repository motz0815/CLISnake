#include <iostream>
#include <ncurses.h>
#include <ctype.h>
#include <termios.h>
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

int score,highscore;
char retry='y';


int main()
{
    cout << endl;
    cout << endl;
    cout << "  ***** *   *  ***  *   * *****\n";
    cout << "  *     **  * *   * * *   *\n";
    cout << "  ***** * * * ***** **    ***\n";
    cout << "      * *  ** *   * * *   *\n";
    cout << "  ***** *   * *   * *   * ******\n";
    cout << endl;
    cout << " Press Any Key to Continue"<<endl;
    getch();

    while (retry=='y' || retry == 'Y')
    {
        srand(time(NULL));
        score=0;
        int pion=(rand()-1)%18+1; // Zufaellige Platzierung des Essens
        int poin=(rand()-1)%18+1;
        int x[100]; // Laenge der Schlange soll nicht mehr als 100 sein
        int y[100];
        x[0]=10; // Startpunkt der Schlange definieren
        y[0]=10;
        x[1]=9;
        y[1]=10;
        x[2]=8;
        y[2]=10;

        int ular=3 ;
        string a[20][20]; // Spielfeldgroesse
        char ctr='d'; // Bewegungsrichtung der Schlange am Anfang
        while (x[0]!=0 && x[0]!=19 && y[0]!=0 && y[0]!=19)
        {
            for (int i=0;i<20;i++)
            {
                for (int j=0;j<20;j++)
                {
                    if (i==0 || j==0 || i==19 || j==19)
                         a[i][j]="* "; // Raender des Spielfelds ausgeben
                    else
                         a[i][j]="  "; // Leerfelder ausgeben
                }
            }
            a[poin][pion]="o "; // Essen drucken
            for(int s=ular;s>0;s--)
            {
                x[s]=x[s-1]; // damit Koerper und Schwanz dem Kopf der Schlange folgen
                y[s]=y[s-1];
            }
            for (int r=0;r<=ular;r++)
            {
                a[y[r]][x[r]]="* ";
            }
            if (kbhit()) // Eingabe abfragen w, a, s, d zur Steuerung
            {
                ctr=getch();
            }
            if(ctr=='w')
                y[0]--;
            if(ctr=='s')
                y[0]++;
            if(ctr=='a')
                x[0]--;
            if(ctr=='d')
                x[0]++;

            for(int m=0;m<20;m++)
            {
                for (int n=0;n<20;n++)
                {
                    cout << a[m][n]; // Spielfeld aktualisieren
                }
                cout << endl;
            }
            if (a[0][0]==a[poin][pion]) // Schlange trifft auf Essen und wird um 1 vergroessert
            {
                ular++;
                poin=rand()%19;
                if (poin%19==0)
                    poin++;
                pion=rand()%19;
                if (pion%19==0)
                    pion++;
                score=score+1;
             }
            for (int gh=1;gh<ular;gh++) // Schlange stirbt wenn sie Hindernis trifft
            {
                if (x[0]==x[gh] && y[0]==y[gh] )
                {
                    x[0]=0;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(25)); // Bei jedem Durchlauf 25ms warten
            system("clear"); // Bildschirm loeschen
        }
        cout << "GAMEOVER!" <<endl;
        cout << "Score = " << score<<endl;
        if (score > highscore)
        {
            highscore=score;
        }
        cout << "High Score: "<<highscore<<endl;
        cout << "Retry (y/n): "; cin >>retry;
    }
    return 0;
}
