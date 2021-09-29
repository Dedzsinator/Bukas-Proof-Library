Bukás Proof könyvtár
====================

Egy könyvtár tartalmazza a 9-12-es anyag leghaszonsabb fügvényeit adatstruktúrákra bontva.

Használata
----------

A könyvtár a következő típusú változókat tud feldolgozni:

	int
	float	
	double
	long
    char

A könyvtár a következő adatstruktúrák hasznos fügvényeit tartlamazza: 

- Tömbök
- Mátrixok
- Listák (egyszeresen, kétszeresen láncolt)
- Karakterláncok
- Dinamikus Adatszerkezetek (Verem, Sor)
- Gráfok
- Bináris fák

A tömbök függvényeinek dokumentációja:

	// Kicserél két elemet egy tömbben
	void univ_swap(T& a, T& b);
	
	// Visszatéríti a megadott tömb méretét
	int Arrsize(T(&)[size]);
	
	// Visszatéríti a tömb elemeinek átlagát
	T ArrAvg(T(&array)[size]);
	
	// Visszatéríti a tömb elemeinek összegét
	T ArrSum(T(&array)[size]);

	// Eldönti hogy a tömb üres-e
	static bool ArrEmpty(T(&array)[size]);
	
	// Eldönti hogy a tömb csak nullást tartlmaz
	static bool Csak0(T(&array)[size]);

    // Eldönti hogy a tömb csak nullánál nagyobb számokat tartlmaz
    static bool CsakPoz(T(&array)[size]);

    // Eldönti hogy a tömb csak negatív számokat tartlmaz
    static bool CsakPoz(T(&array)[size]);

    // Eldönti hogy a megadott számot tartlmazza-e a tömb
    static bool Tartalm(T(&array)[size], T element);

    // Megkeresi a legnagyobb értéket a tömbben
	static T ArrMaxi(T(&array)[size]);

	// Megkeresi a legkisebb értéket a tömbben
	static T ArrMini(T(&array)[size]);

	// Megkeresi a legnagyobb értéket a tömbben és visszaküldi a tömbbeli pozicióját
	static int maxIndex(T(&array)[size]);

	// Megkeresi a legkisebb értéket a tömbben és visszaküldi a tömbbeli pozicióját
	static int minIndex(T(&array)[size]);

	// Kiirja a tömb értékeit két határ között
	static void printArr(T(&array)[size], T limit1, T limit2);

	// Visszatéríti a tömb utolsó elemét
	static T getLastElement(T(&array)[size]);
	
	// Visszatéríti a tömb első elemét
	static T getFirstElement(T(&array)[size]);

	// Visszatéríti a tömb páros elemeit
	static T getEvenElements(T array[]);

	// Visszatéríti a tömb páratlan elemeit
	static T getOddElements(T array[]);

	// Visszatéríti a tömb mindegyik n-edik elemét, k-tól kezdve
	static void ArrElemNtoK(T (&array)[size1],T n,T k, T (&result)[size2]);

	// Visszatéríti egy adott elem megjelenéseinek számát
	static int countOccurrencesOf(T(&array)[size],T element);

	// Kiszámolja a tömb elemeinek legnagyobb közös osztóját
	static int ArrLnko(T(&array)[size]);

	// Kiszámolja a tömb elemeinek legkisebb közös többszörösét
	static int ArrLkkt(T(&array)[size]);

	// Kiszámolja a tömb elemeinek szorzatát
	static double ArrProd(T(&array)[size]);

	// Kiszámolja a tömb elemeinek számtani közepét
	static double ArrMean(T(&array)[size]);

	// Kiszámolja a tömb elemeinek mértani közepét
	static double ArrMedian(T(&array)[size]);

	// Kiszámolja a tömb varianciáját
	static double ArrVariance(T(&array)[size]);

	// Kiszámolja a tömb elemeinek standard deviációját
	static double ArrStdDev(T array[]);

	// Kiszámolja a tömb abszolút értékeinek összegét (L1 norma) 
	static double ArrNorm1(T(&array)[size]);

	// Kiszámolja a tömb Absolút értékeinek az összegének a gyökét (L2 norma)
	static double ArrNorm2(T(&array)[size]);
	
	// Kiszámolja a tömb P-edik normáját
	static double ArrNormP(T(&array)[size],double p);

	// Kiszámolja a tömb Magnitudját (L2 norma)
	static double ArrMag(T array[]);

	// A tömb minden elemét egy adott értékre cseréli
	static void fillArrWith(T(&array)[size],T element);

	// A tömb minden elemét megszorozza egy értékkel
	static void ArrMultiScal(T(&array)[size],T scalar);

	// Összeszoroz két tömböt
	static void ArrMultiVec(T(&array1)[size],T(&array2)[size]);

	// Eloszt minden elemet egy adott értékkel
	static void ArrDivScal(T(&array)[size],T scalar);

	// Eloszt egymással két tömböt
	static void ArrDivVec(T(&array1)[size],T(&array2)[size]);

	// A tömb minden eleméhez hozzáad egy értéket
	static void ArrAddScal(T(&array)[size],T value);

	// Összead két tömböt
	static void ArrAddVec(T(&array1)[size],T(&array2)[size]);

	// Kivon egy értéket a tömb minden eleméből
	static void ArrSubScal(T(&array)[size],T value);

	// Kivon két tömböt egymásból
	static void ArrSubVec(T(&array1)[size],T(&array2)[size]);

	// Kiszámolja a tömb minden elemének az abszolút értékét
	static void ArrAbs(T(&array)[size]);

	// Kiszámolja a tömb minden elemének a négyzetét
	static void ArrPow(T(&array)[size]);

	// Kiszámolja a tömb minden elemének a gyökét
	static void ArrSqrt(T(&array)[size]);

	// Rendezi a tömb elemeit növekvő sorrenbe (Quicksort módszer)
	static void ArrSort(T &array, int low, int high);

	// Megdorditja a tömböt
	static void ArrRev(T &array);

	// Átméretezi a tömb elemeit a két határérték szerint <bold>???</bold>
	static double ArrScale(T(&array)[size],double lowerLimit,double upperLimit);

	// Létrehoz egy tömböt ami a tömb elem szerinti különbségeket fogja tartalmazni
	static T ArrDiff(T(&array)[size]);

	// Létrehoz egy új tömböt és feltölti nullásokkal
	static T ArrZeros(T(&array)[size]);

	// Létrehoz egy új tömböt és feltölti egyesekkel
	static T ArrOnes(T(&array)[size]);

	// Létrehoz egy tömböt aminek értékei két határérték között lesznek, megadott lépésszámmal
	static T ArrRange(int limit1,int limit2,int step);

	// Létrehoz egy tömböt aminek az értékei nullától egy felső határig lesznek
	static T ArrRMax(int maxValue);

	// Létrehoz egy új tömböt amiben a kisebb határértéktől a nagyobbig fogja tárolni a számokat
	static T ArrRMinMax(int minValue,int maxValue);

	// Kiszámolja a skaláris szorzatát két tömbnek
	static double ArrDProd(T(&array1)[size],T(&array2)[size]);

	// Kiszámolja az Euklidészi távolságot két tömb között
	static double ArrEucliDist(T(&array1)[size],T(&array2)[size]);

	// Kiszámolja a koszinusz hasonlóságot két tömb között
	static double ArrCosSim(T(&array1)[size],T(&array2)[size]);

	// Kiszámolja a koszinusz távolságot két tömb között
	static double ArrCosDist(T(&array1)[size],T(&array2)[size]);

	// Két különböző hosszúságú tömb elemeinek összevonása egy harmadik tömbbe
	static T ArrMerge(T(&array1)[size1],T(&array2)[size2]);


Függvények Listái
-----------------

The following are some example functions that the toolkit includes:

**Simple info about a vector:**

- sum()
- max()
- min()
- maxIndex()
- minIndex()

**Simple statistics:**

- mean()
- median()
- standardDeviation()
- variance()

**Working with scalars or other vectors:**

- multiply()
- divide()
- add()
- subtract()

**Distance and Similarity:**

- euclideanDistance()
- cosineSimilarity()
- cosineDistance()

**Other Handy Things:**

- getEvenElements()
- getOddElements()
- printVector()
- isAllPositiveOrZero()
- contains()
- reverse()

and lots of other functions of these types.


Verziók
---------------

**v1.3 - 27/9/2014**

- Dokumentáció
- Pár függvény (Összefésülés, Lnko, Lkkt)

**v1.2 - 25/9/2021**

- Tömbök függvényeinek elkezdése

**v1.1 - 23/9/2021**

- Kiegészítés + Mátrix alapok

**v1.0 - 20/9/2021**

- Az első alap függvények