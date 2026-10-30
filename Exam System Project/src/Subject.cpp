
#include "Subject.h"
#include <iostream>
#include <utility>

Subject::Subject(string name)
    : subjectName(name)
{
}

string Subject::getName() const
{
    return subjectName;
}

void Subject::addSection(string name)
{
    sections.emplace_back(name);
}

bool Subject::hasSections() const
{
    return !sections.empty();
}

int Subject::getSectionsCount() const
{
    return static_cast<int>(sections.size());
}

Section *Subject::getSection(int index)
{
    if (index < 0 || index >= static_cast<int>(sections.size()))
    {
        return nullptr;
    }

    return &sections[index];
}

const vector<Section> &Subject::getSections() const
{
    return sections;
}

void Subject::displaySections() const
{
    cout << "\nSubject: " << subjectName << '\n';

    if (sections.empty())
    {
        cout << "No sections available.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(sections.size()); i++)
    {
        cout << i + 1 << ". " << sections[i].getName() << '\n';
    }
}
