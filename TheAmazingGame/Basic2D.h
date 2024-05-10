#pragma once
template <typename T>
class Basic2D
{
public:
	T x;
	T y;
	Basic2D();
	Basic2D(const T& x, const T& y);
	Basic2D(const Basic2D& base);
	void SetXY(const T& x, const T& y);
	void AddXY(const T& x, const T& y);
	void operator=(const Basic2D&);
	void operator+=(const Basic2D&);
	void operator-=(const Basic2D&);
	void operator*=(const Basic2D&);
	void operator/=(const Basic2D&);
	bool operator==(const Basic2D&);
	bool operator!=(const Basic2D&);

};
template <typename T>
Basic2D<T>::Basic2D() {
	x = 0;
	y = 0;
}
template <typename T>
Basic2D<T>::Basic2D(const T& _x, const T& _y) {
	x = _x;
	y = _y;
}
template <typename T>
Basic2D<T>::Basic2D(const Basic2D& base) {
	x = base.x;
	y = base.y;
}
template <typename T>
void  Basic2D<T>::SetXY(const T& _x, const T& _y) {
	x = _x;
	y = _y;
}
template <typename T>
void  Basic2D<T>::AddXY(const T& _x, const T& _y) {
	x += _x;
	y += _y;
}
template <typename T>
void Basic2D<T>::operator=(const Basic2D& pos) {
	x = pos.x;
	y = pos.y;
}
template <typename T>
void Basic2D<T>::operator+=(const Basic2D& pos) {
	x += pos.x;
	y += pos.y;
}
template <typename T>
void Basic2D<T>::operator-=(const Basic2D& pos) {
	x -= pos.x;
	y -= pos.y;
}
template <typename T>
void Basic2D<T>::operator*=(const Basic2D& pos) {
	x *= pos.x;
	y *= pos.y;
}
template <typename T>
void Basic2D<T>::operator/=(const Basic2D& pos) {
	x /= pos.x;
	y /= pos.y;
}
template <typename T>
bool Basic2D<T>::operator==(const Basic2D& pos) {
	if (x == pos.x && y == pos.y)
		return true;
	return false;
}
template <typename T>
bool Basic2D<T>::operator!=(const Basic2D& pos) {
	if (x == pos.x && y == pos.y)
		return false;
	return true;
}


