#include <stdio.h>


// Rationale Zahlen: Zaehler/Nenner.
// Repraesentiert als struct.
// Oft schreiben wir x1/x2 als Kurzform fuer x.Zahler/x.Nenner.
struct RZ_ {
    int Zaehler;        // Zähler ist eine integer Variable
    int Nenner;         // Nenner ist eine integer Variable
};

// Abkuerzende Schreibweise.
typedef struct RZ_ RZ;      // Struktur RZ_ als Typ RZ definieren so das diese zu Variablendefinition verwendet werden kann.

// Geht auch direkt. Typedef kombiniert mit Strukturdeklaration.
/*
typedef struct RZ_ {
    int Zaehler;
    int Nenner;
} RZ;
*/

// Vorwaertsfunktions Deklarationen
// dammit die Funktionen bei Aufruf bekannt sind, sonnst nimmt der Kompiler an, das diese vom typ <int funktion(int)> sind
void printRZ(RZ x);
RZ scanRZ();
RZ multRZ(RZ x, RZ y);
RZ addRZ(RZ x, RZ y);
RZ skaliereRZ(RZ x, int k);



// Ausgabe.
// den übergeben Bruch auf der Konsole Ausgeben
void printRZ(RZ x) {
  printf("%d/%d", x.Zaehler, x.Nenner); // Nenner und Zähler als dezimale Ganzzahlen ausgeben
}

// Eingabe.
RZ scanRZ() {
  RZ x;     // erzeuge lokale Variable (auf dem Stack) für den Bruch
  
  scanf("%d", &x.Zaehler);      // den Zähler einlesen
  printf(" / ");
  scanf("%d", &x.Nenner);       // den Näner einlesen

  return x;     // gebe den eingeledenen Bruch als flache Kopie zurück
}

// Multiplikation ist Komponenteweise.
//   x1/x2 * y1/y2
// = (x1*y1) / (x2*y2)
RZ multRZ(RZ x, RZ y) {
  RZ z;      // erzeuge lokale Variable (auf dem Stack) für den Bruch

  z.Zaehler = x.Zaehler * y.Zaehler;    // multipliziere den Zähler von x mit dem Zähler von y, speichere das Ergebnis in den Zähler von z      
  z.Nenner = x.Nenner * y.Nenner;       // multipliziere den Nenner von x mit dem Nenner von y, speichere das Ergebnis in den Nenner von z

  return z; // gebe den multiplizierten Bruch als flache Kopie zurück
}



// Skaliere.
// die variable x vom Typ RZ wird als flache Kopie (shallow copy, Call by Value) übergeben. 
// somit wird bei der Übergabe eine neue Variable/Objekt (als Struktur) erzeugt
// die Werte für Zähler und Nenner werden aus dem Original automatisch kopiert
// die Variable k wird als Coll by Value übergaben
RZ skaliereRZ(RZ x, int k) {
  RZ z;                         // erzeuge lokale Variable (auf dem Stack) für den Bruch

  z.Zaehler = x.Zaehler*k;      // multipliziere Zähler mit Skalierer
  z.Nenner  = x.Nenner*k;       // multipliziere Nenner mit Skalierer

  return z;                     // gebe den neu skalierten Bruch zurück 
}


// Variante mit Referenzuebergabe.
// die variable x vom Typ RZ wird als Zeiger übergeben
// die Variable k wird als Coll by Value übergaben
void skaliereRZ2(RZ *x, int k) {
  RZ z;                             // erzeuge lokale Variable (auf dem Stack) für den Bruch (wird nicht verwendet)

  (*x).Zaehler = (*x).Zaehler*k;    // multipliziere Zähler mit Skalierer
  (*x).Nenner  = (*x).Nenner*k;     // multipliziere Nenner mit Skalierer
  
  // da x als call by reference aufgeruffen wurde, ist hier keine Rückgabe notwendig, da hier mit dem "Original" Objekt gearbeitet wurde
}



// Addition. Auf gemeinsamen Nenner bringen.
//   x1/x2 + y1/y2
// = (x1*y2) / (x2*y2)   +  (y1*x2) / (x2*y2)
// = (x1*y2 + y1*x2) / (x2*y2).
RZ addRZ(RZ x, RZ y) {
  RZ z, xTemp, yTemp;           // lokale Variablen (Strukturen) für Brüche z, xTemp sowie yTemp auf demm Stack erzeugen

  xTemp = skaliereRZ(x, y.Nenner);      // rufe skaliereRZ2 auf, x sowie y.Nenner werden als call by Value Übergeben
  yTemp = skaliereRZ(y, x.Nenner);      // rufe skaliereRZ2 auf, y sowie x.Nenner werden als call by Value Übergeben
  z.Zaehler = xTemp.Zaehler + yTemp.Zaehler;    // addiere den x sowie y Zähler und speichere das Ergebnis in den z Zähler
  z.Nenner  = xTemp.Nenner;                     // Nenner aus dem der Struktur yTemp in die z Struktur Übertragen (Wert direkt kopieren)

  return z;                      // Variable z zurückgeben. Die Rückgabe erfolgt über eine flache Kopie
}


