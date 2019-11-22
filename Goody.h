//
// Created by timo on 11/22/19.
//

#ifndef EXERCISES2_CODE_GOODY_H
#define EXERCISES2_CODE_GOODY_H

struct Goody {
    unsigned weight;
    unsigned value;
    bool operator == ( const Goody& rhs) {
        return this->weight == rhs.weight && this->value == rhs.value;
    }
};
#endif //EXERCISES2_CODE_GOODY_H
