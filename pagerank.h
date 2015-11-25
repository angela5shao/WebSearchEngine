#ifndef PAGERANK_H
#define PAGERANK_H

#include <iostream>
#include <set>
#include <map>
#include "myset.h"
#include "webpage.h"
using namespace std;

// adds PR value to the given candidate page set
void pagerank(set<WebPage*> pages, int steps, double e) {
	map<WebPage*, set<WebPage*> > inLinks_;
	map<WebPage*, set<WebPage*> > outLinks_;

	// add self-loop
	for (set<WebPage*>::iterator it = pages.begin(); it != pages.end(); ++it) {

		myset<WebPage*> set1 = (*it)->incoming_links();
		set1.insert(*it); // add self-loop
		set<WebPage*> tempSet;
		// only include pages in set1 that aren't in candidate set
		for (set<WebPage*>::iterator set1It = set1.begin(); set1It != set1.end(); ++set1It) {
			if (pages.find(*set1It) != pages.end()) {
				tempSet.insert(*set1It);
			}
		}
		inLinks_.insert(pair<WebPage*, set<WebPage*> >(*it, tempSet));

		set1 = (*it)->outgoing_links();
		set1.insert(*it);
		set<WebPage*>tempSet2;
		for (set<WebPage*>::iterator set1It = set1.begin(); set1It != set1.end(); ++set1It) {
			if (pages.find(*set1It) != pages.end()) {
				tempSet2.insert(*set1It);
			}
		}
		outLinks_.insert(pair<WebPage*, set<WebPage*> >(*it, set1));

		// set PR at step 0 to 1/n
		(*it)->setPR(1.0 / pages.size());
	}

	map<WebPage*, double> sumMap;
	for (int i=0; i<steps; i++) {
		// for each page, store and calculate summation value in PR equation
		for (set<WebPage*>::iterator pgIt = pages.begin(); pgIt != pages.end(); ++pgIt) {
			double sum = 0;

			set<WebPage*> in = inLinks_.find(*pgIt)->second;
			for (set<WebPage*>::iterator inIt = in.begin(); inIt != in.end(); ++inIt) {
				sum += (*inIt)->PR() / outLinks_.find(*inIt)->second.size();
			}

			// if page isn't in sumMap already, insert; else, update
			if (sumMap.find(*pgIt) == sumMap.end()) {
				sumMap.insert(pair<WebPage*, double>(*pgIt, sum));
			} else { 
				sumMap.find(*pgIt)->second = sum;
			}
		}

		// for each page, calculate & update PR value
		double sum = 0;
		for (set<WebPage*>::iterator pgIt = pages.begin(); pgIt != pages.end(); ++pgIt) {
			double pr = (1-e) * sumMap.find(*pgIt)->second + e/pages.size();
			(*pgIt)->setPR(pr);

			//cout << "  " << (*pgIt)->filename() << " : " << (*pgIt)->PR() << endl;
			sum += pr;
		}
		//cout << sum << endl;
	}

}

#endif