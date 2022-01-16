#ifndef BUKAS_PROOF_FUNCS
#define BUKAS_PROOF_FUNCS
#define INF 99999
#include <bits/stdc++.h>
using namespace std;

//ANCHOR: //** UTIL FUNCTIONS */

template <typename T>
    void univ_swap(T& a, T& b) {
        T c(a); a = b; b = c;
    }

void DFSUtil(int u, int adj[100][100], bool visited[], int n) {
        visited[u] = true;
        for (int i=1; i <= n; i++)
            if (visited[adj[u][i]] == false)
                DFSUtil(adj[u][i], adj, visited, n);
    }

void azonos(int a,int b, int komp[100], int n) {
    int c = komp[b];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(komp[i] == c) {
                komp[i] = komp[a];
            }
        }
    }
}

void BSort(int ell[100][4], int m) {
    bool x = false;
    int lp = 0;
    do {
        x = false;
        for (int i = 1; i < m - lp; i++) {
            if (ell[i][3] > ell[i + 1][3]) {
                x = true;
                univ_swap(ell[i][1], ell[i + 1][1]);
                univ_swap(ell[i][2], ell[i + 1][2]);
                univ_swap(ell[i][3], ell[i + 1][3]);
            }
            lp++;
        }
    } while (x == true);
}

bool ellenoriz(int a,int b, int komp[100]) {
    return komp[a] == komp[b];
}

