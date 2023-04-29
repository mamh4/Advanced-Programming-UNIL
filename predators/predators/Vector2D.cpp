#include "Vector2D.h"
#include <iostream>
#include <cmath>
#include <vector>
 using namespace std;

///Within the Vector2DcClass 

// Set function
Vector2D::Vector2D(double x , double y)
: x_(x), y_(y)
{}

//Self Operators	
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
	
vector <Vector2D> operator +  (Vecteur3D const& x, vector<Vecteur3D>& V2){
    V2.push_back(x);
	return V2;
	}
vector <Vecteur3D> operator + (vector<Vecteur3D>& V2,Vecteur3D const& x){
	V2.push_back(x);
	return V2;
	}
	
	
const bool operator == (Vecteur3D const& V1, Vecteur3D const& V2){
	if (((V1.getx_()==V2.getx_()) and (V1.gety_()==V2.gety_())) and (V1.getz_()==V2.getz_())){
		return true;
		}
	return false;
	} 
	const bool operator < (Vecteur3D const& V1, Vecteur3D const& V2){
		if (V1.norme2()<V2.norme2()){
			return true;
			}else{
				return false;
				}
		}

const bool operator < (Vecteur3D const& V1, double const& a){
if (V1.norme2()< a){
			return true;
			}else{
				return false;
				}
		}
		
const bool operator < (double const& a,Vecteur3D const& V1){
if (a< V1.norme2()){
			return true;
			}else{
				return false;
				}
		}
		

const bool operator > (Vecteur3D const& V1, Vecteur3D const& V2){
if (V1.norme2()>V2.norme2()){
			return true;
			}else{
				return false;
				}
		}

const bool operator > (Vecteur3D const& V1, double const& a){
	if (V1.norme2()>a){
			return true;
			}else{
				return false;
				}
	}
	const bool operator > (double const& a,Vecteur3D const& V1){
if (a > V1.norme2()){
			return true;
			}else{
				return false;
				}
		}
const bool operator <= (Vecteur3D const& V1, Vecteur3D const& V2){
	return V2>V1;
	}
const bool operator <= (Vecteur3D const& V1, double const& a){
	return a>V1;
	}
const bool operator <= (double const& a, Vecteur3D const& V1){
	return V1>a;
	}
const bool operator >= (Vecteur3D const& V1, Vecteur3D const& V2){
	return V2<V1;
	}
const bool operator >= (Vecteur3D const& V1, double const& a){
	return a<V1;
	}
const bool operator >= (double const& a,Vecteur3D const& V1){
	return V1<a;
	}