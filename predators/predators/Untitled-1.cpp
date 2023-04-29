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

//Operators	
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
	
//methodes	
	
	const double  Vecteur3D::norme2() const{
		return (*this)*(*this);
		}

	const double  Vecteur3D::norme() const {return (sqrt(norme2()));}

	Vecteur3D Vecteur3D::normalise(double facteur) const{
			double n;
			n=norme();
			if(n==0.0){
			return *this;
			}
			else{
			return (((*this)/n)*facteur);}
		}

	vector<Vecteur3D> Vecteur3D::generateur_de_repere_orthonorme() const{
			Vecteur3D v1(normalise());
			Vecteur3D v2(0,1,0);
			Vecteur3D v3(0,0,1);
			v2-=(v1*v2)*v1;
			v3-=((v1*v3)*v1+(v2*v3)*v2);
			vector<Vecteur3D> repere;
			v2.normalise();
			v3.normalise();
			repere.push_back(v1);
			repere.push_back(v2);
			repere.push_back(v3);
			return repere;
		}
	
	double Vecteur3D:: angle(Vecteur3D const & autre) const {
		return acos(((*this)*autre)/(1.0*norme()*autre.norme()));
		}
	
	void  Vecteur3D:: set_coord(unsigned int x, double a){ /// throw si x diff de 0 1 2 ???
		if (x==0){
			x_=a;
			return;
			}
		if (x==1){
			y_=a;
			return;
			}
		if (x==2){
			z_=a;
			return;
			}
		return;
		}


	

	const double Vecteur3D:: getx_() const{
		return x_;
		}
	const double Vecteur3D:: gety_() const{
		return y_;
		}
	const double Vecteur3D:: getz_()const{
		return z_;
		}
	///exterieur à la classe Vecteur3D
///************************************************************************
	const Vecteur3D operator + (Vecteur3D V1, Vecteur3D const& V2){
		V1 += V2;
		return V1;
		}
	
const Vecteur3D operator - (Vecteur3D V1, Vecteur3D const& V2){
	V1 -= V2;
	return V1;
	}	
	
	
const  Vecteur3D operator * (Vecteur3D  V1, double const& a){
		V1 *= a;
		return V1;
		}

const Vecteur3D operator * (double const& a ,Vecteur3D  V1 ){
		V1 *= a;
		return V1;
		}
		
const Vecteur3D operator / (Vecteur3D V1, double const& a){
	V1 /= a;
	return V1;
}

const Vecteur3D operator / (double const& a ,Vecteur3D  V1 ){
	V1 /= a;
	return V1;
	}

	
 const double operator * (Vecteur3D const& V1, Vecteur3D const& V2){
		 return (V1.getz_()*V2.getz_()+V2.gety_()*V1.gety_()+V1.getx_()*V2.getx_());
		}
	
const	Vecteur3D operator ^ (Vecteur3D V1, Vecteur3D const& V2){
		V1 ^= V2;
		return V1;
		}
	
	
	 ostream& operator << (ostream& sortie, Vecteur3D const& vecteur){
		 sortie << vecteur.getx_()<<" "<<vecteur.gety_()<<" "<<vecteur.getz_();
		 return sortie;
		}
	
	
	
ostream& operator << (std::ostream& sortie, vector<Vecteur3D> V1){
	if (V1.size() == 0){
		return sortie;
		}
	for ( size_t i (0); i< V1.size(); ++i){
		sortie << V1[i];
		}
	return sortie;
	}
	
	
	

vector <Vecteur3D> operator + (vector<Vecteur3D>& V1, vector<Vecteur3D> const& V2){
		if (V2.size() == 0){
		return V1;
		}
	for (size_t j (0);j < V2.size() ;++j){
		  Vecteur3D V (V2[j]);
		V1.push_back(V);
		}
	return V1;
	}
	
vector <Vecteur3D> operator +  (Vecteur3D const& x, vector<Vecteur3D>& V2){
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

	
//~ ************************************************************************	
//~ Fonctions dépassée en commentaire :

//~ void  Vecteur3D::affiche() const{
		//~ cout << x_ << " " << y_ << " " << z_ << " " << endl;
		//~ return;
		//~ }
//~ -------------------------------------------------------------------------

	//~ bool  Vecteur3D:: compare(Vecteur3D point) const{
		//~ if ((x_==point.x_) and (y_==point.y_) and (y_==point.y_)){
			//~ return true;
			//~ }
		//~ else {return false;}
		//~ }
//~ -----------------------------------------------------------------------------
//~ Vecteur3D  Vecteur3D:: prod_vect(Vecteur3D autre) const{
		//~ Vecteur3D vecteur_reponse;
		//~ vecteur_reponse.set_coord(0, (y_*autre.z_ - z_*autre.y_));
		//~ vecteur_reponse.set_coord(1, (z_*autre.x_ - x_*autre.z_));
		//~ vecteur_reponse.set_coord(2, (x_*autre.y_ - y_*autre.x_));
		//~ return vecteur_reponse;
		//~ }
//~ --------------------------------------------------------------------------
	 
	//~ Vecteur3D Vecteur3D:: soustraction(Vecteur3D autre) const{
		//~ return addition(autre.oppose());
		//~ }
//~ -----------------------------------------------------------------------------		
	//~ Vecteur3D Vecteur3D:: mult(double a) const{
 	//~ Vecteur3D vecteur_reponse;
		//~ vecteur_reponse.set_coord(0, a*x_);
		//~ vecteur_reponse.set_coord(1, a*y_);
		//~ vecteur_reponse.set_coord(2, a*z_);
		//~ return vecteur_reponse;
		//~ }
//~ -------------------------------------------------------------------------------
//~ Vecteur3D Vecteur3D::addition(Vecteur3D autre) const{
		//~ Vecteur3D vecteur_reponse;
		//~ vecteur_reponse.set_coord(0, x_+autre.x_);
		//~ vecteur_reponse.set_coord(1, y_+autre.y_);
		//~ vecteur_reponse.set_coord(2, z_+autre.z_);
		//~ return vecteur_reponse;
		//~ }
//~ ----------------------------------------------------------------------------
//~ Vecteur3D oppose() const{
		 //~ Vecteur3D vecteur_reponse;
		//~ vecteur_reponse.set_coord(0, -x_);
		//~ vecteur_reponse.set_coord(1, -y_);
		//~ vecteur_reponse.set_coord(2, -z_);
		//~ return vecteur_reponse;
		 //~ }
//~ *******************************************************************************