int minKey(int key[100], bool mstSet[100], int n) {
    int min = INT_MAX, min_index;

    for (int v = 1; v <= n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMST(int parent[100], int boole[100][100], int n, int ell[100][3]) {
    for (int i = 2; i <= n; i++) {
        ell[i - 1][1] = parent[i];
        ell[i - 1][2] = i;
        ell[i - 1][3] = boole[i][parent[i]];
    }
}

int miniDist(int dist[100], bool visited[100], int n) {
    int mini = INT_MAX, min_index;

    for (int v = 1; v <= n; v++) {
        if (visited[v] == false && dist[v] <= mini) {
            mini = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void pP(int parent[100], int j) {
    if (parent[j] == -1)
        return;

    pP(parent, parent[j]);

    cout << " -> " << j;
}

bool iS(int v, int boole[100][100], int path[100], int pos, int n) {
    if (boole[path[pos - 1]][v] == 0)
        return false;

    for (int i = 1; i <= pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hmCU(int boole[100][100], int path[100], int pos, int n) {
    if (pos == n+1) {
        if (boole[path[pos - 1]][path[1]] == 1)
            return true;
        else
            return false;
    }

    for (int v = 2; v <= n; v++) {
        if (iS(v, boole, path, pos, n)) {
            path[pos] = v;
            if (hmCU(boole, path, pos + 1, n) == true) {
                return true;
            }

            path[pos] = -1;
        }
    }
    return false;
}

bool isCircU(int adj[100][100],int n,int v, bool visited[], int parent) {
    visited[v] = true;
    for(int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if(isCircU(adj, n, i, visited, v))
                return true;
        } else if (i != parent) {
            return true;
        }
    }
    return false;
}

void ut(int v, bool visited[100], int n) {
    visited[v] = true;
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            ut(i, visited, n);
        }
    }
}

//** UTIL FUNCTIONS */

//ANCHOR: //** BASIC SHIT !!! */
template<typename T>
    T lnko(T a, T b) {
        if (a == 0)
            return b;
        return lnko(b % a, a);
    }

template<typename T>
    bool isOdd(T x) {
    if(x % 2 != 0) {
        return true;
    }
    return false;
    }

template<typename T>
    T SumToN(int n) {
        return n * (n+1) / 2;
    }

bool ifPrim(int n) {
    if (n == 1 || n == 0) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int Fact(int n) {
    int result[1000] = {0};
    if (n >= 0) {
        result[0] = 1;
        for (int i = 1; i <= n; ++i) {
            result[i] = i * result[i - 1];
        }
        return result[n];
    }
}

int nVk(int n, int k) {
    int P = 1;

    for (int i = 0; i < k; i++)
        P *= (n-i);

    return P;
}

int nCk(int n, int k) {
    int C[k + 1];
    memset(C, 0, sizeof(C));

    C[0] = 1;

    for (int i = 1; i <= n; i++) {   
        for (int j = min(i, k); j > 0; j--)
            C[j] = C[j] + C[j - 1];
    }
    return C[k];
}

int fib(int n) {
    int a = 0, b = 1, c, i;
    if (n == 0)
        return a;
    for (i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

//** BASIC SHIT !!! */

//ANCHOR: //** TEMPLATES ARRAY !!! */

template <typename T, int size>
    void ArrRead(T(&array)[size], istream& is) {
        T tmp;
		for(int i = 0; i < size; i++){
			is>>tmp;
			array[i] = tmp;
		}
    }

template<typename T, int size>
    int ArrSize(T(&)[size]){
        return size;
    }

template <typename T, int size>
    T ArrAvg(T(&array)[size]) {
        T sum = 0.0;
        for(int i = 0; i < ArrSize(array); i++) {
            sum += array[i];
        }
        return (sum/ArrSize(array));
    }

template <typename T, int size>
    T ArrSum(T(&array)[size]) {
        T sum = 0.0;
        for (int i = 0; i < ArrSize(array); i++) {
            sum += array[i];
        }
        return sum;
    }

template <typename T, int size>
    static void ArrSort(T(&array)[size]) {
        for(int i = 0; i < size; i++) {
            for(int j = i + 1; j < size; j++) {
                if(array[i] > array[j]) {
                    univ_swap(array[i], array[j]);
                }
            }
        }
    }

template <typename T, int size>
    static bool ArrEmpty(T(&array)[size]) {
        return (ArrSize(array) == 0);
    }
    
template <typename T, int size>
    static bool Csak0(T(&array)[size]) {
        if (!ArrEmpty(array)) {
            for (int i = 0; i < ArrSize(array); i++) {
                if (array[i] != 0) {
                    return false;
                }
            }
            return true;
        } else {
            throw invalid_argument("A tomb ures");
        }
    }

template <typename T, int size>
    static bool CsakPoz(T(&array)[size]) {
        if (!ArrEmpty(array)) {
            for (int i = 0; i < ArrSize(array); i++) {
                if (array[i] < 0) {
                    return false;
                }
            }

            return true;
        } else {
            throw invalid_argument("A tomb ures");
        }
    }

template <typename T, int size>
    static bool CsakNeg(T(&array)[size]) {
        if (!ArrEmpty(array)) {
            for (int i = 0; i < ArrSize(array); i++) {
                if (array[i] > 0) {
                    return false;
                }
            }
            return true;
        } else {
            throw invalid_argument("A tomb ures");
        }
    }

template <typename T, int size>
    static bool Tartalm(T(&array)[size], T element) {
        for (int i = 0; i < ArrSize(array); i++) {
            if (array[i] == element) {
                return true;
            }
        }
        return false;
    }

template <typename T, int size>
    static T ArrMaxi(T(&array)[size]) {
        if (!ArrEmpty(array)) {
            T maxVal = array[0];
            for (int i = 1;i < ArrSize(array);i++) {
                if (array[i] > maxVal) {
                    maxVal = array[i];
                }
            }
            return maxVal;
        } else {
            throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>
    static T ArrMini(T(&array)[size]) {
        if (!ArrEmpty(array)) {
        T minVal = array[0];
        for (int i = 1;i < ArrSize(array);i++) {
            if (array[i] < minVal) {
                minVal = array[i];
            }
        }
        return minVal;
        } else {
        throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>
    int Partition(T(&array)[size], int start, int end) {
        
        int pivot = end;
        int j = start;
        for(int i = start;i < end; ++i){
            if(array[i] < array[pivot]){
                swap(array[i],array[j]);
                ++j;
            }
        }
        swap(array[j],array[pivot]);
        return j;
        
    }

template <typename T, int size>
    void ArrQSort(T(&array)[size], int start, int end ) {

        if(start < end){
            int p = Partition(array,start,end);
            ArrQSort(array,start,p-1);
            ArrQSort(array,p+1,end);
        }
        
    }

template<typename T, int size>
    int ArrBinChr(T(&array)[size], int n, T x) {
        int start = 0;
        int end = n-1;
        while(start<=end) {
            int mid = (start+end)/2;
            if(array[mid]==x)	
                return mid;
            else if(array[mid]<x)	
                start = mid + 1;
            else	
                end = mid - 1;
        }
        return -1;
    }

template <typename T, int size>
    static int maxIndex(T(&array)[size]) {
        if (!ArrEmpty(array)) {
        T maxVal = array[0];
        int maxIndex = 0;
        for (int i = 1;i < ArrSize(array);i++) {
            if (array[i] > maxVal) {
                maxVal = array[i];
                maxIndex = i;
            }
        }
        return maxIndex;
        } else {
            throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>
    static int minIndex(T(&array)[size]) {
        if (!ArrEmpty(array)) {
        T minVal = array[0];
        int minIndex = 0;

        for (int i = 1;i < ArrSize(array);i++) {
            if (array[i] < minVal) {
                minVal = array[i];
                minIndex = i;
            }
        }
        return minIndex;
        } else {
            throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>
    static void ArrPrint(T(&array)[size], T limit1, T limit2) {
        for (int i = limit1; i < limit2;i++) {
            cout << array[i] << " ";
        }
    }

template <typename T, int size>
    static T getLastElement(T(&array)[size]) {
        if (ArrSize(array) > 0) {
            return array[ArrSize(array)-1];
        } else {
        throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>  
    static T getFirstElement(T(&array)[size]) {
        if (ArrSize(array) > 0) {
            return array[0];
        } else {
        throw invalid_argument("Hiba");
        }
    }

template <typename T, int size1, int size2>
    static T getEvenElements(T (&array)[size1], T (&result)[size2]) {
        return ArrElemNtoK(array, 2, 0, result);
    }

template <typename T, int size1, int size2>
    static T getOddElements(T (&array)[size1], T (&result)[size2]) {
        return ArrElemNtoK(array, 2, 1, result);
    }

template <typename T, int size1, int size2>
    //???        
    static void ArrElemNtoK(T (&array)[size1],T n,T k, T (&result)[size2]) {
        if ((n >= ArrSize(array)) || (n >= ArrSize(array))) {
            throw invalid_argument("Hibas parameterek");
        } else {
        int i = k;
        
        while (i < ArrSize(array)) {
            result[i] = array[i];
            i += n;
        }
        
        }
    }

template <typename T, int size>
    static int countOccurrencesOf(T(&array)[size],T element) {
            int count = 0;
        
            for (int i = 0;i < ArrSize(array);i++) {
            if (array[i] == element) {
                count++;
            }
        }
        
        return count;
    }

template <typename T, int size>
    static int ArrLnko(T(&array)[size]) {
        int result = array[0];
        for (int i = 1; i < size; i++) {
            result = lnko(array[i], result);

            if(result == 1) {
                return 1;
            }
        }
        return result;
    }

template <typename T, int size>
    static int ArrLkkt(T(&array)[size]) {
        int result = array[0];

        for (int i = 1; i < size; i++)
            result = (((array[i] * result)) /
                (lnko(array[i], result)));

        return result;
    }

template <typename T, int size>
    static double ArrProd(T(&array)[size]) {
            if (!ArrEmpty(array)) {
            double prod = (double) array[0];
            
            for (int i = 1;i < ArrSize(array);i++) {
                prod *= ((double) array[i]);
            }
            
            return prod;
            } else {
            throw invalid_argument("Hiba");
            }
    }
    
template <typename T, int size>
    static double ArrMean(T(&array)[size]) {
        if (!ArrEmpty(array)) {
        double L = (double) ArrSize(array);
        double sumVal = (double) ArrSum(array);
        return sumVal / L;
        } else {
            throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>
    //?
    static double ArrMedian(T(&array)[size]) {
        if (!ArrEmpty(array)) {
        double median;
        size_t L = ArrSize(array);
        
        ArrSort(array);
        
        if (L % 2 == 0) {
            median = ((double)(array[L / 2 - 1] + array[L / 2])) / 2.0;
        } else {
            median = (double) array[(L-1) / 2];
        }
        return median;
        } else {
        throw invalid_argument("Hiba");
        }
    }
    
template <typename T, int size>
    static double ArrVariance(T(&array)[size]) {
        if (!ArrEmpty(array)) {
        double mu = ArrMean(array);
        double sumVal = 0.0;
        for (int i = 0;i < ArrSize(array);i++) {
            double diff = array[i]-mu;
            sumVal += diff*diff;
        }
        return sumVal / ((double)ArrSize(array));
        } else {
        throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>
    static double ArrStdDev(T(&array)[size]) {//& StandardDeviations
        if (!ArrEmpty(array)) {
            double var = ArrVariance(array);

            if (var > 0) {
                return sqrt(var);
            } else {
                return 0.0;
            }

        } else {
            throw invalid_argument("Hiba");
        }
    }
    
template <typename T, int size>
    static double ArrNorm1(T(&array)[size]) {
        double sumVal = 0.0;
    
        for (int i = 0;i < ArrSize(array);i++) {
            if (array[i] > 0) {
                sumVal += (double) array[i];
            } else {
                sumVal += (double) (-1*array[i]);
            }
        }
    
        return sumVal;
    }
    
template <typename T, int size>
    static double ArrNorm2(T(&array)[size]) {
        double sumVal = 0.0;
    
        for (int i = 0;i < ArrSize(array);i++) {
        sumVal += (double) (array[i]*array[i]);
        }

    return sqrt(sumVal);
    }
    
template <typename T, int size>
    static double ArrNormP(T(&array)[size],double p) {
        double sumVal = 0.0;
    
        for (int i = 0;i < ArrSize(array);i++) {
            double val;
        
            if (array[i] > 0) {
                val = (double) array[i];
            } else {
                val = (double) (-1*array[i]);
            }
        
            sumVal += pow(val,p);
        }

        return pow(sumVal,1.0/p);
    }
    
template <typename T, int size>
    static double ArrMag(T(&array)[size]) {
        return ArrNorm2(array);
    }

template <typename T, int size>
    static void fillArrWith(T(&array)[size],T element) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] = element;
        }
    }
    
template <typename T, int size>
    static void ArrMultiScal(T(&array)[size],T scalar) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] *= scalar;
        }
    }
    
template <typename T, int size>
    static void ArrMultiVec(T(&array1)[size],T(&array2)[size]) {
        if (ArrSize(array1) == ArrSize(array2)) {
            for (int i = 0;i < ArrSize(array1);i++) {
                array1[i] *= array2[i];
            }

        } else {
            throw invalid_argument("Hiba");
        }
    }
    
template <typename T, int size>
    static void ArrDivScal(T(&array)[size],T scalar) {
        if(scalar != 0) {
            for (int i = 0;i < ArrSize(array);i++) {
                array[i] /= scalar;
            }
        } else {
            throw invalid_argument("Zeroval valo osztas");
        }
    }
    
template <typename T, int size>
    static void ArrDivVec(T(&array1)[size],T(&array2)[size]) {
        if(ArrSize(array1) == ArrSize(array2))  {
            if (!contains(array2, 0)) {
                for (int i = 0;i < ArrSize(array1);i++) {
                    array1[i] /= array2[i];
                }
            } else {
                throw invalid_argument("Hiba");
            }
        } else {
        throw invalid_argument("A tomb hosszai nem egyenloek");
        }
    }
    
template <typename T, int size>
    static void ArrAddScal(T(&array)[size],T value) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] += value;
        }
    }
    
template <typename T, int size>
    static void ArrAddVec(T(&array1)[size],T(&array2)[size]) {
        if (ArrSize(array1) == ArrSize(array2)) {
            for (int i = 0;i < ArrSize(array1);i++) {
            array1[i] += array2[i];
            }
        } else {
            throw invalid_argument( "A tomb hosszai nem egyeznek");
        }
    }
    
template <typename T, int size>
    static void ArrSubScal(T(&array)[size],T value) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] -= value;
        }
    }
    
template <typename T, int size>
    static void ArrSubVec(T(&array1)[size],T(&array2)[size]) {
        if (ArrSize(array1) == ArrSize(array2)) {
            for (int i = 0;i < ArrSize(array1);i++) {
                array1[i] -= array2[i];
            }
        } else {
            throw invalid_argument( "A tomb hosszai nem egyeznek");
        }
    }
    
template <typename T, int size>
    static void ArrAbs(T(&array)[size]) {
        for (int i = 0;i < ArrSize(array);i++) {
            if ((array[i] < 0) || (array[i] == -0.0)) {
                array[i] *= -1;
            }
        }
    }

template <typename T, int size>
    static void ArrPow(T(&array)[size]) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] = array[i]*array[i];
        }
    }
    
template <typename T, int size>
    static void ArrSqrt(T(&array)[size]) {
        if (CsakPoz(array)) {
            for (int i = 0;i < ArrSize(array);i++) {
                array[i] = (T) sqrt((double)array[i]);
            }
        } else {
            throw invalid_argument( "Negativ szam gyoke");
        }
    }

template <typename T, int size>
    static void ArrRev(T(&array)[size]) {
        for (int low = 0, high = size - 1; low < high; low++, high--) {
            univ_swap(array[low], array[high]);
        }
    }

template <typename T, int size>
    //* Scales the values in a vector to take values in the range [lowerLimit, upperLimit]
    //ANCHOR //!!!
    static double ArrScale(T(&array)[size],double lowerLimit,double upperLimit) {
        T result[];
    
        double minVal = (double) ArrMini(array);
        double maxVal = (double) ArrMaxi(array);
        double outputRange = upperLimit - lowerLimit;
        double inputRange = maxVal - minVal;
    
        for (int i = 0;i < ArrSize(array);i++) {
            double value = (double) array[i];
            double scaledValue = ((value - minVal) * outputRange) / inputRange + lowerLimit;
            result[i] = scaledValue;
        }
    
        return result;
    }
    
template <typename T, int size>
    //???
    static T ArrDiff(T(&array)[size]) {
        T result[];
    
        for (int i = 1;i < ArrSize(array);i++) {
            result[i] = array[i]-array[i-1];
        }
    
        return result;
    }

template <typename T, int size>
    static void ArrZeros(T (&result)[size]) {
        if (ArrSize(result) >= 0) {        
            for (int i = 0;i < size;i++) {
                result[i] = 0;
            }
        } else {
            throw invalid_argument("Negativ hossz");
        }
    }
    
template <typename T, int size>
    static T ArrOnes(T (&result)[size]) {
        if (ArrSize(result) >= 0) {
            for (int i = 0;i < ArrSize(result);i++) {
                result[i] = 1;
            }
        } else {
            throw invalid_argument("Negativ hossz");
        }
    }

template <typename T, int size>
    static void ArrRange(T limit1, T limit2, int step, T (&result)[size]) {
        if (step > 0) {
            for (T i = limit1;i < limit2;i += step) {
                result[i] = i;
            }
        } else if (step < 0) {
            for (T i = limit1;i > limit2;i += step) {
                result[i] = i;
            }
        } else {
            throw invalid_argument( "Nem lehet nulla lepesszam");
        }
    }

template <typename T>
    static T ArrRMax(T maxValue) {
        return ArrRange(0, maxValue, 1);
    }

template <typename T>
    static T ArrRMinMax(T minValue,T maxValue) {
        return ArrRange(minValue, maxValue, 1);
    }

template <typename T, int size>
    static double ArrDProd(T(&array1)[size],T(&array2)[size]) {
        if (ArrSize(array1) == ArrSize(array2)) {
            double sumVal = 0.0;
        
            for (int i = 0;i < ArrSize(array1);i++) {
                sumVal += (array1[i]*array2[i]);
            }
        
            return sumVal;
        } else {
            throw invalid_argument("A tombok hosszai nem egyeznek");
        }
    }
    
template <typename T, int size>
    static double ArrEucliDist(T(&array1)[size],T(&array2)[size]) {
        if (ArrSize(array1) == ArrSize(array2)) {
            double sumVal = 0.0;
        
            for (int i = 0;i < ArrSize(array1);i++) {
                double diff = (double) (array1[i] - array2[i]);
                sumVal += (diff*diff);
            }
        
            if (sumVal > 0) {
                return sqrt(sumVal);
            } else {
                return 0.0;
            }
        } else {
            throw invalid_argument("A tombok hosszai nem egyenloek");
        }
    }
    
template <typename T, int size>
    static double ArrCosSim(T(&array1)[size],T(&array2)[size]) {
        return ArrDProd(array1, array2) / (ArrMag(array1) * ArrMag(array2));
    }

template <typename T, int size>
    static double ArrCosDist(T(&array1)[size],T(&array2)[size]) {
        return 1.0 - ArrCosSim(array1, array2);
    }

template <typename T, int size1, int size2>
    static T ArrMerge(T(&array1)[size1],T(&array2)[size2]) {
        T array3[];
        ArrSort(array1);
        ArrSort(array2);

        int i = 0, j = 0, k = 0;  
        while (i < size1 && j < size2) { 
            if (array1[i] <= array2[j]) {  
                array3[k] = array1[i];  
                i += 1;  
                k += 1;  
            } else {  
                array3[k] = array2[j];
                j += 1;  
                k += 1;  
            }  
        }  
        while (i < size1) {
            array3[k] = array1[i];  
            i += 1;  
            k += 1;  
        }  
        while (j < size2) {
            array3[k] = array2[j];  
            j += 1;  
            k += 1;  
        }

        return array3;
    }

//** TEMPLATES ARRAY !!! */

//ANCHOR: //** TEMPLATES MATRIX !!! */

template <typename T, size_t row, size_t col>
    // 0 - sorok, 1 - oszlopok
    static int MatSize(T(&matrix)[row][col], int x) {
        if(x==0) {
            return row;
        }else if(x==1){
            return col;
        }else{
            
            throw invalid_argument("in Matrix::size()");
        }
    }

template <typename T, size_t row, size_t col>
    static T MatGet(T(&matrix)[row][col], T r, T c) {
        if(0 <= r && r < row && 0 <= c && c < col){
		    return matrix[r][c];
	    } else {
		throw invalid_argument("Meghaladott meret");
	    }
    }

template <typename T, size_t row, size_t col>
    static T MatSet(T(&matrix)[row][col], T r, T c, T val) {
        T ret = 0;
	    if(r < row && c < col){
		    matrix[r][c] = val;
	    } else {
		    ret = 1;
		    throw invalid_argument("Meghaladott meret");
	    }
	    return ret;
    }

template <typename T, size_t row, size_t col>
    static void MatPrint(T(&matrix)[row][col]) {
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                cout << matrix[i][j] << " ";
            }
            cout<<endl;
        }
	cout<<endl;
    }

template <typename T, size_t row, size_t col>
    void MatRead(T(&matrix)[row][col], istream& is){
	T tmp;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			is>>tmp;
			matrix[i][j] = tmp;
		}
	}
}

template <typename T, size_t row, size_t col>
    vector<vector<T>> MatToVec(T(&matrix)[row][col]) {
	    return matrix;
    }

template <typename T, size_t row, size_t col>
    void MatAppendRowTo(T(&matrix)[row][col], T(&array1)[col], int loc) {
        if(loc < row){
            for(int i = 0; i < col; i++){
                matrix[loc][i] = array1[i];
            }
        } else {
            throw invalid_argument("Meghaladott meret");
        }
    }

template <typename T, size_t row, size_t col>
    void MatAppendColTo(T(&matrix)[row][col], T(&array1)[row], int loc) {
        if(loc < col){
            for(int i = 0; i < row; i++){
                matrix[i][loc] = array1[i];
            }
        } else {
            throw invalid_argument("Meghaladott meret");
        }
    }

template <typename T, size_t row, size_t col>
    void MatSwapRow(T(&matrix)[row][col], int loc1, int loc2) {
        if(loc1 < row && loc2 < row){
            for(int i = 0; i < col; i++){
                T tmp = matrix[loc1][i];
                matrix[loc1][i] = matrix[loc2][i];
                matrix[loc2][i] = tmp;
            }
        } else {
            throw invalid_argument("Meghaladott meret");
        }
    }

template <typename T, size_t row, size_t col>
    void MatSwapCol(T(&matrix)[row][col], int loc1, int loc2) {
        if(loc1 < col && loc2 < col){
            for(int i = 0; i < row; i++){
                T tmp = matrix[i][loc1];
                matrix[i][loc1] = matrix[i][loc2];
                matrix[i][loc2] = tmp;
            }
        } else {
            throw invalid_argument("Meghaladott meret");
        }
    }

template <typename T, size_t row, size_t col>
    void RemoveRow(T(&matrix)[row][col], int loc) {
        if(loc < row){
            for(int i = loc; i < row-1; i++){
                for(int j = 0; j < col; j++){
                    matrix[i][j] = matrix[i+1][j];
                }
            }
        } else {
            throw invalid_argument("Meghaladott meret");
        }
    }

template <typename T, size_t row, size_t col>
    void RemoveCol(T(&matrix)[row][col], int loc) {
        if(loc < col){
            for(int i = loc; i < col-1; i++){
                for(int j = 0; j < row; j++){
                    matrix[j][i] = matrix[j][i+1];
                }
            }
        } else {
            throw invalid_argument("Meghaladott meret");
        }
    }

template <typename T, size_t row, size_t col>
    int MatTr(T(&matrix)[row][col]) {
        int trace = 0;
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(i == j)
                    trace += matrix[i][j];
            }
        }
        return trace;
    }

