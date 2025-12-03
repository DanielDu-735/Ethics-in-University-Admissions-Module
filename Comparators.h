// Academic only
#include "StudentApplicant.h"
#include <queue>
#include <vector>
struct AcademicOnlyComparator {
    bool operator()(const Applicant& a, const Applicant& b) const {
        double score_a = a.gpa * 400 + a.sat_score;
        double score_b = b.gpa * 400 + b.sat_score;
        return score_a < score_b; // max heap 
    }
};

// Holistic with socioeconomic consideration
struct HolisticComparator {
    double gpa_weight;
    double sat_weight;
    double essay_weight;
    double first_gen_bonus;
    double low_income_bonus;
    double low_income_threshold;
    double mid_income_bonus;
    double mid_income_threshold;
    
    HolisticComparator(double gpa_w = 150.0, double sat_w = 0.3, 
                       double essay_w = 50.0, double fg_bonus = 100.0,
                       double low_inc_bonus = 80.0, double low_threshold = 50000.0,
                       double mid_inc_bonus = 40.0, double mid_threshold = 100000.0)
        : gpa_weight(gpa_w), sat_weight(sat_w), essay_weight(essay_w),
          first_gen_bonus(fg_bonus), low_income_bonus(low_inc_bonus),
          low_income_threshold(low_threshold), mid_income_bonus(mid_inc_bonus),
          mid_income_threshold(mid_threshold) {}
    
    bool operator()(const Applicant& a, const Applicant& b) const {
        double score_a = calculate_score(a);
        double score_b = calculate_score(b);
        return score_a < score_b;
    }
    
private:
    double calculate_score(const Applicant& app) const {
        double score = 0.0;
        
        score += app.gpa * gpa_weight;
        score += app.sat_score * sat_weight;
        
        score += app.essay_score * essay_weight;
        
        if (app.first_gen) score += first_gen_bonus;
        if (app.household_income < low_income_threshold) 
            score += low_income_bonus;
        else if (app.household_income < mid_income_threshold) 
            score += mid_income_bonus;
        
        return score;
    }
};

//Custom - for students to play with
struct CustomComparator {
    double gpa_weight;
    double sat_weight;
    double essay_weight;
    double first_gen_bonus;
    double low_income_bonus;
    double low_income_threshold;
    
    CustomComparator(double gpa_w = 150.0, double sat_w = 0.3, 
                     double essay_w = 50.0, double fg_bonus = 100.0,
                     double low_inc_bonus = 80.0, double low_threshold = 50000.0)
        : gpa_weight(gpa_w), sat_weight(sat_w), essay_weight(essay_w),
          first_gen_bonus(fg_bonus), low_income_bonus(low_inc_bonus),
          low_income_threshold(low_threshold) {}
    
    bool operator()(const Applicant& a, const Applicant& b) const {
        double score_a = calculate_score(a);
        double score_b = calculate_score(b);
        return score_a < score_b;
    }
    
    double calculate_score(const Applicant& app) const {
        double score = 0.0;
        
        score += app.gpa * gpa_weight;
        score += app.sat_score * sat_weight;
        score += app.essay_score * essay_weight;
        
        if (app.first_gen) score += first_gen_bonus;
        if (app.household_income < low_income_threshold) 
            score += low_income_bonus;
        
        return score;
    }
};

template<typename Comparator>
void process_admissions(std::vector<Applicant>& applicants, 
                       Comparator comp, 
                       int slots,
                       const std::string& method_name) {
    std::priority_queue<Applicant, std::vector<Applicant>, Comparator> pq(comp);
    
    for (const auto& app : applicants) {
        pq.push(app);
    }
    
    std::cout << "\n========== " << method_name << " ==========\n";
    std::cout << "Admitting top " << slots << " students:\n\n";
    
    int admitted = 0;
    int low_income = 0, high_income = 0, first_gen = 0;
    
    while (!pq.empty() && admitted < slots) {
        Applicant top = pq.top();
        pq.pop();
        
        std::cout << ++admitted << ". ";
        top.display();
        
        if (top.household_income < 50000) low_income++;
        if (top.household_income > 150000) high_income++;
        if (top.first_gen) first_gen++;
    }
    
    std::cout << "\n--- Demographic Analysis ---\n";
    std::cout << "Low-income students (<$50,000): " << low_income << "/" << slots 
              << " (" << (100.0 * low_income / slots) << "%)\n";
    std::cout << "High-income students (>$150,000): " << high_income << "/" << slots 
              << " (" << (100.0 * high_income / slots) << "%)\n";
    std::cout << "First-generation students: " << first_gen << "/" << slots 
              << " (" << (100.0 * first_gen / slots) << "%)\n";
}

std::vector<Applicant> create_sample_pool() {
    return {
        Applicant("Alex", 3.9, 1500, 200000, false, 8, "High-income"),
        Applicant("Jordan", 3.7, 1450, 35000, true, 9, "Low-income"),
        Applicant("Taylor", 4.0, 1580, 180000, false, 7, "High-income"),
        Applicant("Morgan", 3.6, 1380, 42000, true, 8, "Low-income"),
        Applicant("Casey", 3.8, 1520, 150000, false, 6, "Mid-income"),
        Applicant("Riley", 3.5, 1340, 28000, true, 10, "Low-income"),
        Applicant("Jamie", 3.95, 1560, 220000, false, 9, "High-income"),
        Applicant("Sam", 3.4, 1300, 38000, true, 7, "Low-income"),
        Applicant("Chris", 3.85, 1490, 160000, false, 8, "Mid-income"),
        Applicant("Pat", 3.65, 1420, 45000, true, 9, "Low-income")
    };
}