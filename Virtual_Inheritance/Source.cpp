#include <iostream>


/*
	*******     ******
	*Base *     *Base*
	*******     ******
	   *          *
	*******     ******
	*Der1 *     *Der2*
	*******     ******
	   *         *
		*       *
		  *******
		  *Join *
		  *******
*/

/*Diamond problem*/

class Base {
public:
	/*...*/
protected:
	int data_;
};
class Der1 : public Base { /*...*/ };
class Der2 : public Base { /*...*/ };

class Join : public Der1, public Der2 {
public:
	void method()
	{
		//data_ = 1;
	}
};
/*********InMemory*****************/
/*     *************              */
/*     *  Base     *              */
/*     *  Der1     *              */
/*     *************              */
/*                                */
/*     *************              */
/*     *  Base     *              */
/*     *  Der2     *              */
/*     *************              */
/*                                */
/*          Join                  */
/**********************************/


// РЕШЕНИЕ ПРОБЛЕМЫ

/*
		  ******
		  *Base*
		  ******
		  *   *
		 *     *
	*******     ******
	*Der1 *     *Der2*
	*******     ******
	   *         *
		*       *
		  *******
		  *Join *
		  *******
*/

class Base_ {
public:
	Base_(int) {}
protected:
	int data_;
};

class Der1_ : public virtual Base_ {
public:
	Der1_(int i) : Base_(i) {}
};

class Der2_ : public virtual Base_ { 
public: 
	Der2_(int i) : Base_(i) {}
};

class Join_ : public Der1_, public Der2_ {
public:		// из-за того, что появился virtual, этот производный класс является ответственным за инициализацию Base
	Join_(int i) : Base_{ i }, Der1_ { i }, Der2_{ i } {}  

	void method()
	{
		data_ = 1;
	}
};

int main(int argc, const char* argv[]) {

	// Base* join = new Join(); // ошбика неоднозначности 

	Base_* join = new Join_(10);

	system("pause");
	return 0;
}