template <typename T, size_t row, size_t col>
    void MatPrimDiag(T(&matrix)[row][col], T(&array)[col]) {
        int cnt = 0;
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(i == j) {
                    array[cnt] = matrix[i][j];
                    cnt++;
                }
            }
        }
    }

template <typename T, size_t row, size_t col>
    void MatSecDiag(T(&matrix)[row][col], T(&array)[col]) {
        int cnt = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if ((i + j) == (row - 1)) {
                    array[cnt] = matrix[i][j];
                    cnt++;
                }
            }
        }
    }

template <typename T, size_t row, size_t col>
    float MatNorm(T(&matrix)[row][col]) {
        float normal = 0.0;
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                normal += matrix[i][j];
            }
        }
        normal=sqrt(normal);

        return normal;
    }

template <typename T, size_t row, size_t col>
    int MatDet(T(&matrix)[row][col]) {
        int num1, num2, det = 1, index, total = 1, n = row;

        int temp[n + 1];

        for (int i = 0; i < n; i++) {
            index = i;

            while (matrix[index][i] == 0 && index < n) {
                index++;
            }

            if (index == n) {
                continue;
            }

            if (index != i) {
                for (int j = 0; j < n; j++) {
                    swap(matrix[index][j], matrix[i][j]);
                }
                det = det * pow(-1, index - i);
            }

            for (int j = 0; j < n; j++) {
                temp[j] = matrix[i][j];
            }

            for (int j = i + 1; j < n; j++) {
                num1 = temp[i];
                num2 = matrix[j][i];

                for (int k = 0; k < n; k++) {
                    matrix[j][k] = (num1 * matrix[j][k]) - (num2 * temp[k]);
                }
                total = total * num1;
            }
        }

        for (int i = 0; i < n; i++) {
            det = det * matrix[i][i];
        }
        return (det / total);
    }

