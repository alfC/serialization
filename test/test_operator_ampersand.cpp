// this file tests that boost serialization works with a class that overloads operator&

#include<iostream>

#include<boost/serialization/nvp.hpp>
#include<boost/archive/xml_oarchive.hpp>
#include<boost/archive/xml_iarchive.hpp>

#include<sstream>

struct A{
	int val;
	int operator&(){return val;}
	template<class Archive> void serialize(Archive & ar, const unsigned int){
		ar & BOOST_SERIALIZATION_NVP(val);
	}
};

int main(){

	A a;
	a.val = 5;

	std::stringstream s;
	{
	    boost::archive::xml_oarchive oa(s);
	    oa << BOOST_SERIALIZATION_NVP(a);
	}
	A a2;
	{
	    boost::archive::xml_iarchive ia(s);
	    ia >> BOOST_SERIALIZATION_NVP(a2);
	}
	assert( a.val == a2.val );
	return 0;
}
