/*
 * main.cpp
 *
 *  Created on: 2014/11/07
 *      Author: HondaDai
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Citys {

private:
	string* citys;
	int size;

public:
	Citys(int n) {
		citys = new string[n];
		size = n;
	}

	~Citys() {
		delete[] citys;
	}

	void setName(int index, string name) {
		citys[index] = name;
	}

	string getName(int index) {
		return citys[index];
	}

	int getIndex(string name) {
		for (int i=0;i<size;i++) {
			if (citys[i] == name) {
				return i;
			}
		}
		return -1;
	}
};

class Path {
public:
	string c1, c2;
	int cost;
	Path(string c1, string c2, int cost) {
		this->c1 = c1;
		this->c2 = c2;
		this->cost = cost;
	}

	Path* clone() {
		return new Path(c1, c2, cost);
	}
};

class Paths {
private:
	vector<Path*> paths;

	static bool sortByCostComparer(Path* p1, Path* p2) {
		return p1->cost < p2->cost;
	}
public:

	~Paths() {
		for(int i=0;i<paths.size();i++) {
			Path* p = paths.back();
			paths.pop_back();
			delete p;
		}
	}

	int getCost(string c1, string c2) {
		for(int i=0;i<paths.size();i++) {
			Path* p = paths[i];
			if ((p->c1 == c1 && p->c2 == c2) || (p->c1 == c2 && p->c2 == c1)) {
				return p->cost;
			}
		}
		throw "not match any path.";
		return -1;
	}

	int getIndex(Path* p) {
		for(int i=0;i<paths.size();i++) {
			if (paths[i] == p) {
				return i;
			}
		}
		throw "not match any path.";
		return -1;
	}

	Paths* getPathFrom(string c) {
		Paths* ps = new Paths();
		for (int i=0; i<paths.size(); i++) {
			if (paths[i]->c1 == c || paths[i]->c2 == c) {
				ps->push(paths[i]);
			}
		}
		return ps;
	}

	Paths* popPathFrom(string c) {
		Paths* ps = getPathFrom(c);
		for(int i=0;i<ps->size();i++) {
			this->remove(ps->at(i));
		}
		return ps;
	}


	Paths* clone() {
		Paths* ps = new Paths();
		for (int i=0;i<this->size();i++) {
			ps->push(paths[i]->clone());
		}
		return ps;
	}

	void push(Path* p) {
		paths.push_back(p);
	}

	int size() {
		return paths.size();
	}

	void sortByCost() {
		std::sort(paths.begin(), paths.end(), sortByCostComparer);
	}

	Path* operator[](int i) {
		return at(i);
	}

	Path* at(int i) {
		return paths[i];
	}

	void remove(Path* p) {
		paths.erase(std::remove(paths.begin(), paths.end(), p), paths.end());
	}

	void list() {
		for(int i=0;i<paths.size();i++) {
			Path* p = paths[i];
			cout << p->c1 << " " << p->c2 << " " << p->cost << endl;
		}
	}
};

class SpanningPaths : public Paths {
public:
	bool existRingIfAdd(Path* p) {
		if (this->size() == 0) {
			return false;
		}

		Paths *tmp_path = this->clone();
		string t;

		// BFS
		vector<string> sv, ev;
		sv.push_back(p->c1);
		sv.push_back(p->c2);
		while ( !sv.empty() ) {
			t = sv.back();
			sv.pop_back();
			if ( std::find(ev.begin(), ev.end(), t) != ev.end() ) {
				delete tmp_path;
				return true;
			} else {
				ev.push_back(t);
				Paths* ps = tmp_path->popPathFrom(t);
				for (int i=0;i<ps->size();i++) {
					Path* p = ps->at(i);
					if (p->c1 == t) {
						sv.push_back(p->c2);
					} else {
						sv.push_back(p->c1);
					}
				}
				delete ps;
			}
		}
		delete tmp_path;

		return false;
	}
};


int main(int argc, char** argv)  {

	int n, m;
	int val;
	string c, c1, c2;

	// initialize & input
	cin>>n>>m;
	Citys citys(n);
	Paths paths;
	SpanningPaths spanning_path;

	for(int i=0;i<n;i++) {
		cin >> c;
		citys.setName(i, c);
	}

	for(int i=0;i<m;i++) {
		cin>>c1>>c2>>val;
		paths.push(new Path(c1, c2, val));
	}

	// kruskal's algo
	paths.sortByCost();
	for (int i=0; i<paths.size(); i++) {
		Path* p = paths.at(i);
		if (!spanning_path.existRingIfAdd(p)) {
			spanning_path.push(p->clone());
		}
	}

	int total_cost = 0;
	for (int i=0; i<spanning_path.size(); i++) {
		Path* p = spanning_path.at(i);
		cout << "(" << p->c1 << " " << p->c2 << ") ";
		total_cost += p->cost;
	}
	cout << "\n" << total_cost << endl;

//	paths.list();
//	spanning_path.list();

	return 0;
}

//input:
//	6 9
//	C1 C2 C3 C4 C5 C6
//	C1 C2 1
//	C1 C4 7
//	C2 C3 3
//	C2 C4 6
//	C2 C5 4
//	C3 C5 5
//	C3 C6 9
//	C4 C5 3
//	C5 C6 8
//
//output:
//	(C1 C2) (C2 C3) (C4 C5) (C2 C5) (C5 C6)
//	19