template <typename T, size_t row, size_t col>
    int MatRank(T(&matrix)[row][col]) {
	int rank = col;

	for (int R = 0; R < rank; R++) {
	    if (matrix[R][R]) {
	        for (int C = 0; C < R; C++) {
	            if (C != R) {
	                double mult = (double) matrix[C][R] /
	                    matrix[R][R];

	                for (int i = 0; i < rank; i++)
	                    matrix[C][i] -= mult * matrix[R][i];
	            }
	        }
	    } else {
	        bool reduce = true;
	        for (int i = R + 1; i < row; i++) {
	            if (matrix[i][R]) {
	                for (int j = 0; j < rank; j++) {
                        int temp = matrix[R][j];
                        matrix[R][j] = matrix[i][j];
                        matrix[i][j] = temp;
                    }
	                reduce = false;
	                break;
	            }
	        }

	        if(reduce) {
	            rank--;
	            for (int i = 0; i < row; i++)
	                matrix[i][R] = matrix[i][rank];
	        }

	        R--;
	    }
	}
	return rank;
}

template <typename T, size_t row, size_t col>
    void MatSumRow(T(&matrix)[row][col], int loc) {
        int sum = 0;
        for(int j = 0; j < col; j++) {
            sum += matrix[loc][j];
        }
    }

