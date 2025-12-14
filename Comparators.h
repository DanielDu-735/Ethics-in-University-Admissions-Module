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
    double female_bonus;
    double nonbinary_bonus;
    
    CustomComparator(double gpa_w = 150.0, double sat_w = 0.3, 
                     double essay_w = 50.0, double fg_bonus = 100.0,
                     double low_inc_bonus = 80.0, double low_threshold = 50000.0,
                     double fem_bonus = 50.0, double nb_bonus = 60.0)
        : gpa_weight(gpa_w), sat_weight(sat_w), essay_weight(essay_w),
          first_gen_bonus(fg_bonus), low_income_bonus(low_inc_bonus),
          low_income_threshold(low_threshold), female_bonus(fem_bonus),
          nonbinary_bonus(nb_bonus) {}
    
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
        
        // Gender diversity bonus
        if (app.gender == "Female") score += female_bonus;
        else if (app.gender == "Non-binary") score += nonbinary_bonus;
        
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

std::vector<Applicant> create_sample_pool_male() {
    return {
        Applicant("Alex", 3.9, 1500, 200000, false, 8, "High-income", "Male"),
        Applicant("Jordan", 3.7, 1450, 35000, true, 9, "Low-income", "Male"),
        Applicant("Taylor", 4.0, 1580, 180000, false, 7, "High-income", "Male"),
        Applicant("Morgan", 3.6, 1380, 42000, true, 8, "Low-income", "Male"),
        Applicant("Casey", 3.8, 1520, 150000, false, 6, "Mid-income", "Male"),
        Applicant("Riley", 3.5, 1340, 28000, true, 10, "Low-income", "Male"),
        Applicant("Jamie", 3.95, 1560, 220000, false, 9, "High-income", "Male"),
        Applicant("Sam", 3.4, 1300, 38000, true, 7, "Low-income", "Male"),
        Applicant("Chris", 3.85, 1490, 160000, false, 8, "Mid-income", "Male"),
        Applicant("Pat", 3.65, 1420, 45000, true, 9, "Low-income", "Male")
    };
}

std::vector<Applicant> create_sample_pool_big() {
    return {
        Applicant("Michael", 3.75, 1470, 95000, false, 7, "Mid-income", "Male"),
        Applicant("Emma", 3.88, 1530, 175000, false, 8, "High-income", "Female"),
        Applicant("Skylar", 3.55, 1360, 32000, true, 9, "Low-income", "Non-binary"),
        Applicant("David", 3.92, 1540, 210000, false, 6, "High-income", "Male"),
        Applicant("Sophia", 3.68, 1410, 48000, true, 8, "Low-income", "Female"),
        
        Applicant("River", 3.82, 1500, 120000, false, 7, "Mid-income", "Non-binary"),
        Applicant("James", 3.71, 1455, 185000, false, 7, "High-income", "Male"),
        Applicant("Olivia", 3.63, 1395, 38000, true, 10, "Low-income", "Female"),
        Applicant("Phoenix", 3.78, 1485, 62000, false, 8, "Mid-income", "Non-binary"),
        Applicant("Daniel", 3.58, 1370, 43000, true, 7, "Low-income", "Male"),
        
        Applicant("Isabella", 3.94, 1555, 195000, false, 9, "High-income", "Female"),
        Applicant("Sage", 3.45, 1315, 29000, true, 8, "Low-income", "Non-binary"),
        Applicant("Matthew", 3.87, 1515, 165000, false, 7, "High-income", "Male"),
        Applicant("Ava", 3.72, 1445, 52000, true, 9, "Low-income", "Female"),
        Applicant("Quinn", 3.81, 1495, 110000, false, 8, "Mid-income", "Non-binary"),
        
        Applicant("William", 3.66, 1405, 78000, false, 6, "Mid-income", "Male"),
        Applicant("Mia", 3.91, 1545, 205000, false, 8, "High-income", "Female"),
        Applicant("Ren", 3.52, 1345, 36000, true, 9, "Low-income", "Non-binary"),
        Applicant("Joseph", 3.84, 1505, 155000, false, 7, "High-income", "Male"),
        Applicant("Charlotte", 3.69, 1425, 44000, true, 8, "Low-income", "Female"),
        
        Applicant("Kai", 3.76, 1475, 88000, false, 7, "Mid-income", "Non-binary"),
        Applicant("Andrew", 3.89, 1525, 190000, false, 8, "High-income", "Male"),
        Applicant("Amelia", 3.61, 1385, 39000, true, 9, "Low-income", "Female"),
        Applicant("Avery", 3.79, 1490, 125000, false, 7, "Mid-income", "Non-binary"),
        Applicant("Benjamin", 3.54, 1355, 31000, true, 8, "Low-income", "Male"),
        
        Applicant("Harper", 3.93, 1550, 215000, false, 9, "High-income", "Female"),
        Applicant("Rowan", 3.48, 1325, 34000, true, 7, "Low-income", "Non-binary"),
        Applicant("Ethan", 3.86, 1510, 170000, false, 8, "High-income", "Male"),
        Applicant("Evelyn", 3.74, 1460, 56000, true, 9, "Low-income", "Female"),
        Applicant("Blake", 3.80, 1500, 105000, false, 7, "Mid-income", "Non-binary"),
        
        Applicant("Alexander", 3.67, 1415, 72000, false, 6, "Mid-income", "Male"),
        Applicant("Abigail", 3.90, 1535, 200000, false, 8, "High-income", "Female"),
        Applicant("Ellis", 3.56, 1365, 40000, true, 8, "Low-income", "Non-binary"),
        Applicant("Ryan", 3.83, 1495, 180000, false, 7, "High-income", "Male"),
        Applicant("Emily", 3.70, 1435, 47000, true, 9, "Low-income", "Female"),
        
        Applicant("Ash", 3.77, 1480, 92000, false, 8, "Mid-income", "Non-binary"),
        Applicant("Joshua", 3.64, 1400, 68000, false, 7, "Mid-income", "Male"),
        Applicant("Madison", 3.88, 1520, 185000, false, 8, "High-income", "Female"),
        Applicant("Drew", 3.51, 1340, 33000, true, 9, "Low-income", "Non-binary"),
        Applicant("Christopher", 3.85, 1505, 175000, false, 7, "High-income", "Male")
    };
}