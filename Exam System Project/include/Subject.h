#pragma once

#include <string>
#include <vector>
#include "Section.h"

using namespace std;

class Subject
{
private:
    string subjectName;
    vector<Section> sections;

public:
    Subject(string name);

    string getName() const;

    void addSection(string name);

    bool hasSections() const;

    int getSectionsCount() const;

    Section *getSection(int index);

    const vector<Section> &getSections() const;

    void displaySections() const;
};