template <typename T, size_t row, size_t col>
    void MatSumCol(T(&matrix)[row][col], int loc) {
        int sum = 0;
        for(int i = 0; i < row; i++) {
            sum += matrix[i][loc];
        }
    }

template <typename T, size_t row1, size_t col1,size_t row2, size_t col2>
    void MatProdMat(T(&matrix1)[row1][col1], T(&matrix2)[row2][col2], T(&matrix3)[row1][col2]) {
        if(col1 == row2) {

            for (int i = 0; i < row1; i++) {
                for (int j = 0; j < col2; j++) {
                    matrix3[i][j] = 0;

                    for (int k = 0; k < row2; k++) {
                        matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
                    }
                }
            }
        } else {
            throw invalid_argument("A matrixok nem szorozhatok");
        }
    }

template <typename T, size_t row, size_t col>
    void MatProdConst(T(&matrix)[row][col], T cons) {
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                matrix[i][j] = matrix[i][j] * cons; 
    }

template <typename T, size_t row, size_t col>
    void MatAddConst(T(&matrix)[row][col], T cons) {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                matrix[i][j] += cons;
            }
        }
    }

template <typename T, size_t row, size_t col>
    void MatAddMat(T(&matrix1)[row][col], T(&matrix2)[row][col], T(&matrix3)[row][col]) {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
    }

template <typename T, size_t row, size_t col>
    void MatNthPow(T(&matrix)[row][col], int N, T(&matrix2)[row][col]) {
        int sum = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                for (int k = 0; k < row; k++) //not sure if its row or col
                    sum += matrix[i][k] * matrix[k][j];
                matrix2[i][j] = sum;
                sum = 0;
            }
        }
    }

template <typename T, size_t row, size_t col>
    void MatPPD(T(&matrix)[row][col], int c) { //print_under_prim_diag, 0 - under, 1 - above
        if(c == 0) {
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(i > j) {
                        cout << matrix[i][j] << " ";
                    } else {
                        cout << "0 ";
                    }
                }
                cout << endl;
            }
        } else if(c == 1) {
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(j > i) {
                        cout << matrix[i][j] << " ";
                    } else {
                        cout << "0 ";
                    }
                }
                cout << endl;
            }
        } else {
            throw invalid_argument("Nem megfelelo parameter");
        }
    }

template <typename T, size_t row, size_t col>
    void MatPSD(T(&matrix)[row][col], int c) {  //print_under_sec_diag, 0 - under, 1 - above
        if(c == 0) {
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(row - i - 1 < j) {
                        cout << matrix[i][j] << " ";
                    } else {
                        cout << "0 ";
                    }
                }
                cout << endl;
            }
        } else if(c == 1) {
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(j <= row - i - 1) {
                        cout << matrix[i][j] << " ";
                    } else {
                        cout << "0 ";
                    }
                }
                cout << endl;
            }
        } else {
            throw invalid_argument("Nem megfelelo parameter");
        }
    }

template <typename T, size_t row, size_t col>
    void MatPSpir(T(&matrix)[row][col]) {
        int i, k = 0, l = 0, n = col, m = row;
        /* k - sor első indexe
            m - sor utolsó indexe
            l - oszlop első indexe
            n - oszlop utolsó indexe
            i - iterator
        */

        while (k < m && l < n) {
            for (i = l; i < n; ++i) {
                cout << matrix[k][i] << " ";
            }
            k++;

            for (i = k; i < m; ++i) {
                cout << matrix[i][n - 1] << " ";
            }
            n--;

            if (k < m) {
                for (i = n - 1; i >= l; --i) {
                    cout << matrix[m - 1][i] << " ";
                }
                m--;
            }
            if (l < n) {
                for (i = m - 1; i >= k; --i) {
                    cout << matrix[i][l] << " ";
                }
                l++;
            }
        }
    }

template <typename T, size_t row, size_t col>
    void MatSubConst(T(&matrix)[row][col], T cons) {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                matrix[i][j] -= cons;
            }
        }
    }

template <typename T, size_t row, size_t col>
    void MatSubMat(T(&matrix1)[row][col], T(&matrix2)[row][col], T(&matrix3)[row][col]) {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
            }
        }
    }

template <typename T, size_t row, size_t col>
    void MatDivConst(T(&matrix)[row][col], T cons) {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                matrix[i][j] = matrix[i][j] / cons;
            }
        }
    }

template <typename T, size_t row, size_t col>
    void MatDivMat(T(&matrix1)[row][col], T(&matrix2)[row][col], T(&matrix3)[row][col]) {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                matrix3[i][j] = matrix1[i][j] / matrix2[i][j];
            }
        }
    }

//** TEMPLATES MATRIX !!! */

