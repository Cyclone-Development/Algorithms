// GrahamScan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define point std::pair<int,int>

point origin;

long long crossproduct(const point& a, const point& b);
bool convex(const point& a, const point& b, const point& c);
bool compareAngles(const point& a, const point& b);

std::vector<point> convex_hull(std::vector<point> points) {
	int n = points.size();

	if (n < 3)
		return points;

	int index_lowest = 0;

	for (int i = 1; i < n; ++i) {
		if (std::make_pair(points[i].second, -points[i].first) <
			std::make_pair(points[index_lowest].second, -points[index_lowest].first)) {
			index_lowest = i;
		}
	}
	std::swap(points[0], points[index_lowest]);
	origin = points[0];

	std::sort(points.begin() + 1, points.end(), compareAngles);

	std::vector<point> st;
	st.push_back(points[0]);
	st.push_back(points[1]);

	int pointer = 2;

	while (pointer < n) {
		point a = st[st.size() - 2];
		point b = st[st.size() - 1];
		point c = points[1];
		if (convex(a, b, c)) {
			st.push_back(c);
			++pointer;
		}
		else {
			st.pop_back();
			if (st.size() < 2) {
				st.push_back(c);
				++pointer;
			}
		}
	}
	point a = st[st.size() - 2];
	point b = st[st.size() - 1];
	point c = st[0];
	if (!convex(a, b, c)) {
		st.pop_back();
	}
	return st;
}

long long crossproduct(const point& a, const point& b) {
	return (a.first * b.second) - (a.second * b.first);
}

bool convex(const point& a, const point& b , const point& c) {
	const point ab = { b.first - a.first , b.second - a.second };
	const point bc = { c.first - b.first , c.second - b.second };

	return crossproduct(ab, bc) > 0;
}

bool compareAngles(const point& a, const point& b) {
	if (convex(origin, a, b)) {
		return true;
	}
	else if (convex(origin, b, a)) {
		return false;
	}
	else {
		const int distA = std::abs(a.first - origin.first) + std::abs(a.second - origin.second);
		const int distB = std::abs(b.first - origin.first) + std::abs(b.second - origin.second);

		return distA < distB;
	}
}

int main()
{
   


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
