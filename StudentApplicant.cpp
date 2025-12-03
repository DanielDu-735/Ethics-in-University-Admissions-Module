#include "StudentApplicant.h"


Applicant::Applicant(std::string n, double g, int sat, double income, bool fg, int essay, std::string demo) : name(n), gpa(g), sat_score(sat), household_income(income), first_gen(fg), essay_score(essay), demographic(demo) {}
    
void Applicant::display() const {
    std::cout << "Name: " << name << " | GPA: " << gpa << " | SAT: " << sat_score << " | Income: $" << household_income << " | First-Gen: " << (first_gen ? "Yes" : "No") << " | Essay: " << essay_score << " | Demo: " << demographic << std::endl;
}