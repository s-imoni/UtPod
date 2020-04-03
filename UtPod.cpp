//
// Created by simon on 3/30/2020.
//

#include "UtPod.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>

UtPod::UtPod() {
    songs = NULL;
    memSize = MAX_MEMORY;
}

UtPod::UtPod(int size) {
    songs = NULL;
    if(size > MAX_MEMORY || size <= 0)
        memSize = MAX_MEMORY;
    else
        memSize = size;
}

int UtPod::addSong(Song const &s) {
    int memRemaining = getRemainingMemory();
    if(memRemaining < s.getSize()){
        return NO_MEMORY;
    }
    SongNode* temp = new SongNode;
    temp->s = s;
    temp->next = songs;
    songs = temp;
    return SUCCESS;
}

int UtPod::removeSong(Song const &s) {
    SongNode *head = songs;
    //If removing first song
    if(head->s == s){
        songs = head->next;
        delete head;
        return SUCCESS;
    }
    //If songs in the middle or at the end
    else{
        SongNode *prev = NULL;
        while(head!= NULL){
            // Song found
            if(head->s == s){
                prev->next = head->next;
                delete head;
                return SUCCESS;
            }
            // Continue loop
            else {
                prev = head;
                head = head->next;
            }
        }

    }
    // Song not found
    return NOT_FOUND;
}

void UtPod::shuffle() {
    // Seeds random with currentTime
    unsigned int currentTime = (unsigned) time(0);
    srand(currentTime);
    int songCount = 0;
    SongNode *head = songs;

    // Counts number of songs
    while (head != NULL){
        songCount++;
        head = head->next;
    }

    // Generates two random numbers within range [0:songCount)
    // Swaps songs at the indexes, songCount*2 times
    for(int i = 0; i < songCount*2; i++){
        int randIndexOne = rand()%songCount;
        int randIndexTwo = rand()%songCount;
        swap(randIndexOne, randIndexTwo);
    }
}

void UtPod::showSongList() {
    SongNode *head = songs;
    while (head != NULL){
        //Traverses through linked list from head to Null and prints title, artist, size in MB
        cout << head->s.getTitle() << ", " << head->s.getArtist() << ", " << head->s.getSize() << " MB" << endl;
        head = head->next;
    }
}

void UtPod::sortSongList() {
    //Created nested loop to find the first smallest element starting from first index, then swapping
    //Traverses through linked list to find the next smallest element starting from the next index, then swapping
    //Sort is completed when head index reaches NULL
    SongNode *head = songs;
    while(head != NULL){
        SongNode *innerLoop = head;
        SongNode *smallest = head;
        while(innerLoop != NULL){
            if(smallest->s > innerLoop->s){
                smallest = innerLoop;
            }
            innerLoop = innerLoop->next;
        }
        Song tempSong = head->s;
        head->s = smallest->s;
        smallest->s = tempSong;
        head = head->next;
    }
}

void UtPod::clearMemory() {
    //Frees all SongNode pointers in linked list
    SongNode *head = songs;
    SongNode *temp = NULL;
    while (head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
    songs = NULL;
}

int UtPod::getRemainingMemory() {
    //Calculates sum of memory in the UtPod and subtracts from the total memory size
    //Traverse through linked list to calculate the sum
    int totalMem = 0;
    int remainingMem = 0;
    SongNode *head = songs;
    while (head != NULL){
        totalMem += head->s.getSize();
        head = head->next;
    }
    remainingMem = memSize - totalMem;
    return (memSize - totalMem);
}

UtPod::~UtPod() {   //frees all memory if called
    clearMemory();
}

void UtPod::swap(int indexOne, int indexTwo) {  //swaps nodes at given indeces of linked list
    SongNode *temp = songs;
    SongNode *temp2 = songs;
    for(int i = 0; i < indexOne; i++){
        temp = temp->next;
    }
    for(int i = 0; i < indexTwo; i++){
        temp2 = temp2->next;
    }
    Song temp3 = temp->s;
    temp->s = temp2->s;
    temp2->s = temp3;
}
