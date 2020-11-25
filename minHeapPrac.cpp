
#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <algorithm> // std::min
#include <unordered_map>
#include <queue>

using namespace std;

// class sig
struct sig // copy and paste this
{
	// public:
	double cost;
	int time;
	char vert;
};

class comp //	and this
{
public:
	bool operator()(sig const &p1, sig const &p2)
	{
		if (p1.cost != p2.cost)
		{
			return p1.cost > p2.cost;
		}
		else
		{
			if (p1.time != p2.time)
			{
				return p1.time > p2.time;
			}
			else
			{
				return p1.vert > p2.vert;
			}
		}
	}
};

int main()
{
	vector<sig> test;
	sig t;
	t.cost = 0;
	t.time = 0;
	t.vert = '0';
	test.push_back(t);

	// sig t;
	t.cost = 2;
	t.time = 4;
	t.vert = '1';
	test.push_back(t);

	// sig t;
	t.cost = 4;
	t.time = 2;
	t.vert = '4';
	test.push_back(t);

	// sig t;
	t.cost = 4;
	t.time = 5;
	t.vert = '0';
	test.push_back(t);

	// sig t;
	t.cost = 5;
	t.time = 6;
	t.vert = '2';
	test.push_back(t);

	// sig t;
	t.cost = 6;
	t.time = 5;
	t.vert = '5';
	test.push_back(t);

	// sig t;
	t.cost = 3;
	t.time = 9;
	t.vert = '4';
	test.push_back(t);

	t.cost = 10;
	t.time = 3;
	t.vert = '5';
	test.push_back(t);

	// sig t;
	t.cost = 10;
	t.time = 3;
	t.vert = '1';
	test.push_back(t);

	// sig t;
	t.cost = 9;
	t.time = 3;
	t.vert = '5';
	test.push_back(t);

	// sig t;
	t.cost = 7;
	t.time = 9;
	t.vert = '6';
	test.push_back(t);

	// sig t;
	t.cost = 10;
	t.time = 6;
	t.vert = '6';
	test.push_back(t);

	// sig t;
	t.cost = 15;
	t.time = 4;
	t.vert = '2';
	test.push_back(t);

	// sig t;
	t.cost = 13;
	t.time = 4;
	t.vert = '6';
	test.push_back(t);

	// sig t;
	t.cost = 12;
	t.time = 4;
	t.vert = '3';
	test.push_back(t);

	// sig t;
	t.cost = 13;
	t.time = 5;
	t.vert = '2';
	test.push_back(t);

	priority_queue<sig, vector<sig>, comp> lol; //	and this

	for (auto el : test)
	{

		lol.push(el);

		cout << "( " << el.cost << "," << el.time << " ) : " << el.vert << "\n";
	}

	while (!lol.empty())
	{
		auto tlol = lol.top();

		lol.pop();

		cout << "Current val:\t(" << tlol.cost << "," << tlol.time << ") : " << tlol.vert << endl;
	}
}