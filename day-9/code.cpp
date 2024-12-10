#include <bits/stdc++.h>
using namespace std;

long long getCost (int index, long long len, long long id){
	// calculate the cost if we put file 'id' starting from position 'index' with length 'len'
	return id * (((2 * index + len - 1) * len) / 2);
}

void part1 (string &line){

	vector<int> blockSizes;
	for (char c : line){
		blockSizes.push_back(c - '0');
	}

	size_t leftPointer = 0;
	size_t rightPointer = blockSizes.size() - 1;

	if (rightPointer % 2 == 1){
		// remove redundancy at the end
		rightPointer--;
	}

	long long checkSum = 0;
	int index = 0; // keeping track of writing index

	while (leftPointer <= rightPointer){
		if (leftPointer % 2 == 0){
			checkSum += getCost(index,blockSizes[leftPointer],leftPointer / 2);
			index += blockSizes[leftPointer];
			leftPointer++;
		}
		else if (rightPointer % 2 == 1){
			rightPointer--;
		}
		else {
			if (blockSizes[rightPointer] >= blockSizes[leftPointer]){
				// fill all of the empty spaces
				checkSum += getCost(index,blockSizes[leftPointer],rightPointer / 2);
				index += blockSizes[leftPointer];

				blockSizes[rightPointer] -= blockSizes[leftPointer];
				if (blockSizes[rightPointer] == 0){
					rightPointer--;
				}
				leftPointer++;
			}
			else {
				// fill partially
				checkSum += getCost(index,blockSizes[rightPointer], rightPointer / 2);
				index += blockSizes[rightPointer];

				blockSizes[leftPointer] -= blockSizes[rightPointer];
				rightPointer--;
			}
		}
	}

	cout << checkSum << "\n";
}

// Using Segment Tree for Prefix Min, Point Update, each pos is equivalent to a block, storing the empty space size
typedef pair<int,int> option;

class SegmentTree{
private:
	vector<option> st;

	int n;

	void build (int node, int tl, int tr){
		if (tl == tr){
			st[node] = make_pair(0,tl);
			return;
		}
		int tm = (tl + tr) >> 1;
		build(node << 1,tl,tm);
		build(node << 1 | 1,tm + 1,tr);
		st[node] = max(st[node << 1],st[node << 1 | 1]);
	}

public:

	SegmentTree (int sz){
		n = sz;
		st.resize(n << 2);
		build(1,1,size());
	}

	int size(){
		return n;
	}

	void update (int pos, int value, int node, int tl, int tr){
		if (tl == tr){
			st[node] = make_pair(value,pos);
			return;
		}
		int tm = (tl + tr) >> 1;
		if (pos <= tm){
			update(pos,value,node << 1,tl,tm);
		}
		else {
			update(pos,value,node << 1 | 1,tm + 1,tr);
		}
		st[node] = max(st[node << 1],st[node << 1 | 1]);
	}

	option get (int size, int node, int tl, int tr){
		if (st[node].first < size){
			// every empty blocks have smaller sizes
			return make_pair(0,-1);
		}
		
		if (tl == tr){
			return st[node];
		}

		int tm = (tl + tr) >> 1;
		if (st[node << 1].first >= size){
			return get(size,node << 1,tl,tm);
		}
		else {
			return get(size,node << 1 | 1,tm + 1,tr);
		}
	}

};

void part2 (string &line){
	long long checkSum = 0;
	
	vector<int> blockSizes; // size of each block
	vector<int> startingIndex; // starting index for each block

	SegmentTree emptySpaces(int(line.size()));

	for (int i = 0 ; i < line.size() ; i++){
		int dig = line[i] - '0';

		if (startingIndex.size() == 0){
			startingIndex.push_back(0);
		}
		startingIndex.push_back(startingIndex.back() + dig);
		blockSizes.push_back(dig);

		if (i % 2 == 1){
			// empty space
			emptySpaces.update(i + 1,dig,1,1,emptySpaces.size());
		}
	}

	for (int i = line.size() - 1 ; i >= 0 ; i--){
		if (i % 2 == 1){
			// encounter an empty space -> discard
			emptySpaces.update(i + 1,0,1,1,emptySpaces.size());
		}
		else {
			// encounter a file -> check if we can move it
			option cur = emptySpaces.get(blockSizes[i],1,1,emptySpaces.size());

			if (cur.first <= 0){
				// keep in the old place
				checkSum += getCost(startingIndex[i],blockSizes[i],i/2);
				//cout << "keep " << i / 2 << " at " << startingIndex[i] << endl;
			}
			else {
				// can fill
				checkSum += getCost(startingIndex[cur.second - 1],blockSizes[i],i/2);

				startingIndex[cur.second - 1] += blockSizes[i];

				cur.first -= blockSizes[i];
				emptySpaces.update(cur.second,cur.first,1,1,emptySpaces.size());
			}
		}
	}

	cout << checkSum << "\n";

}

int main() {
	string line;
	getline(cin,line);
	part1(line);
	part2(line);
}

