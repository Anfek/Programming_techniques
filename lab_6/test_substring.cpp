#include "substring.h"

int main() {
    string sentence = "Hello, world! It's great to live in there!";

    cout << "Our text: " << sentence << endl;

    cout << "\n\nBoyer-Moore algorithm is running..." << endl;
    cout << "Searching for 'there': " << endl;
    BoyerMoore(sentence, "there") ? cout << "exists" << endl : cout << "not found" << endl;

    cout << "Searching for 'thee': " << endl;
    BoyerMoore(sentence, "thee") ? cout << "exists" << endl : cout << "not found" << endl;

    cout << "Searching for 'Hell': " << endl;
    BoyerMoore(sentence, "Hell") ? cout << "exists" << endl : cout << "not found" << endl;

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    cout << "\n\nRabin-Karp algorithm is running..." << endl;
    cout << "Searching for 'there': " << endl;
    RabinKarp(sentence, "there") ? cout << "exists" << endl : cout << "not found" << endl;

    cout << "Searching for 'thee': " << endl;
    RabinKarp(sentence, "thee") ? cout << "exists" << endl : cout << "not found" << endl;

    cout << "Searching for 'Hell': " << endl;
    RabinKarp(sentence, "Hell") ? cout << "exists" << endl : cout << "not found" << endl;

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    cout << "\n\nKnuth-Morris-Pratt algorithm is running..." << endl;
    cout << "Searching for 'there': " << endl;
    KnuthMorrisPratt(sentence, "there") ? cout << "exists" << endl : cout << "not found" << endl;

    cout << "Searching for 'thee': " << endl;
    KnuthMorrisPratt(sentence, "thee") ? cout << "exists" << endl : cout << "not found" << endl;

    cout << "Searching for 'Hell': " << endl;
    KnuthMorrisPratt(sentence, "Hell") ? cout << "exists" << endl : cout << "not found" << endl;
    
    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    string sentence_A = "AAAAAAAAAAAAAA";

    cout << "Our text: " << sentence_A << endl;

    cout << "\n\nBoyer-Moore algorithm is running..." << endl;
    cout << "Searching for 'AAA': " << endl;
    BoyerMoore(sentence_A, "AAA") ? cout << "exists" << endl : cout << "not found" << endl;

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    cout << "\n\nRabin-Karp algorithm is running..." << endl;
    cout << "Searching for 'AAA': " << endl;
    RabinKarp(sentence_A, "AAA") ? cout << "exists" << endl : cout << "not found" << endl;

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    cout << "\n\nKnuth-Morris-Pratt algorithm is running..." << endl;
    cout << "Searching for 'AAA': " << endl;
    KnuthMorrisPratt(sentence_A, "AAA") ? cout << "exists" << endl : cout << "not found" << endl;
}