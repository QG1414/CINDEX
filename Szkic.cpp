DZEWO BST - szkic       "Index slow"
===============
PROBLEM
------
Napisac program wczystujacy slowa (identyfikatory) z pliku tekstowego i wstawiajacy je do drzewa BST
wraz z numerem linii, w ktorej to slowo wystapilo,
przy czym jesli slowo w drzewie juz istnieje to zwiekszny jest licznik wystapien oraz 
dodawany jest kolejny numer linii, w ktorym slowo wystapilo ponownie (lista wystapien z podwojna glowa- jak w fifo
                                                                      bo dadawanie na koncu listy aby byla od razu posortowana).
Numery linii nie powtarzaja sie na liscie


UWAGA:
slowo to dowolny ciag znakow zaczynajacy sie od podkreslenia lub litery i potem sa litery lub cyfry lub podkreslenia
(czyli dokladnie jest to identyfikator w jezyku programowania). NIe wolno uzywac w pliku teksowym 
polskich znakow diakrytycznych (dla ULATWIENIA)

NA wejsciu: wiec dowolny plik tekstowy - parametr programu (jak bylo juz w poprzenidch projektach)
-------------
NA Wyjsciu: wydrukowane drzewo w inorder (slowa beda w kolejnosci alfabetycznej z iloscia wystapien i lista wystapien od 
                                          najmniejszej liczby do najwiekszej - czyli tak jak sa dodawane) // jak w fifo zmieniamy z wskaŸnika na inta -> robimy kopie i zmieniamy z global na int
-------------

int main( int argc, char* argv[] )
{
  sprawdzic parametr programu (czy jest)
  wywolac funkcje wczytujaca plik (w niej otworzyc i zamknac) i budujACA DDRZEWO bst // ta funkcja czytajaca plik to glowny element
  wywolac funkcje drukujaca do plik (np IndeksSlow.txt)
  zwolnic drzewo
  koniec
}

----------
// gdyby zdazylo sie slowo wieksze niz 40 znakow to tylko wpisujemy pierwsze 40
// tworzymy drzewo callockiem -> counter ustawiamy na 1 -> na pFifo pQCreate i enqueue
// gdyby by³o s³owo i wywo³a³o siê Visit( slowo plus gdzie ) counter++ i enqueue
// drukowanie to s³owo, counter plus do drukowania queue
// przy usuwaniu free na char*, na fifo FQRemove i tyle.
w pliku naglowkowym zdefiniowac odpowiedni typ dla elementu drzewa binarnego o nazwie TreeItem:
Podobnie jak dla listy tylko teraz definujemy poddrzewa: pLeft, pRight 
(wsk na ta sama strukture TreeItem jak w liscie)
Dodatkowo, w typie musi byc pole wskaznik na slowo (alokacja tablicy 41 znakowa - slowa 40 znakowe),
pole counter do pamietania liczby wystapien 
oraz wskaznik na FIFO - lista do zapamietywania numerow linii - ale zawsze na koncu. 

Prosze wykorzystac modul FIFO z dwoma wskazniklami
pHead i pTail (co bylo pisane) i polem int (numer linii).
Typ dla listy (te dwa wskazniki) musi byc wczesniej przed typem elementu drzewa 
a typ dla elementu listy jeszcze wczesniej 

Dzieki temu bedzie mozna bardzo latwo wypisac numery linii w jakich wystapilo slowo przelgadajac liste 
od pierwszego elementu do ostatniego
----------

//w findInsert dodajemy str* i numer linii
Przy wstawianiu do drzewa nie alokowac nowej pamieci ale podwiazac wsk na (slowo) tablice pod wskaznik w elemencie drzewa

// alokowac str przy czytaniu
// otwieramy sprawdzamy czy udalo sie (return 0,1) -> czytamy po jednym znaku
// zewnetrzna petla az do znaku nowej linii
// gdy znajdziemy element ktory moze byc pierwsza litera identyfikatora to wtedy alokujemy tablice 41 elementow wstawiamy od razu
// nastepnie wewnetrzna petla ktora doczytuje znaki az do konca pliku lub spacji lub znaku nie identyfikatora
// po zczytaniu wstawiamy do drzewa

Wydruk do pliku:
Przegladac drzewo w InOrder i wypisywac kolejno odwiedzane wezly drzewa. wW ten sposob dostaniemy 
posortowany indeks slow
wypisuje sie slowo a potem ilosc wystapien w nawiasie 
a potem numery linii w ktorych wystapilo (wszyskto w jednej linii)


UWAGA:
nalezy napisac wlasna funkcje porownujaca
    int compStr( char* s1, char* s2 )
lancuchy znakowe bo ma byc niezalezne od duzych i malych liter
// cala funkcja napisana tylko przy pomocy funkcji bibliotecznych

SZKIC: (stosujemy wylacznie funkcje biblioteczne standardowego C )
-----------
// mozna olac sprawdzanie alokacji pamieci
alokowac pamiec str1 na kopie parametru pierwszego // alokujemy na strlen + 1 
alokowac pamiec str2 na kopie parametru drugiego
wkopiowc do str1 pierwszy parametr  (odpowienida funkcja biblioteczna --> string.h) // strcpy
wkopiowc do str2 drugi parametr     (odpowienida funkcja biblioteczna --> string.h)
zamienic w str1 wszystko na male ( funkcja _strlwr()  ---> string.h )  // _strupr <=> na du¿e
zamienic w str2 wszystko na male ( funkcja _strlwr()  ---> string.h )
porownac i zapamietac wynik  (odpowiednia funckja porownujaca lancuchy znakowe ---> string.h) // strcmp
zwolnic str1 // free
zwolnic str2 // free
zwrocic zapamietany wynik

// dodatkowo
//stala na alokacje 5 znakow (stala)
// jezeli zapelnie to o kolejne 5


// funkcja realloc, je¿eli *pTab jest null to robi malloc, inaczej 
// 
// void AllocAddMemBets( int*** pTab, int nCurrSize )
// int** pTemp = (Player**)realloc( *pTab, (nCurrSize + ALLOCPLAYER) * sizeof( Player* ) );
// *pTab = pTemp
// memset( *pTab + nCurrSize, 0, ALLOCPLAYER ) usuwamy ostatnia wartosc