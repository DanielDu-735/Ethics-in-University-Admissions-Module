#ifndef STUDENTAPPLICANT_H
#define STUDENTAPPLICANT_H

#include <iostream>
#include <string>
struct Applicant {
    std::string name;
    double gpa;           // 0.0 - 4.0
    int sat_score;        // 400 - 1600
    double household_income; // actual income value
    bool first_gen;       // first generation college student
    int essay_score;      // 1 - 10
    std::string demographic; // for tracking
    
    Applicant(std::string n, double g, int sat, double income, bool fg, int essay, std::string demo);
    
    void display() const;
};

#endif
