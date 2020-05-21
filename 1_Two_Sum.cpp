// 1. Two Sum.cpp 
// date: 21.5.2020
///////////////////////////////////////////////////////////////////////////////////////////////
// Chalange Description                                                                     ///
///////////////////////////////////////////////////////////////////////////////////////////////
/* Easy
Given an array of integers, return indices of the two numbers such that 
they add up to a specific target.

You may assume that each input would have exactly one solution, 
and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

///////////////////////////////////////////////////////////////////////////////////////////////
// Submissions                                                                              ///
///////////////////////////////////////////////////////////////////////////////////////////////
/*
twoSum_BruteForce:                      Runtime : 896 ms, Memory Usage :  9.3 MB
twoSum_OnePassHashTableToModernCPP:     Runtime :  16 ms, Memory Usage : 10.3 MB (faster than 62.80 % and less than 29.70% of C++ online submissions for Two Sum)
*/

#include <iostream>
#include <vector>
#include <algorithm>        // for copy()
#include <iterator>         // for ostream_iterator<>
#include <unordered_map>    // for unordered_map<>
using std::vector;
using std::unordered_map;

///////////////////////////////////////////////////////////////////////////////////////////////
// Approach 1: Brute Force. Time complexity : O(n^2)O(n2). Space complexity : O(1)O(1).     ///
///////////////////////////////////////////////////////////////////////////////////////////////
/*
Approach 1: Brute Force
The brute force approach is simple. Loop through each element xx and find if there is another 
value that equals to target - xtarget−x.

Complexity Analysis

Time complexity : O(n^2)O(n2). 
For each element, we try to find its complement by looping through the rest of array 
which takes O(n)O(n) time. 
Therefore, the time complexity is O(n^2)O(n2).

Space complexity : O(1)O(1).
*/
vector<size_t> twoSum_BruteForce( vector<int>& nums, int target ) {

    for( size_t i = 0; i < nums.size(); ++i )
        for( size_t j = 0; j < nums.size(); ++j )
            if( (i != j ) && ( ( nums[i] + nums[j] ) == target ) )
                return {i, j};
    return {}; // same as: return vector<int>();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Approach 2: Two-pass Hash Table. Time complexity : O(n)O(n). Space complexity : O(n)O(n). //
///////////////////////////////////////////////////////////////////////////////////////////////
/*
Approach 2: Two-pass Hash Table
To improve our run time complexity, 
we need a more efficient way to check if the complement exists in the array. 
If the complement exists, we need to look up its index. 
What is the best way to maintain a mapping of each element in the array to its index? 
A hash table.

We reduce the look up time from O(n)O(n) to O(1)O(1) by trading space for speed. 
A hash table is built exactly for this purpose, it supports fast look up in near constant time. 
I say "near" because if a collision occurred, a look up could degenerate to O(n)O(n) time. 
But look up in hash table should be amortized O(1)O(1) time as long as the hash function 
was chosen carefully.

A simple implementation uses two iterations. 
In the first iteration, we add each element's value and its index to the table. 
Then, in the second iteration we check if each element's 
complement (target - nums[i]target−nums[i]) exists in the table. 
Beware that the complement must not be nums[i]nums[i] itself!

// Java example:
public int[] twoSum(int[] nums, int target) {
    Map<Integer, Integer> map = new HashMap<>();
    for (int i = 0; i < nums.length; i++) {
        map.put(nums[i], i);
    }
    for (int i = 0; i < nums.length; i++) {
        int complement = target - nums[i];
        if (map.containsKey(complement) && map.get(complement) != i) {
            return new int[] { i, map.get(complement) };
        }
    }
    throw new IllegalArgumentException("No two sum solution");
}

Complexity Analysis:

Time complexity : O(n)O(n). 
We traverse the list containing nn elements exactly twice. 
Since the hash table reduces the look up time to O(1)O(1), 
the time complexity is O(n)O(n).

Space complexity : O(n)O(n). 
The extra space required depends on the number of items 
stored in the hash table, which stores exactly nn elements.
*/

///////////////////////////////////////////////////////////////////////////////////////////////
// Approach 2: Two-pass Hash Table: Hashmap solution to C, top 1%, 4ms runtime.             ///
///////////////////////////////////////////////////////////////////////////////////////////////
struct node 
{
    int key;
    int val;
    struct node* next;
};

struct table 
{
    int size;
    struct node** list;
};

struct table* createTable( int size ) 
{
    struct table* t = ( struct table* )malloc( sizeof( struct table ) );
    t->size = size;
    t->list = ( struct node** )malloc( sizeof( struct node* ) * size );
    int i;
    for( i = 0; i < size; i++ )
        t->list[i] = NULL;
    return t;
}

int hashCode( struct table* t, int key ) 
{
    if( key < 0 )
        return -( key % t->size );
    return key % t->size;
}

void insert( struct table* t, int key, int val ) 
{
    int pos = hashCode( t, key );
    struct node* list = t->list[pos];
    struct node* newNode = ( struct node* )malloc( sizeof( struct node ) );
    struct node* temp = list;
    while( temp ) 
    {
        if( temp->key == key ) 
        {
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->val = val;
    newNode->next = list;
    t->list[pos] = newNode;
}

int lookup( struct table* t, int key ) 
{
    int pos = hashCode( t, key );
    struct node* list = t->list[pos];
    struct node* temp = list;
    while( temp ) 
    {
        if( temp->key == key ) 
            return temp->val;
        
        temp = temp->next;
    }
    return -1;
}

int* twoSum_TwoPassHashTableToC( int* nums, int numsSize, int target, int* returnSize ) 
{
    struct table* t = createTable( numsSize );
    int i;
    *returnSize = 2;
    int* result = (int*)malloc( sizeof( int ) * *returnSize );
    for( i = 0; i < numsSize; i++ ) 
        insert( t, nums[i], i );

    for( i = 0; i < numsSize; i++ ) 
    {
        int complement = target - nums[i];
        if( lookup( t, complement ) != -1 && lookup( t, complement ) != i ) 
        {
            result[0] = lookup( t, complement );
            result[1] = i;
        }
    }
    free( t );

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Approach 2: Two-pass Hash Table: Modern C++.                                             ///
///////////////////////////////////////////////////////////////////////////////////////////////
vector<int> twoSum_TwoPassHashTableToModernCPP( vector<int>& nums, int target ) 
{
    unordered_map<int, int> map;
    for( size_t i = 0; i < nums.size(); ++i ) 
        map.emplace( std::make_pair( nums.at( i ), i ) );
    
    for( size_t i = 0; i < nums.size(); ++i ) 
    {
        const auto mit = map.find( target - nums.at( i ) );
        if( mit != map.end() && (int)i != mit->second ) 
            return { (int)i, mit->second };
    }
    return vector<int>();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Approach 3: One-pass Hash Table. Time complexity : O(n)O(n). Space complexity : O(n)O(n).///
///////////////////////////////////////////////////////////////////////////////////////////////
/*
Approach 3: One-pass Hash Table
It turns out we can do it in one-pass. 
While we iterate and inserting elements into the table, 
we also look back to check if current element's complement 
already exists in the table. If it exists, we have found 
a solution and return immediately.

// Java example:
public int[] twoSum(int[] nums, int target) {
    Map<Integer, Integer> map = new HashMap<>();
    for (int i = 0; i < nums.length; i++) {
        int complement = target - nums[i];
        if (map.containsKey(complement)) {
            return new int[] { map.get(complement), i };
        }
        map.put(nums[i], i);
    }
    throw new IllegalArgumentException("No two sum solution");
}

// Clean Python One-Pass solution:
def twoSum(nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: List[int]
    """
    seen = {}
    for i, v in enumerate(nums):
        remaining = target - v
        if remaining in seen:
            return [seen[remaining], i]
        seen[v] = i
    return []

Complexity Analysis:

Time complexity : O(n)O(n). 
We traverse the list containing nn elements only once. 
Each look up in the table costs only O(1)O(1) time.

Space complexity : O(n)O(n). 
The extra space required depends on the number of items 
stored in the hash table, which stores at most nn elements.

*/

///////////////////////////////////////////////////////////////////////////////////////////////
// Approach 3: One-pass Hash Table: Modern C++.                                             ///
///////////////////////////////////////////////////////////////////////////////////////////////
vector<size_t> twoSum_OnePassHashTableToModernCPP( const vector<int>& nums, int target )
{
    unordered_map<int, size_t> map; // map<key, pos>
    for( size_t i = 0; i < nums.size(); ++i ) 
    {
        int complement = target - nums.at( i );
        // "map.find() Complexity = Amortized constant on average, worst case linear in the size of the container."
        // const auto it = map.find( target - nums.at( i ) );                                  // same as:
        // const unordered_map<int, size_t>::iterator it = map.find( target - nums.at( i ) );  // same as:
         
        unordered_map<int, size_t>::const_iterator it = map.find( complement );
        // unordered_map<Key, T> explanation:
        /*
        unordered_map<Key, T>::iterator it;
        ( *it ).first;             // the key value (of type Key)
        ( *it ).second;            // the mapped value (of type T)
        ( *it );                   // the "element value" (of type pair<const Key,T>)

        it->first;               // same as (*it).first   (the key value)
        it->second;              // same as (*it).second  (the mapped value) 

        */

        if( it != map.end() && i != it->second )  
        {
            size_t first_number_pos  = it->second;
            size_t second_number_pos = i;
            return { first_number_pos, second_number_pos };
        }

        map.emplace( std::make_pair( nums.at( i ), i ) );
    }
    return vector<size_t>(); // same as return {};
}

/*/////////////////////////////////////////////////////////////
//        auxiliary function: operator<< vector<T>           //
/////////////////////////////////////////////////////////////*/
template <typename T>
std::ostream& operator<< ( std::ostream& out, const std::vector<T>& v ) {
    if( !v.empty() ) {
        out << '[';
        std::copy( v.begin(), v.end(), std::ostream_iterator<T>( out, ", " ) );
        out << "\b\b]";
    }
    return out;
}

int main()
{
    vector<int> nums = { 2, 7, 11, 15, 3, 1, 9 };
    int target = 13;


    std::cout << twoSum_BruteForce(nums, target) << std::endl;

    std::cout << twoSum_OnePassHashTableToModernCPP( nums, target ) << std::endl;
}