//ANCHOR: //** TEMPLATES GRAPH !!! */

//~ Matrixok atalakitasai

//! (main: siz = 0)
void boolToIncid(int boole[100][100], int n, int inc[100][100], int &siz) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            if(boole[i][j] == 1) {
                siz++;
            }
        }
    }
    siz = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            if(boole[i][j] == 1) {
                siz++;
                inc[i][siz] = 1;
                inc[j][siz] = 1;
            }
        }
    }
}

//!(main: m = 0)
void boolToEll(int boole[100][100], int n, int ell[100][4], int &m) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            if(boole[i][j] != 0) {
                m++;
                ell[m][1] = j;
                ell[m][2] = i;
            }
        }
    }
}

void boolToAdj(int boole[100][100], int n, int adj[100][100]) {
    int k;
    for(int i = 1; i <= n; i++) {
        k = 0;
        for(int j = 1; j <= n; j++) {
            if(boole[i][j] == 1) {
                k++;
                adj[i][k] = j;
            }
            adj[i][0] = k;
        }
    }
}

//! (main: num = 0)
void ellToAdj(int ell[100][3], int n, int adj[100][100], int &num) {
    int t[100];
    for(int i = 1; i <= 2*n; i++) {
        t[i] = false;
    }
    for(int i = 1; i <= n + 1; i++) {
        adj[i][0] = 0;
    }
    for(int i = 1; i <= n; i++) {
        t[ell[i][1]] = true;
        t[ell[i][2]] = true;
        adj[ell[i][1]][0]++;
        adj[ell[i][2]][0]++;
        adj[ell[i][1]][adj[ell[i][1]][0]] = ell[i][2];
        adj[ell[i][2]][adj[ell[i][2]][0]] = ell[i][1];
    }
    while(t[num+1] == true) {
        num++;
    }
}

void incidToEll(int inc[100][100],int n,int m, int ell[100][3]) {
    bool ok;
    for(int i = 1; i <= m; i++) {
        ok = true;
        for(int j = 1; i < n; j++) {
            if(inc[j][i] == 1) {
                if(ok) {
                    ell[i][1] = j;
                    ok = !ok;
                } else {
                    ell[i][2] = j;
                }
            }
        }
    }
}

void adjToBool(int adj[100][100], int n, int boole[100][100]) {
    //Le van nullazva a boole
    for(int i = 1; i <= adj[i][0]; i++) {
        for(int j = 1; j <= adj[i][0]; j++) {
            boole[i][adj[i][j]] = 1;
        }
    }
}

void ellToBool(int ell[100][3], int n, int boole[100][100]) {
    //Le van nullazva a boole
    for(int i = 1; i <= n; i++) {
        boole[ell[i][1]][ell[i][2]] = 1;
        boole[ell[i][2]][ell[i][1]] = 1;
    }
}

void EllToIncid(int ell[100][3], int m, int &n, int inc[100][100]) {
    n = 0;
    int maxi = 1;
    int cnt = 0;
    for(int i = 1; i <= m; i++) {
        maxi = ell[i][2];
        if(maxi > n) {
            n = maxi;
        }
        cnt++;
        inc[ell[i][1]][cnt] = 1;
        inc[ell[i][2]][cnt] = 1;
    }
}

//^CHECK
void incidToBool(int inc[100][100], int n, int m, int boole[100][100]) {
}

//^CHECK
void incidToAdj(int inc[100][100], int n, int m, int adj[100][100]) {
    
}

//^CHECK
void adjToIncid(int adj[100][100], int n, int inc[100][100]) {

}

void adjToEll(int adj[100][100], int n, int ell[100][3]) {
    int k = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(adj[i][j] != 0) {
                ell[k][1] = i;
                ell[k][2] = adj[i][j];
                k++;
            }
        }
    }
}

//~ Bejarasok

void grBFS(int boole[30][30],int n, int cs) {
    int first, last, pont;
    int queue[50];
    bool arr[50];

    for(int i = 1; i <= n; i++) {
        arr[i] = false;
    }
    arr[cs] = true;
    first = last = 1;
    queue[first] = cs;
    cout<<cs << " ";
    while(first <= last) {
        pont = queue[first];
        first++;

        for(int i = 1; i <= n; i++) {
            if(!arr[i] && boole[pont][i] != 0) {
                last++;
                queue[last] = i;
                arr[i] = true;
                cout<<i << " ";
            }
        }
    }
}

void grDFS(int boole[30][30],int n, int cs) {
    int stack[30] = {0};
    int visited[30] = {false};
    int top = 1;
    stack[top] = cs;
    cout << cs << " ";
    visited[stack[top]] = 1;
    bool ok = false;

    while(top != 0) {
        ok = false;
        for(int i = 1; i <= n && ok == false; i++) {
            if(boole[stack[top]][i] == 1 && visited[i] == false) {
                top++;
                stack[top] = i;
                visited[i] = true;
                cout<< stack[top] << " ";
                ok = true;
            }
        }
        if(ok==false) {
            top--;
        }
    }
}

//~ Fak

int grCntTrees(int adj[100][100], int n) {
    bool visited[n];
    memset(visited,false,sizeof(visited));
    int res = 0;
    for (int u=1; u <= n; u++) {
        if (visited[u] == false) {
            DFSUtil(u, adj, visited, n);
            res++;
        }
    }
    return res;
}

//~ Feszitofa alkotas

//&Kruskal
void grKruskal(int boole[100][100], int n, int ell[100][4], int m, int ell2[100][3]) {
    int komp[100], k, i;
    boolToEll(boole,n,ell,m);
    BSort(ell, m);
    k=1, i = 1;
    while(k <= n - 1) {
        if(ellenoriz(ell[i][1], ell[i][2], komp) == false) {
            azonos(ell[i][1], ell[i][2], komp, n);
            ell2[k][1] = ell[i][1];
            ell2[k][2] = ell[i][2];
            ell2[k][3] = ell[i][3];
            k++;
        }
        i++;
    }
}

