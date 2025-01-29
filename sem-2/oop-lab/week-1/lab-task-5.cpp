#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

unsigned digits(unsigned i) {
    return i > 0 ? static_cast<unsigned>(std::log10(static_cast<double>(i))) + 1 : 1;
}  

int main() {
    std::string curr_input;
    std::cout << "Please enter the following information...\n";

    std::string movie_name {""};
    float adult_ticket_price {0};
    float child_ticket_price {0};
    int adult_tickets_sold {0};
    int child_tickets_sold {0};
    float donation_gross_percentage {0};
    try {
        std::cout << "Movie name: ";
        std::getline(std::cin, movie_name);
    
        std::cout << "Adult ticket price: ";
        std::getline(std::cin, curr_input);
        adult_ticket_price = std::stof(curr_input);
    
        std::cout << "Child ticket price: ";
        std::getline(std::cin, curr_input);
        child_ticket_price = std::stof(curr_input);
    
        std::cout << "Number of adult tickets sold: ";
        std::getline(std::cin, curr_input);
        adult_tickets_sold = std::stoi(curr_input);
    
        std::cout << "Number of child tickets sold: ";
        std::getline(std::cin, curr_input);
        child_tickets_sold = std::stoi(curr_input);
    
        std::cout << "Percentage of the gross amount to be donated to the charity: ";
        std::getline(std::cin, curr_input);
        donation_gross_percentage = std::stof(curr_input);
        if (donation_gross_percentage > 100) {
            std::cerr << "[ERROR] Cannot donate more than you have!\n";
            return -1;
        }
    } catch (std::exception const &ex) {
        std::cerr << "[ERROR] Invalid input. You probably entered text where a number should be or entered a number too big...\n";
        return -1;
    }

    /// Calculation
    float gross_amount {adult_ticket_price * static_cast<float>(adult_tickets_sold)
                        + child_ticket_price * static_cast<float>(child_tickets_sold)};
    float donation_amount {gross_amount * (donation_gross_percentage/100)};
    float net_sale {gross_amount - donation_amount};
    
    /// Printing
    /// I could have made a template out of this and made it more complicated than it needed to be
    /// ... which this already has become... but I dont really feel like it... 
    std::string longest_out_str {"% of Gross to be donated: "};
    int label_width { static_cast<int>(longest_out_str.length()) };
    int data_width { static_cast<int>(std::max({
                    static_cast<unsigned>(movie_name.length()),
                    digits(static_cast<unsigned>(adult_ticket_price)) + 3, // + 3 for the %.2f
                    digits(static_cast<unsigned>(child_ticket_price)) + 3,
                    digits(static_cast<unsigned>(adult_tickets_sold)),
                    digits(static_cast<unsigned>(child_tickets_sold)),
                    digits(static_cast<unsigned>(donation_gross_percentage)) + 3,
                    digits(static_cast<unsigned>(donation_amount)) + 3,
                    digits(static_cast<unsigned>(net_sale)) + 3})) + 3 };
    
    std::cout << std::fixed << std::setprecision(2)
              << std::setfill('.') << '\n'
              << std::setw(label_width) << std::left  << "Movie name: "
              << std::setw(data_width)  << std::right << movie_name << '\n'
              << std::setw(label_width) << std::left  << "Adult ticket price: "
              << std::setw(data_width)  << std::right << adult_ticket_price << '\n'
              << std::setw(label_width) << std::left  << "Child ticket price: "
              << std::setw(data_width)  << std::right << child_ticket_price << '\n'
              << std::setw(label_width) << std::left  << "Adult tickets sold: "
              << std::setw(data_width)  << std::right << adult_tickets_sold << '\n'
              << std::setw(label_width) << std::left  << "Child tickets sold: "
              << std::setw(data_width)  << std::right << child_tickets_sold << '\n'
              << std::setw(label_width) << std::left  << longest_out_str
              << std::setw(data_width)  << std::right << donation_gross_percentage << '\n'
              << std::setw(label_width) << std::left  << "Amount to be donated: "
              << std::setw(data_width)  << std::right << donation_amount << '\n'
              << std::setw(label_width) << std::left  << "Net sale: "
              << std::setw(data_width)  << std::right << net_sale << std::endl;
}
