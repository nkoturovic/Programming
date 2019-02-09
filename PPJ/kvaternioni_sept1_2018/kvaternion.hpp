#ifndef _KVATERNION_H_
#define _KVATERNION_H_

#include <iostream>


class Kvaternion {
private: 
	bool is_s_def = false, is_i_def = false, is_j_def = false, is_k_def = false;

	friend std::ostream& operator << (std::ostream& out, const Kvaternion& kv);
	friend Kvaternion operator - (const Kvaternion &q);
	friend Kvaternion operator + (const Kvaternion &q, const Kvaternion& r);
	friend Kvaternion operator - (const Kvaternion &q, const Kvaternion& r);
	friend Kvaternion operator * (const Kvaternion &q, const Kvaternion& r);
	friend Kvaternion operator * (float a, const Kvaternion& q);
	friend Kvaternion operator / (const Kvaternion &q, const Kvaternion& r);
	
public:
	float s = 0, i = 0, j = 0, k = 0;

	std::string postavi_komponentu(char komponenta, float vrednost);
	float komponenta(char komponenta);
	static float norma(const Kvaternion &k);
};


std::ostream& operator << (std::ostream& out, const Kvaternion& kv);
Kvaternion operator - (const Kvaternion &q);
Kvaternion operator + (const Kvaternion &q, const Kvaternion& r);
Kvaternion operator - (const Kvaternion &q, const Kvaternion& r);
Kvaternion operator * (const Kvaternion &q, const Kvaternion& r);
Kvaternion operator * (float a, const Kvaternion& q);
Kvaternion operator / (const Kvaternion &q, const Kvaternion& r);



#endif