//&Prim
void grPrim(int boole[100][100], int n, int ell[100][3]) {
    int parent[100];
    int key[100];
    bool mstSet[100];

    for (int i = 1; i <= n; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[1] = 0;
    parent[1] = -1;

    for (int count = 1; count <= n - 1; count++) {
        int u = minKey(key, mstSet, n);

        mstSet[u] = true;

        for (int v = 1; v <= n; v++)
            if (boole[u][v] && mstSet[v] == false && boole[u][v] < key[v])
                parent[v] = u, key[v] = boole[u][v];
    }
    printMST(parent, boole, n, ell);
}

//~ Legrovidebb utak

//& Dijkstra
void grDijkstra(int boole[100][100], int src, int n) {
    int dist[100];
    bool visited[100];
    int parent[100];

    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for(int c = 1; c <= n - 1; c++) {
        int u = miniDist(dist, visited, n);
        visited[u] = true;

        for (int v = 1; v <= n; v++) {
            if (!visited[v] && boole[u][v] && dist[u] + boole[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + boole[u][v];
            }
        }
    }
    cout << "Csomopont\t Tavolsag\tUt" << endl;
    for (int i = 1; i <= n; i++) {
        cout << src << " -> " << i << "\t\t " << dist[i] << "\t\t" << src;
        pP(parent, i);
        cout << endl;
    }
}

//& Floyd Warshall
void grFloydWarshall(int graph[100][100], int n) {
    //!!! 99 et vagy valami nagy szamot kell megadni INFnek, a matrix kezdeti erteke 99 kiveve a foatlon
    int i, j, k;

    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (graph[i][j] > (graph[i][k] + graph[k][j])
                    && (graph[k][j] != INF
                        && graph[i][k] != INF))
                    graph[i][j] = graph[i][k] + graph[k][j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] == 99)
                cout << "INF" << "     ";
            else
                cout << graph[i][j] << "     ";
        }
        cout << endl;
    }
}

//~ Spec

void grRevDGr(int boole[100][100], int n, int boole2[100][100]) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(boole[i][j] == 1) {
                boole2[j][i] = 1;
            }
        }
    }
}

bool grExistPath(int ell[100][4],int n, int u, int v) {
    bool bol[n][n];
    memset(bol, false, sizeof(bol));

    for (int i = 1; i <= n; i++)
        bol[ell[i][1]][ell[i][2]] = true;

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                bol[i][j] = bol[i][j] || bol[i][k] && bol[k][j];
            }
        }
    }

    if (u >= n || v >= n) {
        return false;
    }

    if (bol[u][v])
        return true;
    return false;
}

bool grCheckIsolated(int boole[100][100], int n) {
    for (int i = 1; i <= n; i++) {
        int count = 0;
        for (int j = 1; j <= n; j++) {
            if (boole[i][j])
                count++;
        }
        if (count == 0)
            return true;
    }
    return false;
}

void grPathMat(int boole[100][100], int n) {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(boole[i][j] == 0) {
                    boole[i][j] = boole[i][k] * boole[k][j];
                }
            }
        }
    }
}

void grDelVert(int adj[100][100], int n, int cs) {
    //!!! Adj lista

    adj[cs][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= adj[i][0]; j++) {
            if(adj[i][j] == cs) {
                for(int k = j; k <= (adj[i][0] - 1); k++) {
                    adj[i][k] = adj[i][k+1];
                }
                adj[i][0]--;
            }
        }
    }
}

int grCntDeg(int boole[100][100], int n, int num) {
    int cnt = 0;
    for(int j = 1; j <= n; j++) {
        if(boole[num][j] != 0) {
            cnt++;
        }
    }

    return cnt;
}

//? i = 0 ?????
void grInOutDeg(int adj[100][100], int n,int in[100],int out[100]) {
    for(int i=0;i<n;i++) {
        out[i] = ArrSize(adj[i]);
            for(int j=0;j<ArrSize(adj[i]);j++)
                in[adj[i][j]]++;
    }
}

//& Check Hamilton
bool grIsHamiltonian(int boole[100][100], int n) {
    int path[100];
    for (int i = 1; i <= n; i++) {
        path[i] = -1;
    }

    path[1] = 1;
    if (hmCU(boole, path, 2, n) == false ) {
        cout << "\nNem Hamiltoni kor";
        return false;
    }

    cout <<"Van Hamiltoni kore: \n";
    for (int i = 1; i <= n; i++) {
        cout << path[i] << " ";
    }
    cout << path[1] << " ";
    cout << endl;

    return true;
}

//& Check Eulerian
//!!! main(cnt = 0 //euler graf hossza)
//^ bool
void grIsEulerian(int boole[100][100],int n, int start, int path[100], int &cnt) {
    for(int i = 1 ; i <= n ; i ++)
        if(boole[start][i] == 1) {
            boole[start][i] = boole[i][start] = 0;
            grIsEulerian(boole, n, i, path, cnt);
        }
    path[++cnt] = start;
}

bool grIsBipartite(int boole[100][100], int n, int src) {
    int visited[n];
    for (int i = 1; i <= n; ++i) {
        visited[i] = -1;
    }
    visited[src] = 1; 

    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if(boole[u][u] == 1) {
            return false;
        }

        for (int v = 1; v <= n; ++v) {
            if (boole[u][v] && visited[v] == -1) {
                visited[v] = 1 - visited[u];
                q.push(v);

            } else if (boole[u][v] && visited[v] == visited[u])
                return false;
        }
    }

    return true;
}

bool GrIsComplete(int boole[100][100], int n) {
    int inc[100][100], siz = 0;
    boolToIncid(boole,n, inc, siz);
    if(siz == n*(n-1)/2) {
        return true;
    } else {
        return false;
    }

}

//& Check Circle
bool grIsCyclic(int adj[100][100], int n) {
    bool visited[n];
    memset(visited,false,sizeof(visited));

    for (int u = 1; u <= n; u++) {
        if (visited[u] == true)
            if (isCircU(adj, n, u, visited, -1)) {
                return true;
            }
    }
    return false;
}

//& Check for strongly connected comps
bool grIsStrongConnect(int boole[100][100], int n) {
    int boole2[100][100];
    memset(boole2, false, sizeof(boole2));
    bool visited[n];
    memset(visited,false,sizeof(visited));

    ut(1, visited, n);

    for(int i = 1; i <= n; i++) {
        if(visited[i] == false) {
            return false;
        }
    }

    grRevDGr(boole, n, boole2);

    memset(visited,false,sizeof(visited));

    ut(1, visited, n);

    for(int i = 1; i <= n; i++) {
        if(visited[i] == false) {
            return false;
        }
    }

    return true;
}

void getCliques(int n, int boole[100][100]) {
    int e, u, bejar[20], lat[20], h = 1;
    for(int i = 1; i <= n; i++) {
        if(lat[i] == 0) {
            e = 1;
            u = 2;
            lat[i] = h;
            bejar[e] = i;
            while(e < u) {
                for(int j = 1; j <= n; j++) {
                    if((boole[bejar[e]][j]) == 1 && (lat[j] == 0)) {
                        bejar[u] = j;
                        lat[j] = h;
                        u++;
                    }
                }
                e++;
            }
            h++;
        }
    }

    for(int i = 1; i <= h-1; i++) {
        cout<<i << "th click: ";
        for(int j = 1; j <= n; j++) {
            if(lat[j] == i) {
                cout<<j<< " ";
            }
        }
        cout<<endl;
    }
}

//** TEMPLATES GRAPH !!! */

