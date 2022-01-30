Bukás Proof könyvtár
====================

Egy könyvtár tartalmazza a 9-11-es anyag leghaszonsabb függvényeit adatstruktúrákra kategorizálva.

# Használata

<span style=" font-size:35px;">*Nevezéktan:*</span>

A függvények neveit következő szabályok szerint képezzük (amennyiben nincsen függvény választós linterünk):

* A függvények nevének első része a használni kívánt adatstruktúra angol rövidítése.
    * "Arr" - Tömb
	* "Mat" - Mátrix
	* "list" - Listák (Egyszeresen, Kétszeresen körökörös)
	* "BT", "BST", "Queue", "Stack" - Bináris Fák, Bináris Keresőfák, Sor, Verem
	* "gr" - gráf

	* "char" - karakter(karakterlánc)
* Majd az adatstruktúra neve után a művelet angolosított (néhol hosszan kifejtett) nevét melynek első betűje mindig nagy.

    * Pl. szeretnénk egy tömb méretét megtudni, szóval az adatstruktúrán neve "Arr" lesz és a művelet "size" lesz, és a szabály értelmében a "size" első betűje jelen esetben "S" lesz. Szóval meghívásnál így járunk el:
    >cout << "A tömb mérete: " << ArrSize(arr);

A könyvtár a következő típusokkal tud dolgozni:

    int
    float
    double
    long long
    char

### A könyvtár a következő adatstruktúrák hasznos fügvényeit tartlamazza:

- Tömbök
- Mátrixok
- Listák (egyszeresen, kétszeresen láncolt)
- Karakterláncok
- Dinamikus Adatszerkezetek (Verem, Sor)
- Gráfok
- Bináris fák
- Bináris keresőfák

### Függvények listája:

