#include "Position.h"
void  Position::Add(const Direction& dir) {
	x += dir.x;
	y += dir.y;
}
void Position::operator+=(const Direction& dir) {
	x += dir.x;
	y += dir.y;
}
Position Position::operator+(const Direction& dir) {
	Position pos;
	pos.x = x + dir.x;
	pos.y = y + dir.y;
	return pos;
}