// Add Variante welche skaliereRZ2 verwendet
// Die Variablen x und y vom Typ RZ werden hier als Call by Value über eine flache Kopie übergeben
RZ addRZ2(RZ x, RZ y) {
  RZ z;                                 // erstelle eine lokale Variable Z vom Typ RZ auf dem Stack
                                        // die erstellte Variable wird nicht explizit Initialisiert
                                        // die darin enthaltene Werte sind zufällig (das was an der Speicherdtelle im Stack bereits da war)

  skaliereRZ2(&x, y.Nenner);            // rufe skaliereRZ2 auf, x wird als Call by referenze, y.Nenner als call by Value Übergeben
  skaliereRZ2(&y, x.Nenner);            // rufe skaliereRZ2 auf, y wird als Call by referenze, z.Nenner als call by Value Übergeben
  z.Zaehler = x.Zaehler + y.Zaehler;    // multipliziere Zähler von x mit dem Zähler von y , Speichere das Ergebnis in dem Zähler von z
  z.Nenner  = x.Nenner;                 // nener von x nach z kopieren

  return z;                             // Variable z zurückgeben. Die Rückgabe erfolgt über eine flache Kopie
}

// Beachte:
// In C muessen all Variablen am Anfang der Funktion deklariert werden.
// In C++ duerfen Variablen auch innerhalb einer Funktion definiert werden.
void test1() {
  RZ x, y, z;                   // lokale Variablen (Strukturen) für Brüche x, y sowie z auf demm Stack erzeugen

  printf("Test 1 \n");

  printf("Eingabe1: \n");
  x = scanRZ();                 // Bruch x einlesen

  printf("\n Eingabe2: \n");
  y = scanRZ();                 // Bruch y einlesen


  printRZ(x); printRZ(y);       // Bruch x sowie y auf der Konsole Ausgeben

  printf("\n Add Ausgabe: ");
  printRZ(addRZ(x,y));          // Brücher x sowie y Addieren (Call by Value) sowie auf den Konsole Ausgeben

  printf("\n Mult Ausgabe: ");
  printRZ(multRZ(x,y));         // Brücher x sowie y Multiplizieren (Call by Value) sowie auf den Konsole Ausgeben

}


// Testfunktion

void unitTest1() {
  RZ x, y, z;                   // lokale Variablen (Strukturen) für Brüche x, y sowie z auf demm Stack erzeugen

  x.Zaehler = 5; x. Nenner = 3;         // x = 5/3
  y.Zaehler = 3; y.Nenner = 5;          // y = 3/5

  z = multRZ(x,y);                      // multipliziere den Bruch x mit dem Bruch y        
                                        // beide Brüche werden als flache Kopiern an die multRZ funktion übergeben
                                        // z wird aus dem Funktionsergebnis, der als Flache Kopie übergeben wurde, wiederum als eine Flache Kopie Übernommen 

  if(z.Zaehler != z.Nenner)             // wenn Zähler und Nennen nicht gleich sind
     printf("\n Fehler");               // Wort "Fehler" auf der Konsole ausgeben


  x.Zaehler = 2; x. Nenner = 3;         // x = 2/3
  y.Zaehler = 1; y.Nenner = 3;          // y = 1/3

  z = addRZ(x,y);                       // Brüche x sowie y Addieren. Übergebe der brüche sowie übername 
                                        // des Rückgabewertes erfolgt als flache Kopie (Call by value)

  if(z.Zaehler != z.Nenner)             // wenn Zähler und Nennen nicht gleich sind
     printf("\n Fehler");               // Wort "Fehler" auf der Konsole ausgeben
}


// Funktion intertiert einem als Variable (flache Kopie, call by Value) übergebenen Bruch
RZ inverseRZ(RZ x) {
  int tmp;          // Variable tmp als integerwert auf dem Stack definieren

  tmp = x.Zaehler;      // Zähler des Bruches in die Temporäre Variable kopieren
  x.Zaehler = x.Nenner; // Nenner in de Zähler kopieren
  x.Nenner = tmp;       // // Nenner aus der temporären Variable Übernehmen 

  return x;         // Bruch als flache Kopie zurückgeben
}


