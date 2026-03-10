// Order Statistic Set

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
	
// To declare:
// ord_set<int> s;

// Normal set operations work:
// for (auto i : s) cout << i << endl;
// cout << s.size() << endl;

// k-th smallest element O(log|s|):
// k = 0: smallest element
// cout << *s.find_by_order(k) << endl;

// How many elements are smaller than k O(log|s|):
// cout << s.order_of_key(k) << endl;

// To create a multiset, you need to
// use ord_set<pair<int, int>> where the
// second parameter is something to differentiate
// equal elements.
// s.order_of_key({k, -INF}) will return the
// number of elements < k