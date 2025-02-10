#include <iomanip>
#include <iostream>
#include <string>

class Employee {
    std::string first_name;
    std::string last_name;
    double monthly_salary;
public:
    Employee(std::string_view first_name, std::string_view last_name, double monthly_salary)
        : first_name{first_name}, last_name{last_name} {
        this->monthly_salary = monthly_salary < 0.0 ? 0.0 : monthly_salary;
    }
    void print_yearly_salary() {
        std::cout << "Employee " << first_name << ' ' << last_name << "'s yearly salary is "
                  << std::fixed << std::setprecision(2) << monthly_salary * 12 << '\n';
    }
    double get_monthly_salary() { return monthly_salary; }
    void set_monthly_salary(double new_monthly_salary) {
        if (new_monthly_salary < 0) return;
        monthly_salary = new_monthly_salary;
    }
};

int main(int argc, char* argv[])
{
    if (argc < 7) { // 1 extra for executable path
        std::cout << "Insufficient arguments passed to the main function...\n";
        std::cout << "Enter Employee A's first name, last name, and monthly salary, then the same information for Employee B! (Total of 6 args)\n";
        return -1;
    }

    double salary_a {}, salary_b {};
    try {
        salary_a = std::stod(argv[3]);
        salary_b = std::stod(argv[6]);
    } catch (const std::invalid_argument& _) {
        std::cerr << "\n[ERROR] One of the salaries is not a number!\n";
    } catch (const std::out_of_range& _) {
        std::cerr << "\n[ERROR] One of the salaries is too large or too small!\n";
    }

    Employee empA = Employee(argv[1], argv[2], salary_a);
    Employee empB = Employee(argv[4], argv[5], salary_b);
    empA.print_yearly_salary();
    empB.print_yearly_salary();
    std::cout << "Giving both employees a 10% Raise...\n";
    empA.set_monthly_salary(empA.get_monthly_salary() * 1.1);
    empB.set_monthly_salary(empB.get_monthly_salary() * 1.1);
    empA.print_yearly_salary();
    empB.print_yearly_salary();
    
    return 0;
}
