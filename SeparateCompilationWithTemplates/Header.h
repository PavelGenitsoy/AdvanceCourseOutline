#pragma once

// Шаблоны неообходимо определять в том же месте, где вы объявляете сам шаблон   (т.е. в одном и том же файле)
// но можно делать велосипеды с использованием файлов с расширениями tpp



// либо так
/*
template <typename T>
class Test {
public:
	Test(T t);
private:
	T data;
};

template <typename T>
Test<T>::Test(T t) : data{ t } {}
*/



// либо так можно
template <typename T>
class Test {
public:
	Test(T t) : data{t} {}
private:
	T data;
};