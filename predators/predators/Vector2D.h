#include <iostream>
#include <vector>
#ifndef PRJ_Vector2D_H
#define PRJ_Vector2D_H


class Vector2D {
	
	public:
//~ PUBLIC

// Initialization
	Vector2D(double x = 0, double y =0);

// Set
	void set_coord(boolean coord_select, double coord);
		
// Get
	const double getx_() const;
	const double gety_()const;
	const double getz_()const;

//Operators	onto self
	//Vectorial sum 
		const Vector2D operator += (Vector2D const& othervector);
	//Vectorial difference 
		const Vector2D operator -= (Vector2D const& othervector);
	//Product with a scalar
		const Vector2D operator *= (double const& scalar);
	//Division by a scalar 
		const Vector2D operator /= (double const& scalar);

//Scalar product 
    const double scalar_product(Vector2D othervector) const;

//L2 Norm
	const double squaredl2norm() const;
	const double l2norm() const;

//Normalize
	Vector2D normalize(double factor=1.0) const;

//Generate an orthonormal basis aligned with the vector 
	std::vector<Vector2D> orthonormal_coordinated_generator() const;

// Determine the angle between two vectors 
	double angle(Vector2D const & othervector) const;

	private:
//~ PRIVATE
	
// Attributes 
	double x_;
	double y_;
	};

// Outside of class 

// Operator Surcharge 
	// Vectorial sum
		const Vector2D operator + (Vector2D vector1, Vector2D const& vector2);
	// Vectorial difference
		const Vector2D operator - (Vector2D vector1, Vector2D const& vector2);
	//Product of a vector with a scalar 
		const Vector2D operator * (Vector2D vector1, double const& scalar);
	//Product of a scalar with a vector 
		const Vector2D operator * (double const& scalar ,Vector2D  vector1);
	//Division of a vector by a scalar  	
		const Vector2D operator / (Vector2D vector1, double const& scalar);
	//Scalar product 
		const double operator * (Vector2D const& vector1, Vector2D const& vector1);
	//Append a message with a vector 
		std::ostream& operator << (std::ostream& output1, Vector2D const& vector1);
	//Append a message with a vector of vectors
		std::ostream& operator << (std::ostream& output1, std::vector<Vector2D> vector1);
	//Append a vector of vectors with a vector of vectors
		std::vector <Vector2D> operator + (std::vector<Vector2D>& vector1, std::vector<Vector2D> const& vector2);
	//Append a vector of vectors with a vector (vector as first term)
		std::vector <Vector2D> operator +  (DD const& x, std::vector<Vector2D> & vector1);
	//Append a vector of vectors with a vector (vector as second term)
		std::vector <Vector2D> operator + (std::vector<Vector2D>& vector1,Vector2D const& x);
	//Check equality of vectors
		const bool operator == (Vector2D const& vector1, Vector2D const& vector2); 
	//Compare the norm of vectors
		const bool operator < (Vector2D const& vector1, Vector2D const& vector2);
		const bool operator > (Vector2D const& vector1, Vector2D const& vector2);
		const bool operator <= (Vector2D const& vector1, Vector2D const& vector2);
		const bool operator >= (Vector2D const& vector1, Vector2D const& vector2);
	//Compare the norm of a vector with a scalar 
	const bool operator < (Vector2D const& vector1, double const& scalar);
	const bool operator > (Vector2D const& vector1, double const& scalar);
	const bool operator <= (Vector2D const& vector1, double const& scalar);
	const bool operator >= (Vector2D const& vector1, double const& scalar);
	const bool operator < (double const& scalar, Vector2D const& vector1);
	const bool operator > (double const& scalar, Vector2D const& vector1);
	const bool operator <= (double const& scalar, Vector2D const& vector1);
	const bool operator >= (double const& scalar, Vector2D const& vector1);

#endif // PRJ_Vector2D_H