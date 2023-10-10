#include <stdio.h>
#include <stdlib.h>

// Anzahl aller Zeicher (ohne Null-terminator).
// Funktion nimmt als Eingabe einem String (bzw. Zeiger auf dem erstem Character in der Zeichenkette)
// Rückgabewert ist ein Integer mit der menge der Zeichen OHNE den Nullterminator (also Netto)
// funktioniert nur mit ASCII Zeichenketten, bei UTF-xyz wird die menge des Belegten Speichers, nicht die Anzal der Zeichen zurückgegeben
int length(char *s) {
  int n = 0;    // Definiere Integer Variable n und initialisiere diese mit 0
  while(*s != '\0') {   // solange das Zeichen auf dem der Zeiger zeicht nicht der Nullterminator ist
    n++;    // zeichen hochzehlen
    s++;    // Zeicher auf das nächste Zeichen in der Zeichenkette verschieben
  }

  return n; // menge der Zeichen zurückliefern
}


// Kopiere n Zeichen von s nach t.
// Annahme: n ist > 0
// Funktion nimmt als Eingabe (s sowie t) zwei String (bzw. Zeiger auf dem erstem Character in diesen Zeichenketten)
// der dritte Parameter ist die menge der Zeichen die kopiert werden sollen
// Vorsicht, falls n der netto länge entspricht, wird der Nullterminator nicht mitkopiert! 
void copy(char* s, int n, char* t) {
  int i = 0;     // Definiere Integer Variable i und initialisiere diese mit 0
  while(i < n) {    // solange i < n, bei n = 5  wird i so die Werte 0,1,2,3,4 
    t[i] = s[i];    // copiere ein Byte/Char von der Quelle (s) zum Ziel (t) an der Stelle [i]
    i++;            // index um eins erhöhen
  }
}



// Baue neuen String welcher mit Zeichen c startet gefolgt von allen Zeichen in s.
// Erster Parameter (c) ist das Zeichen das eiungefügt werden sollte
// Zweiter Parameter ist der String in dem das Zeichen eingefügt werden sollte
char* putFront(char c, char* s) {
  const int n =  length(s); // bestimme die Netto Länge der Zeichenkette
  char* r = (char*)malloc(sizeof(char) * (n+2));    // Reserviere Speicherplatz auf dem Heap. 
                                                    // Die Reservierte Zeichenmenge entspricht der :
                                                    // Nettoneichemenge + c + Nullterminator, also 2 Zeichen mehr als in n 
  copy(s, n+1, r+1);    // Kopiere von b nach t+1 so das im t vorne ein Platz für das hinzufügen von c bleibt
                        // die zu Kopierende Menge n+1, Was der Bruttomenge entspricht (Zeichenkette+Nulterminator)
  r[0] = c;             // Füge c am Anfangder Zeichenkette r
  return r;             // neuerstellte Zeichenkette zurückgeben
}

// Liefere laengsten Prefix in welchem
// keine zwei hintereinander folgenden Doppelpunkte (::) vorkommen.
//
// Beispiele:
// extractPrefix("Hallo") => "Hallo"
// extractPrefix(":H::all::o") => ":H:"
//
// Beachte.
//
char* extractPrefix(char *s) {
  char c;
  char* r;

  if(length(s) <= 1) {      // wenn die Zeichenkette weniger als zwei Zeichen lang ist 
    return s;               // gibt es nichts zum umdrehen
  }

  if(s[0] == ':' && s[1] == ':') {      // wenn das Aktuelle Zeichen sowie das diesem folgende Zeichen ein Doppelpunkt sind (also "::")
    r = (char*)malloc(sizeof(char) * 2);    // reserviere Platz für zwei Zeichen
    r[0] = ':';                     // erstes Zeichen im neuem String ist ein Doppelpunkt   
    r[1] = '\0';                    // zweites Zeichen im neuem String ist der Nulterminator
    return r;                       // Rücksprung und ende der allerseits beliebten Rekursion
  }

  c = s[0];                         // erstes Zeichen aus der Zeichenkette auslesen
  r = extractPrefix(s+1);           // ruffe sich selbst, mit dem Zeiger auf das zweite Zeichen in der Zeichenkette 

    // SPEICHERLECK!!!
  return putFront(c,r);             // einfüge Zeichen c am Anfang der Zeichenkette r
}



char* reverse(char* s) {
  const int n = length(s);
  char* t = (char*)malloc(n + 1);
  int i;

  for(i = 0; i < n; i++) {
    t[i] = s[n-1-i];
  }
  t[n] = '\0';

  return t;
}

char* extract(char* s) {
  return(reverse(extractPrefix(reverse(s))));

}

void tests(char* (*extr)(char*)) {
  int i;
  char* strings[] = {
    "Hallo",
    "H:all:o",
    "H::allo::o",
    "::Hallo",
    "::Hallo::",
    ":H::all::o"
  };

  for(i=0; i < 6; i++) {
    printf("\n %s => %s",strings[i], extr(strings[i]));
  }
}


int main() {
  printf("\n extractPrefix \n");
  tests(&extractPrefix);

  printf("\n extract \n");
  tests(&extract);


}