void invarianten() {
  int i,n,m;        // Lokale Integer-Variablen (Stack) i,n,m definieren (ohne Initialisierung ! d.h Werte sind vorerst zufällig)
  RZ rz[4] = { {1,2}, {3,4}, {5,2}, {4,7} };   // Fest definierte Auswahl von Tests
                                                // Feld mit vier Variablen von Typ RZ definieren
                                                // und mit Werten Initialisieren
                                                // jedes Päörchen in den Klammern entspricht einem Bruch {Zähler, Nenner)
  
  RZ x,y,z;             // lokale Variablen (Strukturen) für Brüche x, y sowie z auf demm Stack erzeugen
  n = 4;                // Variable n mit 4 initialisieren


  // mult: n/m * m/n liefert Zaehler == Nenner
  for(i=0; i<n; i++) {      // folgenden Codeblock n mal ausführen, dabei wir bei jedem Schleifendurchlauf die Variable i hochgezählt  
    x = multRZ(rz[i], inverseRZ(rz[i])); // Multipliziere der Bruch der an der Stelle i im Feld gespeichert ist mit seiner invertierten Version
    if(x.Zaehler != x.Nenner)           // wenn Zächler von x mit dem Nenner von x nicht übereinstimmt 
        printf("\n Fehler");            // Ausgabe auf der Konsole "Fehler"
  } // ende der for schleife


    // dieser codeblock führt die Operatrion in der Inneren schleife insgesamt 25 mal aus 
    // für n = 1,sowie nacheinander für  m = 1,2,3,4,5
    // für n = 2,sowie nacheinander für  m = 1,2,3,4,5
    //...
    // für n = 5,sowie nacheinander für  m = 1,2,3,4,5
    // n ist die äußere Schleife m ist die innere Schleife
    
  for(n = 1; n <6; n++) { // folgenden Codeblock 5 mal (für n = 1,2,3,4,5) ausführen, dabei wir bei jedem Schleifendurchlauf die Variable n hochgezählt  
    for(m = 1; m < 6; m++) { // folgenden Codeblock 5 mal ausführen (für m = 1,2,3,4,5), dabei wir bei jedem Schleifendurchlauf die Variable m hochgezählt  
      x.Zaehler = n; x.Nenner = m;   // Bruch x = n/m
      y.Zaehler = m; y.Nenner = n;   // Bruch y = m/n
      z = multRZ(x,y);              // Brücher x sowie z miteinander multiplizieren

      if(z.Zaehler != z.Nenner)     // wenn zähler von Bruch x ungleich den Nenner vom Bruch x
          printf("\n Fehler");      // Ausgabe "Fehler" auf der Konsole

    }
  }

  // add: 1/m + (m-1)/m liefert Zaehler == Nenner
  m = 10;   // initialiseiere die Variable m mit 10
  for(i=2; i<m; i++) { // folgenden Codeblock 8 mal (für i = 2,3,4,5,6,7,8,9) ausführen, dabei wir bei jedem Schleifendurchlauf die Variable i hochgezählt  
    x.Zaehler = 1; x.Nenner = i;        // Bruch x = 1/i => {1/2, 1/3, 1/4,...1/9)
    y.Zaehler = i-1; y.Nenner = i;      // Bruch y = (i-1/)i  =>  (1/2, 2/3,3/4...8/9)  
    z = addRZ(x,y);                     // Addiere Brüche x und y , Ergebnis ist der Bruch z der i/i sein sollte
    if(z.Zaehler != z.Nenner)           // Wenn der zähler ungleich dem Nenner
      printf("\n Fehler %d %d %d \n", i, z.Zaehler, z.Nenner); // Gebe Fehlermeldung auf der Konsole aus 
  }

  // add2 Variante
  // Folgende Abschnitt ist mit dem Vorhergehenden fast identisch, hhier wird allerdings die addRZ2 Funktion statt addRZ aufgeruffen !
    for(i=2; i<m; i++) { // folgenden Codeblock 8 mal (für i = 2,3,4,5,6,7,8,9) ausführen, dabei wir bei jedem Schleifendurchlauf die Variable i hochgezählt  
    x.Zaehler = 1; x.Nenner = i;        // Bruch x = 1/i => {1/2, 1/3, 1/4,...1/9)
    y.Zaehler = i-1; y.Nenner = i;      // Bruch y = (i-1/)i  =>  (1/2, 2/3,3/4...8/9) 
    z = addRZ2(x,y);                    // Addiere Brüche x und y , Ergebnis ist der Bruch z der i/i sein sollte
    if(z.Zaehler != z.Nenner)           // Wenn der zähler ungleich dem Nenner
      printf("\n Fehler %d %d %d \n", i, z.Zaehler, z.Nenner);  // Gebe Fehlermeldung auf der Konsole aus 
  }
}



// Hauptfunktion des Programms
int main() {    

  // test1();
  unitTest1();      // führe dir Funktion unitTest1() aus

  invarianten();    // führe dir Funktion invarianten() aus
}