<span style="font-size: 25px;"><u>Tömbök:<u></span>
    
    // Kicserél két elemet (swap implementáció bármilyen típusra)
    void univ_swap(T& a, T& b);
    
    // Visszatéríti a megadott tömb méretét
    int Arrsize(T(&)[size]);
    
    // Visszatéríti a tömb elemeinek átlagát
    T ArrAvg(T(&array)[size]);
    
    // Visszatéríti a tömb elemeinek összegét
    T ArrSum(T(&array)[size]);
    
    // Eldönti hogy a tömb üres-e
     bool ArrEmpty(T(&array)[size]);
    
    // Eldönti hogy a tömb csak nullást tartlmaz
     bool Csak0(T(&array)[size]);
    
    // Eldönti hogy a tömb csak nullánál nagyobb számokat tartlmaz
     bool CsakPoz(T(&array)[size]);
    
    // Eldönti hogy a tömb csak negatív számokat tartlmaz
     bool CsakPoz(T(&array)[size]);
    
    // Eldönti hogy a megadott számot tartlmazza-e a tömb
     bool Tartalm(T(&array)[size], T element);
    
    // Megkeresi a legnagyobb értéket a tömbben
     T ArrMaxi(T(&array)[size]);
    
    // Megkeresi a legkisebb értéket a tömbben
     T ArrMini(T(&array)[size]);
    
    // Megkeresi a legnagyobb értéket a tömbben és visszaküldi a tömbbeli pozicióját
     int maxIndex(T(&array)[size]);
    
    // Megkeresi a legkisebb értéket a tömbben és visszaküldi a tömbbeli pozicióját
     int minIndex(T(&array)[size]);
    
    // Kiirja a tömb értékeit két határ között
     void printArr(T(&array)[size], T limit1, T limit2);
    
    // Visszatéríti a tömb utolsó elemét
     T getLastElement(T(&array)[size]);
    
    // Visszatéríti a tömb első elemét
     T getFirstElement(T(&array)[size]);
    
    // Visszatéríti a tömb páros elemeit
     T getEvenElements(T array[]);
    
    // Visszatéríti a tömb páratlan elemeit
     T getOddElements(T array[]);
    
    // Visszatéríti a tömb mindegyik n-edik elemét, k-tól kezdve
     void ArrElemNtoK(T (&array)[size1],T n,T k, T (&result)[size2]);
    
    // Visszatéríti egy adott elem megjelenéseinek számát
     int countOccurrencesOf(T(&array)[size],T element);
    
    // Kiszámolja a tömb elemeinek legnagyobb közös osztóját
     int ArrLnko(T(&array)[size]);
    
    // Kiszámolja a tömb elemeinek legkisebb közös többszörösét
     int ArrLkkt(T(&array)[size]);
    
    // Kiszámolja a tömb elemeinek szorzatát
     double ArrProd(T(&array)[size]);
    
    // Kiszámolja a tömb elemeinek számtani közepét
     double ArrMean(T(&array)[size]);
    
    // Kiszámolja a tömb elemeinek mértani közepét
     double ArrMedian(T(&array)[size]);
    
    // Kiszámolja a tömb varianciáját
     double ArrVariance(T(&array)[size]);
    
    // Kiszámolja a tömb elemeinek standard deviációját
     double ArrStdDev(T array[]);
    
    // Kiszámolja a tömb abszolút értékeinek összegét (L1 norma) 
     double ArrNorm1(T(&array)[size]);
    
    // Kiszámolja a tömb Absolút értékeinek az összegének a gyökét (L2 norma)
     double ArrNorm2(T(&array)[size]);
    
    // Kiszámolja a tömb P-edik normáját
     double ArrNormP(T(&array)[size],double p);
    
    // Kiszámolja a tömb Magnitudját (L2 norma)
     double ArrMag(T array[]);
    
    // A tömb minden elemét egy adott értékre cseréli
     void fillArrWith(T(&array)[size],T element);
    
    // A tömb minden elemét megszorozza egy értékkel
     void ArrMultiScal(T(&array)[size],T scalar);
    
    // Összeszoroz két tömböt
     void ArrMultiVec(T(&array1)[size],T(&array2)[size]);
    
    // Eloszt minden elemet egy adott értékkel
     void ArrDivScal(T(&array)[size],T scalar);
    
    // Eloszt egymással két tömböt
     void ArrDivVec(T(&array1)[size],T(&array2)[size]);
    
    // A tömb minden eleméhez hozzáad egy értéket
     void ArrAddScal(T(&array)[size],T value);
    
    // Összead két tömböt
     void ArrAddVec(T(&array1)[size],T(&array2)[size]);
    
    // Kivon egy értéket a tömb minden eleméből
     void ArrSubScal(T(&array)[size],T value);
    
    // Kivon két tömböt egymásból
     void ArrSubVec(T(&array1)[size],T(&array2)[size]);
    
    // Kiszámolja a tömb minden elemének az abszolút értékét
     void ArrAbs(T(&array)[size]);
    
    // Kiszámolja a tömb minden elemének a négyzetét
     void ArrPow(T(&array)[size]);
    
    // Kiszámolja a tömb minden elemének a gyökét
     void ArrSqrt(T(&array)[size]);
    
    // Rendezi a tömb elemeit növekvő sorrenbe (Quicksort módszer)
     void ArrSort(T &array, int low, int high);
    
    // Megdorditja a tömböt
     void ArrRev(T &array);
    
    // Átméretezi a tömb elemeit a két határérték szerint <bold>???</bold>
     double ArrScale(T(&array)[size],double lowerLimit,double upperLimit);
    
    // Létrehoz egy tömböt ami a tömb elem szerinti különbségeket fogja tartalmazni
     T ArrDiff(T(&array)[size]);
    
    // Létrehoz egy új tömböt és feltölti nullásokkal
     T ArrZeros(T(&array)[size]);
    
    // Létrehoz egy új tömböt és feltölti egyesekkel
     T ArrOnes(T(&array)[size]);
    
    // Létrehoz egy tömböt aminek értékei két határérték között lesznek, megadott lépésszámmal
     T ArrRange(int limit1,int limit2,int step);
    
    // Létrehoz egy tömböt aminek az értékei nullától egy felső határig lesznek
     T ArrRMax(int maxValue);
    
    // Létrehoz egy új tömböt amiben a kisebb határértéktől a nagyobbig fogja tárolni a számokat
     T ArrRMinMax(int minValue,int maxValue);
    
    // Kiszámolja a skaláris szorzatát két tömbnek
     double ArrDProd(T(&array1)[size],T(&array2)[size]);
    
    // Kiszámolja az Euklidészi távolságot két tömb között
     double ArrEucliDist(T(&array1)[size],T(&array2)[size]);
    
    // Kiszámolja a koszinusz hasonlóságot két tömb között
     double ArrCosSim(T(&array1)[size],T(&array2)[size]);
    
    // Kiszámolja a koszinusz távolságot két tömb között
     double ArrCosDist(T(&array1)[size],T(&array2)[size]);
    
    // Két különböző hosszúságú tömb elemeinek összevonása egy harmadik tömbbe
     T ArrMerge(T(&array1)[size1],T(&array2)[size2]);

<span style="font-size: 25px;"><u>Mátrixok:<u></span>

<span style="font-size: 25px;"><u>Sor:<u></span>

<span style="font-size: 25px;"><u>Verem:<u></span>

<span style="font-size: 25px;"><u>Listák:<u></span>

<span style="font-size: 25px;"><u>Gráfok:<u></span>

<span style="font-size: 25px;"><u>Fák:<u></span>