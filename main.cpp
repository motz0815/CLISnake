#include <iostream>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

int score,highscore;
char retry='y';


int main()
{
    // Startscreen printen
    cout << endl;
    cout << endl;
    cout << "  ***** *   *  ***  *   * *****\n";
    cout << "  *     **  * *   * * *   *\n";
    cout << "  ***** * * * ***** **    ***\n";
    cout << "      * *  ** *   * * *   *\n";
    cout << "  ***** *   * *   * *   * ******\n";
    cout << endl;
    cout << " Press Any Key to Continue"<<endl;
    getch(); // Auf Eingabe warten

    while (retry == 'y' || retry == 'Y') // Solange ausführen, wie geretryt wird
    {
        srand(time(NULL)); // Rand init
        score=0;
        int pion=(rand()-1)%18+1; // Zufällige Platzierung des Essens
        int poin=(rand()-1)%18+1;
        int x[100]; // Länge der Schlange soll nicht mehr als 100 sein
        int y[100];
        x[0]=10; // Startpunkt der Schlange definieren
        y[0]=10;
        x[1]=9;
        y[1]=10;
        x[2]=8;
        y[2]=10;

        int ular=3 ;
        string a[20][20]; // Spielfeldgrösse
        char ctr='d'; // Bewegungsrichtung der Schlange am Anfang
        while (x[0]!=0 && x[0]!=19 && y[0]!=0 && y[0]!=19)
        {
            for (int i=0;i<20;i++)
            {
                for (int j=0;j<20;j++)
                {
                    if (i==0 || j==0 || i==19 || j==19)
                         a[i][j]="* "; // Ränder des Spielfelds ausgeben
                    else
                         a[i][j]="  "; // Leerfelder ausgeben
                }
            }
            a[poin][pion]="o "; // Essen drucken
            for(int s=ular;s>0;s--)
            {
                x[s]=x[s-1]; // damit Körper und Schwanz dem Kopf der Schlange folgen
                y[s]=y[s-1];
            }
            for (int r=0;r<=ular;r++)
            {
                a[y[r]][x[r]]="* ";
            }
            if (kbhit()) // Eingabe abfragen w, a, s, d zur Steürung
            {
                ctr=getch();
            }

            // Controls annehmen, W-Oben, S-Unten, A-Links, D-Rechts
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
            if (a[0][0]==a[poin][pion]) // Schlange trifft auf Essen und wird um 1 vergrössert
            {
                ular++;
                poin=rand()%19;
                if (poin%19==0)
                    poin++;
                pion=rand()%19;
                if (pion%19==0)
                    pion++;
                score=score+1; // Schlange verlängern
             }
            for (int gh=1;gh<ular;gh++) // Schlange stirbt wenn sie Hindernis trifft
            {
                if (x[0]==x[gh] && y[0]==y[gh] )
                {
                    x[0]=0; // Schlange zurücksetzen
                }
            }
            Sleep(25); // Bei jedem Durchlauf 25ms warten
            system("cls"); // Bildschirm löschen
        }
        cout << "GAMEOVER!" <<endl;
        cout << "Score = " << score<<endl;
        if (score > highscore) // Wenn neuer Highscore gemacht wurde
        {
            highscore=score; // Highscore zu derzeitigem Score ändern
        }
        cout << "High Score: "<<highscore<<endl; // Den Highscore ausgeben
        cout << "Retry (y/n): "; cin >>retry; // Retry-character annehmen (Y/y)
    }
    return 0;
}