//ANCHOR: //** DOUBLY CIRCULAR LINKED LIST !!! */
typedef struct seg {
    int info;
    seg *kov;
    seg *elo;
    //!!! main.cpp template
    /*
    LIST *lista = new LIST;
    lista->head = NULL;
    */
} node;

typedef struct doubly_circular_linked {
    node *head;

    void besz_head(int x) {
        node *uj = new node;

        uj->info = x;

        uj->kov = (head);
        uj->elo = NULL;

        if ((head) != NULL)
            (head)->elo = uj;

        (head) = uj;
    }
    //!!! IDK WHAT IT DOES
    void besz_utan(node *elo_seg, int x) {
        if (elo_seg == NULL) {
            return;
        }
        node *uj = new node;

        uj->info = x;

        uj->kov = elo_seg->kov;

        elo_seg->kov = uj;

        uj->elo = elo_seg;

        if (uj->kov != NULL)
            uj->kov->elo = uj;
    }

    void besz_qutan(node *elo, int x) {
        if (elo == NULL) {
            return;
        }

        node *uj = new node;

        uj->info = x;

        uj->kov = elo->kov;

        elo->kov = uj;

        uj->elo = elo;

        if (uj->kov != NULL)
            uj->kov->elo = uj;
    }

    void besz_last(int x) {
        node *uj = new node;

        node *last = head;

        uj->info = x;

        uj->kov = NULL;

        if (head == NULL) {
            uj->elo = NULL;
            head = uj;
            return;
        }

        while (last->kov != NULL)
            last = last->kov;
        last->kov = uj;

        uj->elo = last;
        return;
    }

    void besz_pos(int x, int pos) {
        node *temp = new node, *s;
        temp->info = x;
        temp->kov = NULL;
        temp->elo = NULL;
        if (pos == 1) {
            temp->kov = head;
            head = temp;
            return;
        }
        node *temp2 = head;
        for (int i = 0; i < pos - 2; i++) {
            temp2 = temp2->kov;
        }
        temp->kov = temp2->kov;
        temp2->kov = temp;
    }

    void megforditas() {
        node *bal = head, *jobb = head;

        while (jobb->kov != NULL)
            jobb = jobb->kov;

        while (bal != jobb && bal->elo != jobb) {
            univ_swap(bal->info, jobb->info);

            bal = bal->kov;
            jobb = jobb->elo;
        }
    }

    void Kiirjobb() {
        node *iter = head;

        while (iter->kov != NULL) {
            cout << iter->info << "<==>";
            iter = iter->kov;
        }
        cout << iter->info << endl;
    }

    void Kiirbal() {
        node *last = head;

        while (last->kov != NULL) {
            last = last->kov;
        }
        while (last != head) {
            cout << last->info << "<==>";
            last = last->elo;
        }
        cout << last->info << endl;
    }

    void torles(node *del) {
        if (head == NULL || del == NULL)
            return;

        if (head == del)
            head = del->kov;

        if (del->kov != NULL)
            del->kov->elo = del->elo;

        if (del->elo != NULL)
            del->elo->kov = del->kov;
        free(del);
        return;
    }

    void torlpos(int n) {
        if (head == NULL || n <= 0)
            return;

        node *curr = head;

        for (int i = 1; curr != NULL && i < n; i++)
            curr = curr->kov;

        if (curr == NULL)
            return;

        torles(curr);
    }
} LIST;

//ANCHOR: //** STACK !!! */
typedef struct st {
    int data;
    st *first;

    //!!! main.cpp template
    /*
    STACK *stack = new STACK;
    stack_node *top = new stack_node;
    top->first = NULL;
    top->data = -1;
    */
} stack_node;

typedef struct stack_struct{
    stack_node *top;

    void push(int val) {
        stack_node *x = new stack_node;
        x->data = val;
        x->first = top;

        top = x;
    }

    int pop(int x) {
        if (top == NULL)
            return 0;
        else {
            x = top->data;
            top = top->first;
        }
    }

    int Top() {
        return top->data;
    }
} STACK;

//ANCHOR: //** QUEUE !!! */
typedef struct nd {
    int data;
    nd* next;

    //!!! main.cpp template
    /*
    QUEUE *queue = new QUEUE;
    queue_node *first = NULL;
    queue_node *last = NULL;
    */
} queue_node;

typedef struct queue_struct {
    queue_node *first;
    queue_node *last;

    bool isEmpty() {
        if (first == NULL) {
            return true;
        }
        return false;
    }

    void push(int ert) {
        queue_node *x = new queue_node;
        x->data = ert;
        x->next = NULL;
        if (isEmpty()) {
            first = last = x;
        }
        else {
            last->next = x;
            last = x;
        }
    }

    int front() {
        if (isEmpty()) {
            return -1;
        }
        else {
            return first->data;
        }
    }

    int pop() {
        int x;
        queue_node *p;
        if (isEmpty()) {
            return -1;
        }
        else {
            p = first;
            x = first->data;
            first = p->next;
            free(p);
            return x;
        }
    }

    void display() {
        queue_node *p;
        p = first;
        while (p != NULL) {
            cout << p->data << " ";
            p = p->next;
        }
    }
} QUEUE;

//ANCHOR: //** CHAR STRINGS !!! */

bool intIsPal(int n) {
    int temp = n, dig, rev = 0;
    do {
        dig = temp % 10;
        rev = (rev * 10) + dig;
        temp /= 10;
    } while(temp  != 0);

    if(n == rev) {
        return true;
    } else {
        return false;
    }
}
//!!!NEEDED FOR CHARISPAL
bool isPal(char str[], int s, int e) {
    if (s == e)
        return true;

    if (str[s] != str[e])
        return false;

    if (s < e + 1)
        return isPal(str, s + 1, e - 1);

    return true;
}
//!!!NEEDED FOR CHARISPAL

bool isVow(char ch) {
    ch = toupper(ch);
    return (ch == 'A' || ch == 'E' || ch == 'I' ||
            ch == 'O' || ch == 'U');
}

int charChrVow(char str[]) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
        if (isVow(str[i]))
            ++count;
    return count;
}

int charChrCons(char str[]) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
        if (isVow(str[i]) == false)
            ++count;
    return count;
}

bool charIsPal(char str[]) {
    int n = strlen(str);

    if (n == 0)
        return true;

    return isPal(str, 0, n - 1);
}

template <typename T, size_t row, size_t col>
    void sortCharMat(T(&matrix)[row][col]) {
        char temp[255];
        for(int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                if (strcmp(matrix[j - 1], matrix[j]) > 0) {
                    strcpy(temp, matrix[j - 1]);
                    strcpy(matrix[j - 1], matrix[j]);
                    strcpy(matrix[j], temp);
                }
            }
        }
    }

//** CHAR STRINGS !!! */

#endif