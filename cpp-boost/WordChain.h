#include <iostream>
#include <chrono>
#include <string>
#include <boost/container/set.hpp>
#include <boost/container/deque.hpp>

using namespace std;
using namespace boost::container;

class WordChain
{
    string _beginning, _end;
    set<string>* _dict;
    deque<deque<string>> _queue;
    std::vector<std::string> _words;

    WordChain(set<string>* dict, string beginning, string end) 
        : _dict(dict), _beginning(beginning), _end(end)
    {        
    }

    deque<string> processQueue() {
        deque<string> emptyChain;

        while (_queue.size() > 0) {
            cout << "Queue size is " << _queue.size() << endl;

            auto chain = _queue.front();
            _queue.pop_front();
            
            if (chain.front() == _end)
                return chain;

            if (chain.size() > 10) {
                cerr << "Chain is getting long. Stopping." << endl;
                return chain;
            }           

            addNeighbors(chain);
        }

        return emptyChain;
    }

    bool areNeighbors(string a, string b) {
        if (a.size() != b.size())
            return false;

        int differentLetters = 0;

        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                differentLetters++;

        return differentLetters == 1;
    }

    bool isInChain(deque<string>& chain, string word) {
        return find(chain.begin(), chain.end(), word) != chain.end();
    }

    void initializeQueue() {
        deque<string> chain;
        chain.push_front(_beginning);
        _queue.push_back(chain);
    }

    void clear(deque<deque<string>> &q)
    {
       deque<deque<string>> empty;
       swap(q, empty);
    }

    void addNeighbors(deque<string>& chain) {
        auto currentEnd = chain.front();

        for (auto word : *_dict) {
            if (areNeighbors(currentEnd, word) && !isInChain(chain, word)) {
                deque<string> newChain(chain);
                newChain.push_front(word);

                if (word == _end) {
                    clear(_queue);
                    _queue.push_back(newChain);
                    return;
                }

                _queue.push_back(newChain);
            }
        }    
    }

    void findWords() {
        _words = { };

        if (_beginning == "" || _end == "" 
            || _beginning.size() != _end.size()
            || _dict->find(_beginning) == _dict->end()
            || _dict->find(_end) == _dict->end())
            return;
        else if (_beginning == _end)
            _words = { _beginning };
        else if (areNeighbors(_beginning, _end))
            _words = { _beginning, _end };
        else {
            initializeQueue();
            auto wordStack = processQueue();

            while (wordStack.size() > 0) {
                std::vector<string>::iterator it;
                it = _words.begin();
                _words.insert(it, wordStack.front());
                wordStack.pop_front();
            }
        }
    }

    public:
    static WordChain create(set<string>* dict, string beginning, string end) {
        auto t1 = std::chrono::high_resolution_clock::now();

        auto chain = WordChain(dict, beginning, end);
        chain.findWords();

        auto t2 = std::chrono::high_resolution_clock::now();

        cout << "Finding the word chain took "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
                  << " milliseconds" << endl;

        return chain;
    }
    
    size_t getLength() {
        return _words.size();
    }
    
    std::vector<string> getWords() {
        return _words;
    }

    void print() {
        for (int i=0; i<_words.size(); i++) {
            if (i > 0)        
                cout << ", ";

            cout << _words[i];
        }

        cout << endl;
    }
};
