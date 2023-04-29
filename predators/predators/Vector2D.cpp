#include "Vector2D.h"
#include <iostream>
#include <cmath>
#include <vector>
 using namespace std;

///Within the Vector2DcClass 

// Initializing
Vector2D::Vector2D(double x , double y)
: x_(x), y_(y)
{}

// Set
void  Vector2D:: set_coord(boolean coord_select, double coord){
	if (coord_select){
		x_=coord;
		return;
		}
	else {
		y_=coord;
		return;
		}
	return;
	}

// Get
const double Vector2D:: getx_() const{
	return x_;
	}
const double Vector2D:: gety_() const{
	return y_;
	}
const double Vector2D:: getz_()const{
	return z_;
	}

//Operators	onto self
    //Vectorial sum 
		const Vector2D Vector2D::operator += (Vector2D const& othervector){
			x_ += othervector.x_;
			y_ += othervector.y_;
			return *this;
			}
    //Vectorial difference     
		 const Vector2D Vector2D::operator -= (Vector2D const& othervector){
			 x_ -= othervector.x_;
			 y_ -= othervector.y_;
			 return *this;
			 }
	//Product with a scalar
		const Vector2D Vector2D::operator *= (double const& scalar){
			 x_ *= scalar;
			 y_ *= scalar;
			 return *this;
			 }
	//Division by a scalar 
		const Vector2D Vector2D::operator /= (double const& scalar){
		x_ *= 1/scalar;
		y_ *= 1/scalar;
	return *this;
	}

//Scalar product 
const double  Vector2D:: scalar_product(Vector2D othervector) const{
			return ((x_*othervector.x_) + (y_*othervector.y_));
	}

//L2 Norm
const double  Vector2D::squaredl2norm() const{
	return (*this)*(*this);
	}
const double  Vector2D::l2norm() const {return (sqrt(squaredl2norm()));}

//Normalize
Vector2D Vector2D::normalize(double factor) const{
		double currentnorm;
		currentnorm=l2norm();
		if(currentnorm==0.0){
		return *this;
		}
		else{
		return (((*this)/currentnorm)*factor);}
	}

//Generate an orthonormal basis aligned with the vector 
vector<Vector2D> Vector2D::orthonomal_basis_generator() const{
			Vector2D vector1(normalize());
			Vector2D vector2(0,1,0);
			vector2-=(vector1*vector2)*vector1;
			vector<Vector2D> basis;
			vector2.normalize();
			basis.push_back(vector1);
			basis.push_back(vector2);
			return basis;
		}
	
// Determine the angle between two vectors 
double Vector2D:: angle(Vector2D const & othervector) const {
	return acos(((*this)*othervector)/(1.0*norme()*othervector.norme()));
	}

// Outside of class 

// Operator Surcharge 
	// Vectorial sum
	const Vector2D operator + (Vector2D vector1, Vector2D const& vector2){
			vector1 += vector2;
			return vector1;
			}
	// Vectorial difference
	const Vector2D operator - (Vector2D vector1, Vector2D const& vector2){
		vector1 -= vector2;
		return vector1;
		}	
	//Product of a vector with a scalar 
	const  Vector2D operator * (Vector2D  vector1, double const& scalar){
			vector1 *= scalar;
			return vector1;
			}
	//Product of a scalar with a vector 
	const Vector2D operator * (double const& scalar ,Vector2D  vector1 ){
			vector1 *= scalar;
			return vector1;
			}
	//Division of a vector by a scalar  	
	const Vector2D operator / (Vector2D vector1, double const& scalar){
		vector1 /= scalar;
		return vector1;
	}
	//Scalar product 
 	const double operator * (Vector2D const& vector1, Vector2D const& vector2){
		 return (vector1.getx_()*vector2.getx_()+vector1.gety_()*vector2.gety_());
		}
	
	//Append a message with a vector 
	 ostream& operator << (ostream& output1, Vector2D const& vector1){
		 output1 << vector1.getx_()<<" "<<vector1.gety_()<<;
		 return output1;
		}
	//Append a message with a vector of vectors
	ostream& operator << (std::ostream& output1, vector<Vector2D> vector1){
		if (vector1.size() == 0){
			return output1;
			}
		for ( size_t i (0); i< vector1.size(); ++i){
			output1 << vector1[i];
			}
		return output1;
		}
	//Append a vector of vectors with a vector of vectors
	vector <Vector2D> operator + (vector<Vector2D>& vector1, vector<Vector2D> const& vector2){
			if (vector2.size() == 0){
			return vector1;
			}
		for (size_t j (0);j < vector2.size() ;++j){
			Vector2D V (vector2[j]);
			vector1.push_back(V);
			}
		return vector1;
		}
	//Append a vector of vectors with a vector (vector as first term)
	vector <Vector2D> operator +  (Vector2D const& vector1, vector<Vector2D>& vector2){
   		vector2.push_back(vector1);
		return vector2;
		}
	//Append a vector of vectors with a vector (vector as second term)
	vector <Vector2D> operator + (vector<Vector2D>& vector1,Vector2D const& vector2){
		vector1.push_back(vector2);
		return vector1;
		}
	//Check equality of vectors
	const bool operator == (Vector2D const& vector1, Vector2D const& vector2){
		if (((vector1.getx_()==vector2.getx_()) and (vector1.gety_()==vector2.gety_()))){
			return true;
			}
		return false;
		} 
	//Compare the norm of vectors
	const bool operator < (Vector2D const& vector1, Vector2D const& vector2){
		return (vector1.l2norm()<vector2.l2norm());
		}
	const bool operator > (Vector2D const& vector1, Vector2D const& vector2){
		return (vector1.l2norm()>vector2.l2norm()); 
		}
	const bool operator <= (Vector2D const& vector1, Vector2D const& vector2){
		return not (vector1>vector2);
		}
	const bool operator >= (Vector2D const& vector1, Vector2D const& vector2){
		return not (vector1<vector2);
		}
	//Compare the norm of a vector with a scalar 
	const bool operator < (Vector2D const& vector1, double const& scalar){
		return (vector1.l2norm()<scalar); 
		}
	const bool operator > (Vector2D const& vector1, double const& scalar){
		return (vector1.l2norm()>scalar); 
		}
	const bool operator <= (Vector2D const& vector1, double const& scalar){
		return not (vector1 >scalar); 
		}
	const bool operator >= (Vector2D const& vector1, double const& scalar){
		return not (vector1 < scalar); 
		}
	const bool operator < (double const& scalar, Vector2D const& vector1){
		return (vector1 > scalar); 
		}
	const bool operator > (double const& scalar, Vector2D const& vector1){
		return (vector1 < scalar); 
		}
	const bool operator <= (double const& scalar, Vector2D const& vector1){
		return (vector1 >= scalar); 
		}
	const bool operator >= (double const& scalar, Vector2D const& vector1){
		return (vector1 <= scalar); 
		}
