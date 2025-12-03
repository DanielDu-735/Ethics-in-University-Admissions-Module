#include "StudentApplicant.h"
#include "Comparators.h"
int main() {
    std::vector<Applicant> applicants = create_sample_pool();
    int admission_slots = 5;
    
    std::cout << "=== AI-Based University Admissions Simulation ===\n";
    std::cout << "Total applicants: " << applicants.size() << "\n";
    std::cout << "Available slots: " << admission_slots << "\n";
    
    // Test different comparators
    process_admissions(applicants, AcademicOnlyComparator(), 
                      admission_slots, "Academic Only (GPA + SAT)");
    
    process_admissions(applicants, 
                      HolisticComparator(150.0, 0.3, 50.0, 100.0, 80.0, 50000.0, 40.0, 100000.0), 
                      admission_slots, "Holistic Review");
    
    // Custom comparator - students can modify these parameter values
    process_admissions(applicants, 
                      CustomComparator(200.0, 0.2, 50.0, 150.0, 100.0, 50000.0), 
                      admission_slots, "Custom Weighted");
    
    std::cout << "\n=== Questions to Consider ===\n";
    std::cout << "1. Which method seems most fair? Why?\n";
    std::cout << "2. Does prioritizing disadvantaged students create reverse bias?\n";
    std::cout << "3. Can any algorithm be truly neutral?\n";
    std::cout << "4. What weights would YOU choose and why?\n";
    
    return 0;
}
