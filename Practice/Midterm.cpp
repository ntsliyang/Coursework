// deep copy 
	char* names[10];
	char buffer[41];

	for (int i = 0; i < 10; i++) {
		cin >> buffer;
		names[i] = new char [strlen(buffer) + 1];
		strcpy(names[i], buffer);
	}

	for (int i = 0; i < 10; i++) {
		delete [] names[i];
	}

// deep copy (change 0th element)
	delete [] names[0];
	cin >> buffer;
	names[0] = new char [strlen(buffer) + 1];
	strcpy(names[0], buffer);

// file i/o (#include <fstream>)
	ifstream.ifile("document.txt"); // read a file
	ofstream.ifile("document.txt"); // write a file 
	ifstream.close(); // close reading file
	ofstream.close(); // close writing file
	cin.fail(); //
	cin.getline(char* buf, int bufsize); // read max of (bufsize-1) characters
	cin.clear(); // turn off fail flag
	cin.ignore(int size, char endingCharacter); // clear inputs (usually used in conjunction with 'cin.clear()')
	ifstream::get(); // return the character at 'fp' and moves 'fp' on by one
	ifstream::seek(); // return the character at 'fp' but NOT move 'fp' on
	ifstream.seekg(); // pass an offset value relative from current location from start or end
	ifstream.tellg(); // return the current location's byte-offset from the beginning 
	ios_base::beg // pos. from beginning of the file
	ios_base::cur // pos. relative to current location 
	iso_base::end // pos. relative to end of file (0 or negative number)
	ofstream.seekp() // go to a particular location
	ofstream.tellp() // return the current location's offset from beginning of the file

// removing an element 
	for (int i = pos + 1; i < current_size; i++) {
		values[i-1] = values[i];
	}
	current_size--;

// inserting an element 
	if (current_size < CAPACITY) {
		current_size++;
		for (int i = current_size - 1; i > pos; i--) {
			values[i] = values[i - 1];
		}
		values[pos] = new_element;
	}

// notices
	化成double的形式时要将式子里的int转换成double (比如1要改成1.0)
	创建一个新的array的时候一定要最后一位加'\0'
	Cin.fail()一定要在输入的时候call一次，处理的时候再call一次（避免次数有误）
	计算array的大小
		1. strlen(char* arr) 计算没有'\0'的array的长度 （所以strcpy的时候strlen要加1）
		2. sizeof(arr)/sizeof(arr[0]) 和 strlen(char* arr) 功能相同
		3. arr.length() 只能运用在string或者char**上
	
