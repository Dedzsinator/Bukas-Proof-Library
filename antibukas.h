#ifndef BUKAS_PROOF_FUNCS
#define BUKAS_PROOF_FUNCS
#include <bits/stdc++.h>
#define MAX_MATRIX_SIZE 1000
using namespace std;

template<typename T>
    int lnko(T a, T b) {
        if (a == 0)
            return b;
        return lnko(b % a, a);
    }

//** TEMPLATES ARRAY !!! */

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
    static void printArr(T(&array)[size], T limit1, T limit2) {
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

/*  
template <typename T, int size1, int size2>
    static T getEvenElements(T (&array)[size1], T (&result)[size2]) {
        return ArrElemNtoK(array, 2, 0, result);
    }

template <typename T, int size1, int size2>
    static T getOddElements(T (&array)[size1], T (&result)[size2]) {
        return ArrElemNtoK(array, 2, 1, result);
    }
*/

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

template <typename T>
    static double ArrStdDev(T array[]) {//& StandardDeviations
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
    
template <typename T>
    static double ArrMag(T array[]) {
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

//** TEMPLATES MATRIX !!! */

template<typename T, size_t row, size_t col>
class Matrix {
public:
	//^ CONSTRUCTORS ^//

	Matrix();

	//& Initialize with row and column
	Matrix(row, col);

    //& Copy constructor
	Matrix(const Matrix&);

    /*
	//& Initialize with a vector
	Matrix(const std::vector<double>&);
	//& Initialize with vector of vector
	Matrix(const std::vector<std::vector<double> >&);
    */


	//^ Destructor ^//
	~Matrix();

	//? COMMON METHODS ?//

	int size(int)const;

	double get(row row, col col)const;

	int set(row row, col col, T value);

	void print();

	void read(istream&);

	vector<vector<double>> toVector();

	//? SCIENTIFIC COMPUTATION ?//
	
	// row and column selecting 
	Matrix getRow(int)const;
	Matrix getRow(const std::vector<int>&);
	Matrix getColumn(int)const;
	Matrix getColumn(const std::vector<int>&);
	
	void setRow(int, const Matrix&);
	void setCol(int, const Matrix&);
	void setRow(int, const std::vector<double>&);
	void setCol(int, const std::vector<double>&);


	/*
		special slicing
	*/
	Matrix getDiagonal()const;
	Matrix getUpper()const;
	Matrix getLower()const;

	/*
		Add a new row.
		Input: A vector of the same length as other rows in the matrix.
	*/
	void appendRow(const std::vector<double>&);
	void appendCol(const std::vector<double>&);
	// general version of append
	void appendRow(const Matrix&);
	void appendCol(const Matrix&);

	// swap two row
	void swapRow(int, int);

	/*
		Remove a row/column
		Input: The row/column index of the row/column to remove.
		Danger: This operation disarranges the matrix order.
		
		: fix it to do stable removal
	*/
	void removeRow(int);
	void removeCol(int);

	// Splitting 
	// horizontal split
	vector<Matrix> hsplit(const vector<int>&);
	vector<Matrix> hsplit();
	// vertical split
    vector<Matrix> vsplit(const vector<int>&);
	vector<Matrix> vsplit();

	// sum along rows or columns (0 or 1)
	Matrix sum(int)const;
	// sum up all elements
	double sum()const;

	// Similar for product
	Matrix product(int);
	double product();

	// max/min element
	Matrix max(int)const;
	Matrix min(int)const;
	Matrix mean(int)const;
	Matrix variance(int)const;
	
	// sorting the matrix by row or column
	void sort(int);
	Matrix sort(int)const;

	//	transpose to make a new matrix
	Matrix transpose()const;

	// cofactor matrix
	Matrix cofactor();

	// adjoint/adjugate matrix
	Matrix adjoint();

	// reverse to make a new matrix
	Matrix inverse();

	// elementary row operation
	Matrix elemRowOp();

	// turn into diagonal matrix by elementary row operation
	Matrix diagonalize();

	// matrix rank
	int rank();

	// det
	double determinant();

	// trace
	double trace();

	///////////////	Overloaded Operators  ////////////////////////
	
	// Equal
	bool operator==(const Matrix&);
	// Not equal
	bool operator!=(const Matrix&);

	// multiply with a double 
	Matrix operator*(const double&);
	friend Matrix operator*(const double&, Matrix&);
	
	// multiply with a matrix
	Matrix operator*(const Matrix&)const;
	//friend Matrix operator*(const Matrix&, const Matrix&);

	// plus 
	Matrix operator+(const Matrix&);
	friend Matrix operator+(const double&, const Matrix&);
	friend Matrix operator+(const Matrix&, const double&);
	
	// minus
	Matrix operator-(const Matrix&)const;
	friend Matrix operator-(const double&, const Matrix&);
	friend Matrix operator-(const Matrix&, const double&);
	
	Matrix operator/(double);

	// Assignment Operator
	Matrix& operator=(const Matrix&);


	/////////////////////////  Itreator  /////////////////////////////

	class iterator: public std::iterator<std::forward_iterator_tag, double>{
	public:
		iterator();
		// Attention: the 3-th param is the size of the row.
		iterator(std::vector<std::vector<double> >::iterator, std::vector<double>::iterator, int, int);
		iterator& operator=(const iterator&);
		iterator operator++(int);
		iterator operator++();
		double& operator*();
		friend bool operator==(const iterator&, const iterator&);
		friend bool operator!=(const iterator&, const iterator&);
	private:
		std::vector<std::vector<double> >::iterator iter1;
		std::vector<double>::iterator iter2;
		int _width;
		int _height;
		int _step;
		int _line;
	};
	
	typedef const iterator& const_iterator;

	iterator begin();
	iterator end();
	const_iterator begin()const;
	const_iterator end()const;

protected:
	// protected class for advanced construction
	Matrix(int, int, double);
	//Matrix(Matrix::const_iterator, Matrix::const_iterator);

private:
	int _row;
	int _col;
    vector<vector<double>> _mat;
	iterator _begin;
	iterator _end;
};












template <typename T, size_t row, size_t col>
    static T MatGet(T(&matrix)[row][col], T r, T c) {
        if(0 <= r && r < row && 0 <= c && c < col){
		    return matrix[r][c];
	    } else {
		throw new outOfRangeExcep("Meghaladott méret");
	    }
    }

template <typename T, size_t row, size_t col>
    static T MatSet(T(&matrix)[row][col], T r, T c, T val) {
        T ret = 0;
	    if(r < row && c < col){
		    matrix[r][c] = val;
	    } else {
		    ret = 1;
		    throw new invalidParamExcep("Meghaladott méret");
	    }
	    return ret;
    }

template <typename T, size_t row, size_t col>
    static 

//** TEMPLATES MATRIX !!! */

//** TEMPLATES GRAPH !!! */



//** TEMPLATES GRAPH !!! */

bool isOdd(int x) {
    if(x % 2 != 0) {
        return true;
    }
    return false;
}

long long int SumToN(int n) {
    return n * (n+1) / 2;
}

void inArr(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
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