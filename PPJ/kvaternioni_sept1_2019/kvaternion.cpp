#include "kvaternion.hpp"
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstdio>

std::string Kvaternion::postavi_komponentu(char komponenta, float vrednost) {
	
	std::stringstream err_twice; 
	err_twice << "Bazni element " << komponenta  << " se ne moze definisati dva puta. ";
	std::string success = "Success";
	
	if (komponenta == 's') {
		if (!is_s_def) {
			is_s_def = true;
			s = vrednost;	
			return success;
		} else {
			return err_twice.str();
		}
	} else if (komponenta == 'i') {
		if (!is_i_def) {
			i = vrednost;	
			is_i_def = true;
			return success;
		} else {
			return err_twice.str();
		}
	} else if (komponenta == 'j') {
		if (!is_j_def) {
			j = vrednost;	
			is_j_def = true;
			return success;
		} else {
			return  err_twice.str();
		}
	} else if (komponenta == 'k') {
		if (!is_k_def) {
			k = vrednost;	
			is_k_def = true;
			return success;
		} else {
			 return err_twice.str();
		}
	} else {
		std::stringstream err_msg;
		err_msg << komponenta << " ne moze biti bazni element. ";
		return err_msg.str();
	}

	return "Greska prikikom definicije kvaterniona.";
}

float Kvaternion::komponenta(char komponenta) {
		switch(komponenta) {
			case 's' : return s;
			case 'i' : return i;
			case 'j' : return j;
			case 'k' : return k;
			default: std::cout << "Nepostojeci ID komponente" << std::endl;
		}
		return 0;
}

std::ostream& operator << (std::ostream& out, const Kvaternion& kv) {

	auto sgn = [](float num) -> std::string {
		if (num < 0) return " - ";
		else return " + ";
	};
	
	out << std::setprecision(2);
	std::fixed(out);

	out << kv.s  << sgn(kv.i) << std::fabs(kv.i) << "i" 
		<< sgn(kv.j) << std::fabs(kv.j) << "j"
		<< sgn(kv.k) << std::fabs(kv.k) << "k";

	return out;
}


float Kvaternion::norma(const Kvaternion &k) {
	return sqrt(k.s*k.s + k.i*k.i + k.j*k.j + k.k * k.k);
}

Kvaternion operator - (const Kvaternion &q) {
	Kvaternion result = Kvaternion();
	result.s = -q.s;
	result.i = -q.i;
	result.j = -q.j;
	result.k = -q.k;
	return result;
}
Kvaternion operator + (const Kvaternion &q, const Kvaternion& r) {
	Kvaternion result = Kvaternion();
	result.s = q.s + r.s;
	result.i = q.i + r.i;
	result.j = q.j + r.j;
	result.k = q.k + r.k;
	return result;
}
Kvaternion operator / (const Kvaternion &q, const Kvaternion& r) {
	Kvaternion rez = Kvaternion();
	float t0, t1, t2, t3;
	
	t0 = (r.s*q.s + r.i*q.i + r.j*q.j + r.k*q.k)/(r.s*r.s + r.i*r.i + r.j*r.j + r.k*r.k);
	t1 = (r.s*q.i - r.i*q.s - r.j*q.k + r.k*q.j)/(r.s*r.s + r.i*r.i + r.j*r.j + r.k*r.k);
	t2 = (r.s*q.j + r.i*q.k - r.j*q.s - r.k*q.i)/(r.s*r.s + r.i*r.i + r.j*r.j + r.k*r.k);
	t3 = (r.s*q.k - r.i*q.j + r.j*q.i - r.k*q.s)/(r.s*r.s + r.i*r.i + r.j*r.j + r.k*r.k);
	rez.s = t0;
	rez.i = t1;
	rez.j = t2;
	rez.k = t3;
	return rez;
}
Kvaternion operator * (const Kvaternion &q, const Kvaternion& r) {
	float n0, n1, n2, n3;
	Kvaternion rez;
	n0 = r.s*q.s - r.i*q.i - r.j*q.j - r.k*q.k;
	n1 = r.s*q.i + r.i*q.s - r.j*q.k + r.k*q.j;
	n2 = r.s*q.j + r.i*q.k + r.j*q.s - r.k*q.i;
	n3 = r.s*q.k - r.i*q.j + r.j*q.i + r.k*q.s;
	rez.s = n0;
	rez.i = n1;
	rez.j = n2;
	rez.k = n3;
	return rez;
}
Kvaternion operator - (const Kvaternion &q, const Kvaternion& r) {
	return q + (-r);
}

Kvaternion operator * (float a, const Kvaternion& q) {
	Kvaternion result = Kvaternion();
	result.s = q.s * a;
	result.i = q.i * a;
	result.j = q.j * a;
	result.k = q.k * a;
	return result;
}
