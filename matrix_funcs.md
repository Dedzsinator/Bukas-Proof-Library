    /*
		The size of the matrix. 
		Input: 0 or 1
		Output:  the number of rows or columns
	*/
	int size(int)const;

	/*
		Fetch a certain element in the matrix
		Input: row and column
		Output: an element in the matrix
	*/
	double get(int row, int col)const;

	/*
		 Set a element to a certain value
		 Input: row, colume, value
		 Output: 0 or 1 (success or failure).
	*/
	int set(int row, int col, double value);

	/*
		Print the matrix on the console window.
	*/
	void print();

	/*
		Read from input stream.
	*/
	void read(std::istream&);

	/*
		Convert matrix to std::vector
	*/
	std::vector<std::vector<double> > toVector();