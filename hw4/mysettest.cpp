#include "myset.h"
#include "webpage.h"
#include <iostream>
using namespace std;

int main() {
	MySetString set1;
	set1.insert("s1");
	set1.insert("s2"); 
	set1.insert("s3");

	MySetString set2;
	set2.insert("s2");
	set2.insert("s4");

	MySetString set1or2 = set1.set_intersection(set2);
	MySetString set1and2 = set1.set_union(set2);
}