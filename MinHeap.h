#include <queue>

template <typename OBJ>	//	this object must be either a struct or object

class minHeap
{

private:
	class comp
	{
	public:
		bool operator()(OBJ const &p1, OBJ const &p2)
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

	priority_queue<OBJ, vector<OBJ>, comp> pq;

	public:

	void push(OBJ x)
	{
		pq.push(x);
	}

	void pop()
	{
		pq.pop();
	}

	bool empty()
	{
		return pq.empty();
	}

	OBJ top()
	{
		return pq.top();
	}
};
