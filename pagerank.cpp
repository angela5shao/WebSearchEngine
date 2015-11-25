#include <iostream>
#include <set>
#include <map>
#include <vector>
#include "myset.h"
#include "webpage.h"
using namespace std;

class Node {
public:
	Node(WebPage* w) {
		page_ = w;

		// add a self-loop
		outLinks_ = w->outgoing_links();
		inLinks_ = w->incoming_links();
		outLinks_.insert(w); 
		inLinks_.insert(w);
	}
	WebPage* page() {return page_;}
	string name() {return page_->filename();}
	set<WebPage*> outLinks() {return outLinks_;}
	set<WebPage*> inLinks() {return inLinks_;}
	void setPR(double pr) {PR_ = pr;}
	double PR() const {return PR_;}

private:
	WebPage* page_; // page of the node
	set<WebPage*> outLinks_;
	set<WebPage*> inLinks_;
	double PR_;
};




class Graph {
public: 
	Graph(const set<WebPage*>& pages, int steps, double e) {
		for (set<WebPage*>::iterator it = pages.begin(); it != pages.end(); ++it) {
			Node* n = new Node(*it);
			nodeSet_.insert(n);
			nodeMap_.insert(pair<WebPage*, Node*>(*it, n));
		}
		steps_ = steps;
		restartProb_ = e;
	}
	~Graph() {
		for (set<Node*>::iterator it = nodeSet_.begin(); it != nodeSet_.end(); ++it) {
			delete *it;
		}
	}
	vector<Node*> pageRank() {
		for (int i=0; i<steps_; i++) {
			// for each node, calculate the sum value for its PR equation and store in sumMap
			map<Node*, double> sumMap;
			for (set<Node*>::iterator it = nodeSet_.begin(); it != nodeSet_.end(); ++it) {
				double sum = 0;
				set<WebPage*> in = (*it)->inLinks();
				//set<Node*> in = nodeSet_.find(*it)->inLinks();
				for (set<WebPage*>::iterator inIt = in.begin(); inIt != in.end(); ++inIt) {
					sum += (*inIt)->PR() / nodeMap_.find(*inIt)->second->outLinks().size();
				}

				sumMap.insert(pair<Node*, double>(*it, sum));
			}

			// update each node's PR value
			for (set<Node*>::iterator it = nodeSet_.begin(); it != nodeSet_.end(); ++it) {
				double pr = (1-restartProb_) * sumMap.find(*it)->second + restartProb_/nodeSet_.size();
				(*it)->setPR(pr);
				cout << (*it)->name() << " : " << (*it)->PR() << endl;
			}
		}

		vector<Node*> v;
		for (set<Node*>::iterator it = nodeSet_.begin(); it != nodeSet_.end(); ++it) {
			v.push_back(*it);
		}
		return v;
	}

private:
	myset<Node*> nodeSet_; // set of all Nodes
	map<WebPage*, Node*> nodeMap_; // maps webpage to node
	int steps_;
	double restartProb_;
};



void pageRankHelper(myset<WebPage*>& pages, int steps);
void pageRank(myset<WebPage*>& pages, int steps, char* configFile) {
	
	for (set<WebPage*>::iterator it = pages.begin(); it != pages.end(); ++it) {
		(*it)->setPR(1.0/pages.size());
	}
	//pageRankHelper(pages, steps);
}

void pageRankHelper(myset<WebPage*>& pages, int steps) {
	// for each step
	for (int i=0; i<steps; i++) {
		cout << "STEP " << i+1 << endl;
		// create temp map to store PR for current step
		map<string,double> temp;
		for (set<WebPage*>::iterator it = pages.begin(); it != pages.end(); ++it) {
			double sum = 0;
			set<WebPage*> in = (*it)->incoming_links();
			for (set<WebPage*>::iterator it2 = in.begin(); it2 != in.end(); ++it2) {
				sum += (*it2)->PR()/((*it2)->outgoing_links().size() + 1); // all nodes have a self loop
			}
			// add itself as an incoming AND outgoing link 
			sum += (*it)->PR()/((*it)->outgoing_links().size() + 1);
			temp.insert(pair<string,double>((*it)->filename(), sum));
			//cout << "  insert:" << (*it)->filename() << " " << sum << endl;
		}

		// update PR for each page
		double total = 0;
		for (set<WebPage*>::iterator it = pages.begin(); it != pages.end(); ++it) {
			if (temp.find((*it)->filename()) == temp.end()) cout << "CANNOT FIND" << endl;
			
			// update its PR value ----------------------------------make e a variable in config -------
			double e = 0.15;
			double pr = (1-e)*temp.find((*it)->filename())->second + e/pages.size();
			(*it)->setPR(pr);
			cout << "  " << (*it)->filename() << " " << pr << endl;
			total += pr;
		}
		cout << "  " << total << endl;
	}
}