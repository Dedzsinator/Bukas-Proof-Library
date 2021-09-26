#ifndef BUKAS_PROOF_FUNCS
#define BUKAS_PROOF_FUNCS
#include <bits/stdc++.h>
#define MAX_MATRIX_SIZE 1000
using namespace std;

//**TEMPLATES !!! */

template <typename T>
    void univ_swap(T& a, T& b) {
        T c(a); a = b; b = c;
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

// ANCHOR //!!!
template <typename T, int size>
    static T maxi(T(&array)[size]) {
        if (!isEmpty(array)) {
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
    /** Finds the maximum value in a vector.
     * @param v the vector from which to find the maximum value
     * @returns the maximum value in the vector v
     */
// ANCHOR //!!!
template <typename T, int size>
    static T mini(T(&array)[size]) {
        if (!isEmpty(array)) {
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
    /** Finds the minimum value in a vector.
     * @param v the vector from which to find the minimum value
     * @returns the minimum value in the vector v
     */

// ANCHOR //!!!
template <typename T, int size>
    static int maxIndex(T(&array)[size]) {
        if (!isEmpty(array)) {
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
    /** Finds the index of the maximum value in a vector.
     * @param v the vector from which to find the max index
     * @returns the index of the maximum value in the vector v
     */
// ANCHORT //!!!
template <typename T, int size>
    static int minIndex(T(&array)[size]) {
        if (!isEmpty(array)) {
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
    /** Finds the index of the minimum value in a vector.
     * @param v the vector from which to find the min index
     * @returns the index of the minimum value in the vector v
     */

template <typename T, int size>
    static void printVector(T(&array)[size]) {
        for (int i = 0; i < ArrSize(array);i++) {
            cout << array[i] << endl;
        }
    }

template <typename T, int size>
/** @Returns the last element of the vector */
    static T getLastElement(T(&array)[size]) {
        if (ArrSize(array) > 0) {
            return array[ArrSize(array)-1];
        } else {
        throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>  
    /** @Returns the first element of the vector */
    static T getFirstElement(T(&array)[size]) {
        if (ArrSize(array) > 0) {
            return array[0];
        } else {
        throw invalid_argument("Hiba");
        }
    }
    
template <typename T>
    /** @Returns a vector containing only the even elements of an input vector */
    static T getEvenElements(T array[]) {
        return getEveryNthElementStartingFromK(array, 2, 0);
    }

template <typename T>
    /** @Returns a vector containing only the odd elements of an input vector */
    static T getOddElements(T array[]) {
        return getEveryNthElementStartingFromK(array, 2, 1);
    }

//ANCHOR //!!!
template <typename T, int size>    
    /** Given an input vector, @returns a vector containing every nth element, starting from k  */    
    static T getEveryNthElementStartingFromK(T(&array)[size],int n,int k) {
        if ((n >= ArrSize(array)) || (array >= ArrSize(array))) {
        throw invalid_argument("Hibas parameterek");
        } else {
        T result[size]; //T result;
        int i = k;
        
        while (i < ArrSize(array)) {
            result[i] = array[i];
            i += n;
        }
        
        return result;
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
    /** Counts the number of occurrences of an element in a given vector.
     * @param v the vector to examine
     * @param element the element to count
     * @returns the number of instances of element in the vector v
     */
    
template <typename T, int size>
    static double ArrProd(T(&array)[size]) {
            if (!isEmpty(array)) {
            double prod = (double) array[0];
            
            for (int i = 1;i < ArrSize(array);i++) {
                prod *= ((double) array[i]);
            }
            
            return prod;
            } else {
            throw invalid_argument("Hiba");
            }
    }
    /** Calculates the product of all elements in the vector.
     * NB. this returns a double as it anticipates a potentially large value
     *
     * @param v the vector to calculate the product for
     * @returns the product of the vector v
     */
    
template <typename T, int size>
    /** Calculates the arithmetic mean of the elements in a vector
     * @param v the vector from which to calculate the arithmetic mean
     * @returns the arithmetic mean of the vector v
     */
    static double ArrMean(T(&array)[size]) {
        if (!isEmpty(array)) {
        double L = (double) ArrSize(array);
        double sumVal = (double) ArrSum(array);
        return sumVal / L;
        } else {
            throw invalid_argument("Hiba");
        }
    }

template <typename T, int size>
    /** Calculates the median of the elements in a vector
     * @param v the vector from which to calculate the median
     * @returns the median of the vector v
     */
    ///ANCHOR //?
    static double ArrMedian(T(&array)[size]) {
        if (!isEmpty(array)) {
        double median;
        size_t L = ArrSize(array);
        
        ArrSort(array, 0, L-1);
        
        if (L  % 2 == 0) {
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
    /** Calculates the variance of the elements in a vector
     * @param v the vector from which to calculate the variance
     * @returns the variance of the vector v
     */
    static double ArrVariance(T(&array)[size]) {
        if (!isEmpty(array)) {
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

template <typename T>
    /** Calculates the standard deviation of the elements in a vector
     * @param v the vector from which to calculate the standard deviation
     * @returns the standard deviation of the vector v
     */
    static double ArrStdDev(T array[]) {//& StandardDeviations
        if (!isEmpty(array)) {
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
    /** Calculates the L1-norm of a vector.
     * @param v the vector from which to calculate the norm
     * @returns the L1-norm of the vector
     */
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
    /** Calculates the L2-norm of a vector.
     * @param v the vector from which to calculate the norm
     * @returns the L2-norm of the vector
     */
    static double ArrNorm2(T(&array)[size]) {
        double sumVal = 0.0;
    
        for (int i = 0;i < ArrSize(array);i++) {
        sumVal += (double) (array[i]*array[i]);
        }

    return sqrt(sumVal);
    }
    
template <typename T, int size>
    /** Calculates the p-norm of a vector.
     * @param v the vector from which to calculate the norm
     * @param p the exponent to use in the calculate of the norm
     * @returns the p-norm of the vector
     */
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
    
template <typename T>
    /** Calculates the magnitude (L2-norm) of a vector 
     * @param v the vector from which to calculate the norm
     * @returns the vector magnitude
     */
    static double ArrMag(T array[]) {
        return ArrNorm2(array);
    }

template <typename T, int size>
    /** Sets every element to a specified value
     * @param v the vector to fill with values
     * @param element the value to set each index in the vector to
     */
    //ANCHOR //!!!
    static void fillVectorWith(T(&array)[size],T element) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] = element;
        }
    }
    
template <typename T, int size>
    /** Multiply every element in a vector by a scalar.
     * @param v the vector to multiply
     * @param scalar the scalar to multiply the vector by
     */

    //ANCHOR //?
    static void ArrMultiScal(T(&array)[size],T scalar) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] *= scalar;
        }
    }
    
template <typename T, int size>
    /** Multiply one vector by another
     * @param array1 the first vector (to be multiplied in place)
     * @param array2 the second vector
     */
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
    /** Divide every element in a vector by a scalar.
     * @param v the vector to divide
     * @param scalar the scalar to divide the vector by
     */
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
    /** Divide one vector by another
     * @param v1 the first vector (to be divided in place)
     * @param v2 the second vector
     */
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
    /** Add a value to every element in a vector.
     * @param v the vector to which the value will be added
     * @param value the value to be added to each element of the vector
     */
    static void ArrAddScal(T(&array)[size],T value) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] += value;
        }
    }
    
template <typename T, int size>
    /** Add one vector to another
     * @param array1 the first vector (to be added to in place)
     * @param array2 the second vector
     */
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
    /** Subtract a value from every element in a vector.
     * @param v the vector from which the value will be subtracted
     * @param value the value to be subtracted from each element of the vector
     */
    static void ArrSubScal(T(&array)[size],T value) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] -= value;
        }
    }
    
template <typename T, int size>
    /** Subtract one vector from another
     * @param v1 the first vector (to be subtracted from in place)
     * @param v2 the second vector
     */
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
    /** Calculate the absolute value for each element of a vector.
     * @param v the vector to calculate the absolute value on
     */
    static void ArrAbs(T(&array)[size]) {
        for (int i = 0;i < ArrSize(array);i++) {
            if ((array[i] < 0) || (array[i] == -0.0)) {
                array[i] *= -1;
            }
        }
    }

template <typename T, int size>
    /** Calculate the square of each element of a vector.
     * @param v the vector to calculate the square of
     */
    static void ArrPow(T(&array)[size]) {
        for (int i = 0;i < ArrSize(array);i++) {
            array[i] = array[i]*array[i];
        }
    }
    
template <typename T, int size>
    /** Calculate the square root of each element of a vector.
     * @param v the vector to calculate the square root of
     */
    //ANCHOR //?
    static void ArrSqrt(T(&array)[size]) {
        if (CsakPoz(array)) {
            for (int i = 0;i < ArrSize(array);i++) {
                array[i] = (T) sqrt((double)array[i]);
            }
        } else {
            throw invalid_argument( "Negativ szam gyoke");
        }
    }
    
template <typename T>
    /** Sorts a vector */
    //ANCHOR //?
    static void ArrSort(T &array, int low, int high) {
        if (low < high) {
            int pivot = array[high];
            int i = (low - 1);

            for (int j = low; j <= high - 1; j++) {
                if (array[j] < pivot) {
                    i++;
                    int temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
            int temp = array[i + 1];
            array[i + 1] = array[high];
            array[high] = temp;
            int pi = i + 1;

            ArrSort(array, low, pi - 1);
            ArrSort(array, pi + 1, high);
        }
    }

template <typename T>
    /** Reverses a vector */
    //ANCHOR //?
    static void reverse(T &array) {
        reverse(array.begin(), array.end());
    }

template <typename T, int size>
    /** Scales the values in a vector to take values in the range [lowerLimit, upperLimit]
     * @param v the vector to scale
     * @param lowerLimit the lower limit of the scaled vector
     * @param upperLimit the uppoer limit of the scaled vector
     * @returns a double precision vector containing the scaled vector
     */
    //ANCHOR //!!!
    static double ArrScale(T(&array)[size],double lowerLimit,double upperLimit) {
        T result[];
    
        double minVal = (double) min(array);
        double maxVal = (double) max(array);
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
    /** Calculate the element-wise difference for a vector */
    //ANCHOR //!!!
    static T ArrDiff(T(&array)[size]) {
        T result[];
    
        for (int i = 1;i < ArrSize(array);i++) {
            result[i] = array[i]-array[i-1];
        }
    
        return result;
    }

template <typename T, int size>
    /** Create a new vector of zeros of length N */
    //ANCHOR //!!!
    static T ArrZeros(T(&array)[size]) {
        if (ArrSize(array) >= 0) {
            T result[];
        
            for (int i = 0;i < ArrSize(array);i++) {
                result[i] = 0;
            }
        
        return result;
        } else {
            throw invalid_argument("Negativ hossz");
        }
    }
    
template <typename T, int size>
    /** Create a new vector of ones of length N */
    //ANCHOR //!!!
    static T ArrOnes(T(&array)[size]) {
        if (ArrSize(array) >= 0) {
            T result[];
        
            for (int i = 0;i < ArrSize(array);i++) {
                result[i] = 1;
            }
        
            return result;
        } else {
            throw invalid_argument("Negativ hossz");
        }
    }

template <typename T>
    /** Create a new vector with values in the range [limit1,limit2], with specified increments.
     * @param limit1 the first limit
     * @param limit2 the second limit
     * @param step the increment to use
     * @returns a new vector containing values in the range [limit1,limit2], with specified incremements.
    */
    //ANCHOR //?
    static T ArrRange(int limit1,int limit2,int step) {
        T result[];
    
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
    
        return result;
    }

template <typename T>
    /** Create a new vector with values increasing from 0->(maxValue-1).
     * @param maxValue the upper limit of the range
     * @returns a new vector containing values in the range [0,maxValue)
    */
    static T ArrRMax(int maxValue) {
        return ArrRange(0, maxValue, 1);
    }

template <typename T>
    /** Create a new vector with values increasing from minValue->(maxValue-1).
     * @param minValue the lower limit of the range
     * @param maxValue the upper limit of the range
     * @returns a new vector containing values in the range [minValue,maxValue)
    */
    static T ArrRMinMax(int minValue,int maxValue) {
        return ArrRange(minValue, maxValue, 1);
    }

template <typename T, int size>
    /** Calculates the dot product between two vectors.
     * @param v1 the first vector
     * @param v2 the second vector
     * @returns the dot product of the two vectors
     */
    ///ANCHOR //?
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
    /** Calculates the Euclidean distance between two vectors.
     * @param v1 the first vector
     * @param v2 the second vector
     * @returns the Euclidean distance between the two vectors
     */
    //ANCHOR //?
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
    /** Calculates the Cosine similarity between two vectors.
     * @param v1 the first vector
     * @param v2 the second vector
     * @returns the Cosine similarity between the two vectors
     */
    //ANCHOR //?
    static double ArrCosSim(T(&array1)[size],T(&array2)[size]) {
        return ArrDProd(array1, array2) / (ArrMag(array1) * ArrMag(array2));
    }

template <typename T, int size>
    /** Calculates the Cosine distance between two vectors.
     * @param v1 the first vector
     * @param v2 the second vector
     * @returns the Cosine distance between the two vectors
     */
    //ANCHOR //?
    static double ArrCosDist(T(&array1)[size],T(&array2)[size]) {
        return 1.0 - ArrCosSim(array1, array2);
    }

//**TEMPLATES !!! */


bool isOdd(int x) {
    if(x % 2 != 0) {
        return true;
    }
    return false;
}

long long int SumToN(int n) {
    return n * (n+1) / 2;
}

int lnko(int a, int b) {
    if (a == 0)
        return b;
    return lnko(b % a, a);
}

int lkkt(int a, int b) {
    return (a * b) / lnko(a, b);
}

void inArr(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
}

void outArr(int array[], int size) {
    for(int i = 0; i < size; i++) {
        cout <<array[i];
    }
    cout <<endl;
}

void inMat(int matrix[][MAX_MATRIX_SIZE], int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            cin >> matrix[i][j];
        }
    }
}

void outMat(int matrix[][MAX_MATRIX_SIZE], int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            cin >> matrix[i][j];
        }
    }
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

/*int sizeofArr(int arr[]) {
    return &arr + 1 - arr;
}*/

int binarySearch(int array[], int left, int right, int x) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (array[mid] == x)
            return mid;

        if (array[mid] > x)
            return binarySearch(array, left, mid - 1, x);

        return binarySearch(array, mid + 1, right, x);
    }

    return -1;
}

//!!!NEEDED FOR QUICKSORT
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
//!!!NEEDED FOR QUICKSORT

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void mergeArrs() {

}

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

typedef struct doubly_circular_linked{
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

    bool ok() {
        if (first == NULL) {
            return true;
        }
        return false;
    }

    void push(int ert) {
        queue_node *x = new queue_node;
        x->data = ert;
        x->next = NULL;
        if (ok()) {
            first = last = x;
        }
        else {
            last->next = x;
            last = x;
        }
    }

    int pop() {
        int x;
        queue_node *p;
        if (ok()) {
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

int charCVow(char str[]) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
        if (isVow(str[i]))
            ++count;
    return count;
}

int charCCons(char str[]) {
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

void sortCharMat(char str[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int n) {
    char temp[255];
    for(int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (strcmp(str[j - 1], str[j]) > 0) {
                strcpy(temp, str[j - 1]);
                strcpy(str[j - 1], str[j]);
                strcpy(str[j], temp);
            }
        }
    }
}

void MatrixPrimDiag(int mat[][MAX_MATRIX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                cout << mat[i][j] << ", ";
        }
    }
    cout << endl;
}

void MatrixSecDiag(int mat[][MAX_MATRIX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i + j) == (n - 1))
                cout << mat[i][j] << ", ";
        }
    }
    cout << endl;
}

void MatrixSpiralPrint(int a[][MAX_MATRIX_SIZE], int m, int n) {
    int i, k = 0, l = 0;

    /* k - sor első indexe
        m - sor utolsó indexe
        l - oszlop első indexe
        n - oszlop utolsó indexe
        i - iterator
    */

    while (k < m && l < n) {
        for (i = l; i < n; ++i) {
            cout << a[k][i] << " ";
        }
        k++;

        for (i = k; i < m; ++i) {
            cout << a[i][n - 1] << " ";
        }
        n--;

        if (k < m) {
            for (i = n - 1; i >= l; --i) {
                cout << a[m - 1][i] << " ";
            }
            m--;
        }
        if (l < n) {
            for (i = m - 1; i >= k; --i) {
                cout << a[i][l] << " ";
            }
            l++;
        }
    }
}

int Fact(int n) {
    if (n > 1)
        return n * Fact(n - 1);
    else
        return 1;
}

int nVk(int n, int k) {
    return Fact(n) / Fact(n - k);
}

int nCk(int n, int k) {
    return Fact(n) / (Fact(k) * Fact(n - k));
}

int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}

#endif