#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <iostream>
#include <vector>

using namespace std;

//if returns 0 it means "no string found"
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
int BoyerMoore(string, string);

int RabinKarp(string, string);

int KnuthMorrisPratt(string, string);

#endif