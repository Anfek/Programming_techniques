#include <iostream>
#include <vector>

using namespace std;

vector<int> to_arr(string image) {
    vector<int> image_arr;
    
    image_arr.push_back(1);                                                                         //if penultimate element from arr
    for(int i = image.size() - 2; i >= 0; i--) {
        for(int j = image.size() - 2; j > i; j--) {
            if(image[i] == image[j]) {
                image_arr.insert(image_arr.begin(), image.size() - 1 - j);                          //if there's the same element before
                break;
            }
            if(j - 1 == i) { image_arr.insert(image_arr.begin(), image.size() - 1 - i); }           //in the other cases
        }
    }

    for(int i = image.size() - 2; i >= 0; i--) {                                                    //for the last element
        if(image[image.size() - 1] == image[i]) {
            image_arr.push_back(image.size() - 1 - i);
            break;
        }
        if(i == 0) { image_arr.push_back(image.size() - 1); }
    }
    return image_arr;
}

int BoyerMoore(string text, string image) {
    vector<int> image_arr = to_arr(image);
    int exists = 0;
    /*
    for(int i = 0; i < image_arr.size(); i++) {
        cout << image_arr[i] << " ";
    }
    */

    int k = image.size() - 1;
    while(k < text.size()) {
        int i = image.size() - 1;
        int count = 0;
        
        while(image[i] == text[k] && i >= 0) {
            if(i == 0) { 
                cout << "Found our substring: [" << k << ", " << k + image.size() - 1 << "]" << endl; 
                exists = 1;
            }
            i--;
            k--;
            count++;
        }

        k += count;
        
        for(int j = 0; j < image.size(); j++) {
            if(image[j] == text[k]) { 
                k += image_arr[j]; 
                break;
            } 
            if(j == image.size() - 1) { k += image.size(); }
        }
    }
    return exists;
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
const int Q = 256;
const int B = 13;

int get_hash(string image) {
    int strLen = image.size();
    int result = 0;

    for(int i = 0; i < strLen; i++) { result = (result * B + (int) image[i]) % Q; }
    
    return result;
}

int RabinKarp(string text, string image) {
    int imageLen = image.size();
    int textLen = text.size();
    int multiplier = 1;
    int exists = 0;
    
    for(int i = 1; i < imageLen; i++) { multiplier = (multiplier * B) % Q; }

    int image_hash = get_hash(image);
    /*
    cout << "Image hash: " << image_hash << endl;
    cout << text.substr(0, imageLen) << endl;
    */
   
    int text_hash = get_hash(text.substr(0, imageLen));

    int count = 0;

    for(int i = 0; i < textLen - imageLen + 1; i++) {
        /*
        cout << "Text hash: " << text_hash << endl;
        cout << text.substr(i, imageLen) << endl;
        */
        if(image_hash == text_hash && text.substr(i, imageLen) == image) { 
            cout << "Found our substring: [" << i << ", " << i + image.size() - 1 << "]" << endl;
            exists = 1;
        }

        if(i < textLen - imageLen) {
            text_hash = ((text_hash - (int) text[i] * multiplier) * B + (int) text[i + imageLen]) % Q;
            if(text_hash < 0) { text_hash += Q; }
            
        }
    }
    return exists;
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
vector<int> first_step(string image) {
    vector<int> pi(image.size());
    pi[0] = 0;
    
    int i = 1, j = 0;
    while(i < image.size()) {
        if(image[i] != image[j]) {
            if(j == 0) {
                pi[i] = 0;
                i++;
            } else {
                j = pi[j - 1];
            }
        } else {
            pi[i] = j + 1;
            i++;
            j++;
        }
    }
    return pi;
}

int KnuthMorrisPratt(string text, string image) {
    vector<int> pi = first_step(image);
    int exists = 0;
    /*
    for(int i = 0; i < pi.size(); i++) {
        cout << pi[i] << " ";
    }
    */

    int k = 0, l = 0;
    while(k < text.size()) {
        if(text[k] == image[l]) {
            k++;
            l++;
            if(l == image.size()) {
                cout << "Found our substring: [" << k - (image.size()) << ", " << k - 1 << "]" << endl;
                exists = 1;
            }
        } else if(text[k] != image[l] && l != 0) {
            l = pi[l - 1];
        } else if(text[k] != image[l] && l == 0) {
            k++;
        }
    }
    return exists;
}