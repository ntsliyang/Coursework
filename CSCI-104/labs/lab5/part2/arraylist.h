#ifndef ARRAYLIST_H
#define ARRAYLIST_H

class ArrayList {
	public:
		ArrayList();
		~ArrayList();

		/**
			Returns the size of the list
		*/
		int size () const;

		/**
			Add an int to the last position in the array.
			If the new array size is bigger than the capacity, resize.
			(Default capacity = 5)
		*/
		void add (const int & val);

		/**
			Insert an int to a certain position, and shift everything backwards.
			If the position is invalid, does not do anything.
			If the new array size is bigger than the capacity, resize.
			(Default capacity = 5)
		*/
		void insert (int position, const int & val);

		/**
			Removes an int from the position, and shift everytihng in place
			Calling remove(2) on | 1 2 3 4 5 | results in | 1 2 4 5 |
			If the position is invalid, does not do anything.
		**/
		void remove (int position);

		/**
			Replaces an int at the position with the new int.
			If the position is invalid, does not do anything.
		*/
		void set (int position, const int & val);

		/**
			Returns the int that's at the position specified
			Returns unexpected result if the position isn't valid - so ensure it is.
		*/
		int& get (int position);
		int const & get (int position) const;

	protected:
		void resize();
		int* array;
		int capacity; // defaults to 5

	private:
		int _size;
};
#endif
