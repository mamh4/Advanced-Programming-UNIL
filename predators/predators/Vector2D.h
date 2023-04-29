#include <iostream>
#include <vector>
#ifndef PRJ_Vector2D_H
#define PRJ_Vector2D_H


class Vector2D {
	
	public:
//~ PUBLIC----PUBLIC----PUBLIC----PUBLIC----PUBLIC----PUBLIC----PUBLIC----PUBLIC----PUBLIC----PUBLIC----PUBLIC----PUBLIC
	Vector2D(double x = 0, double y =0);

// Vector sum and difference
    const Vector2D operator += (Vector2D const& othervector);
	const Vector2D operator -= (Vector2D const& othervector);

// Scalar product
    const double scalar_product(Vector2D othervector) const;

// Scalar multiplication and division
	const Vector2D operator *= (double const& scalar);
	const Vector2D operator /= (double const& scalar);



// Vector norms
	const double l2norm() const;
	const double l1norm() const;

// Vector normalization 	
	Vector2D normalize(double factor=1.0) const;

// Vector  	
	std::vector<Vector2D> orthonormal_coordinated_generator() const;

// Angle with another vector  	
	double angle(Vector2D const & othervector) const;

// Vector Set 
	void set_coord(double x, double y);
		
// Vector Get 
	const double getx_() const;
	const double gety_()const;
	const double getz_()const;
	
	
	private:
//~ PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE----PRIVATE
	
// Attributes 
	double x_;
	double y_;
	};
	

/// Operator Surcharge 

const Vector2D operator + (Vector2D vector1, Vector2D const& vector2);
const Vector2D operator - (Vector2D vector1, Vector2D const& vector2);

const Vector2D operator * (Vector2D vector1, double const& scalar);
const Vector2D operator * (double const& scalar ,Vector2D  vector1);

const Vector2D operator / (Vector2D vector1, double const& scalar);
const Vector2D operator / (double const& scalar ,Vector2D  vector1 );

const double operator * (Vector2D const& vector1, Vector2D const& vector1);

const Vector2D operator ^ (Vector2D vector1, Vector2D const& vector2);

std::ostream& operator << (std::ostream& output1, Vector2D const& vector1);
std::ostream& operator << (std::ostream& output1, std::vector<Vector2D> vector1);

std::vector <Vector2D> operator + (std::vector<Vector2D>& vector1, std::vector<Vector2D> const& vector2);
std::vector <Vector2D> operator +  (DD const& x, std::vector<Vector2D> & vector1);
std::vector <Vector2D> operator + (std::vector<Vector2D>& vector1,Vector2D const& x);

const bool operator == (Vector2D const& vector1, Vector2D const& vector2); 

const bool operator < (Vector2D const& vector1, Vector2D const& vector2);
const bool operator < (Vector2D const& vector1, double const& scalar);
const bool operator < (double const& scalar,Vector2D const& vector1);
const bool operator > (Vector2D const& vector1, Vector2D const& vector2);
const bool operator > (Vector2D const& vector1, double const& scalar);
const bool operator > (double const& scalar,Vector2D const& vector1);

const bool operator <= (Vector2D const& vector1, Vector2D const& vector2);
const bool operator <= (Vector2D const& vector1, double const& scalar);
const bool operator <= (double const& scalar,Vector2D const& vector1);
const bool operator >= (Vector2D const& vector1, Vector2D const& vector2);
const bool operator >= (Vector2D const& vector1, double const& scalar);
const bool operator >= (double const& scalar,Vector2D const& vector1);

#endif // PRJ_Vector2D_H