#include "ladder.h"
#include <string>
#include <iostream>
#include <unordered_set>
#include <fstream>
#include <queue>
#include <set>
#include <vector>

#define my_assert(e) {std::cout << #e << ((e) ? " passed": " failed") << endl;}
using namespace std;

void error(string word1, string word2, string msg){
    std::cout << word1 << word2 << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int str1len = str1.length();
    int str2len = str2.length();
    if(abs(str1len - str2len) > d) return false;

    int count = 0;
    if(str1len == str2len){
        for(int i = 0; i < str1len; ++i){
            if(str1[i] != str2[i]){
                ++count;
                if(count > d) return false;
            }
        }
    } else{
        int i = 0, j = 0;
        while (i < str1len && j < str2len) {
            if (str1[i] != str2[j]) {
                ++count;
                if (count > d) return false;
                if (str1len > str2len) ++i;
                else if (str2len > str1len) ++j;
                else {
                    ++i;
                    ++j;
                }
            } 
            else {
                ++i;
                ++j;
            }
        }
        if (i < str1len || j < str2len) ++count;
    }
    return count <= d;
}

bool is_adjacent(const string& word1, const string& word){
    return edit_distance_within(word1, word, 1);

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    unordered_set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(const string w: word_list){
            if (is_adjacent(last_word, w)){
                if(visited.find(w) == visited.end()){
                    visited.insert(w);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(w);
                    if(w == end_word) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};

}

void load_words(set<string> & word_list, const string& file_name){
    std::ifstream file(file_name);
    string word;
    while(file >> word)
        word_list.insert(word);
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    int len = ladder.size();
    if(len == 0){
        std::cout << "No word ladder found." << std::endl;
        return;
    }
    for(int i = 0; i < len; ++i)
        std::cout << " " << ladder[i];
    std::cout << std::endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}