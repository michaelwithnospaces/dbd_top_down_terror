#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector2D<T> {
public:
	Vector2D(T _x, T _y) { this->x = _x; this->y = _y; }
	Vector2D(Vector2D<T> vec) { this->x = vec.x; this->y = vec.y; }
	Vector2D(Vector2D<T>* vec) { this->x = vec->x; this->y = vec->y; }
	
	T x;
	T y;
	
	T distance(Vector2D<T> vec) {
		T xDist = vec.x - this->x;
		T yDist = vec.y - this->y;
		return sqrt(xDist * xDist + yDist * yDist);
	}

	Vector2D<T> mul(Vector2D<T> other) {
		Vector2D<T> n;
		n.x = this->x * other.x;
		n.y = this->y * other.y;
		return n;
	}

	Vector2D<T> div(Vector2D<T> other) {
		Vector2D<T> n;
		n.x = this->x / other.x;
		n.y = this->y / other.y;
		return n;
	}

	Vector2D<T> sub(Vector2D<T> other) {
		Vector2D<T> n;
		n.x = this->x - other.x;
		n.y = this->y - other.y;
		return n;
	}

	Vector2D<T> add(Vector2D<T> other) {
		Vector2D<T> n;
		n.x = this->x + other.x;
		n.y = this->y + other.y;
		return n;
	}
private:
};

typedef Vector2i Vector2D<int>
typedef Vector2f Vector2D<float>
typedef Vector2d Vector2D<double>

#endif