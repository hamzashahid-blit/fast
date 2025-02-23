#include <iostream>
#include <vector>
#include <string>

struct MenuItem {
    std::string name;
    std::string type;
    double price;
};

class CoffeeShop {
public:
    const std::string name;
    std::vector<MenuItem> menu;
    std::vector<std::string> orders;

    CoffeeShop(std::string n, std::vector<MenuItem> m) : name(n), menu(m) {}

    std::string addOrder(const std::string& itemName) {
        for (const auto& item : menu) {
            if (item.name == itemName) {
                orders.push_back(itemName);
                return "Order added: " + itemName;
            }
        }
        return "This item is currently unavailable!";
    }

    std::string fulfillOrder() {
        if (!orders.empty()) {
            std::string item = orders.front();
            orders.erase(orders.begin());
            return "The " + item + " is ready!";
        }
        return "All orders have been fulfilled!";
    }

    std::vector<std::string> listOrders() const {
        return orders;
    }

    double dueAmount() const {
        double total = 0.0;
        for (const auto& order : orders) {
            for (const auto& item : menu) {
                if (item.name == order) {
                    total += item.price;
                    break;
                }
            }
        }
        return total;
    }

    std::string cheapestItem() const {
        if (menu.empty()) return "No items available";
        MenuItem cheapest = menu[0];
        for (const auto& item : menu) {
            if (item.price < cheapest.price) {
                cheapest = item;
            }
        }
        return cheapest.name;
    }

    std::vector<std::string> drinksOnly() const {
        std::vector<std::string> drinks;
        for (const auto& item : menu) {
            if (item.type == "drink") {
                drinks.push_back(item.name);
            }
        }
        return drinks;
    }

    std::vector<std::string> foodOnly() const {
        std::vector<std::string> food;
        for (const auto& item : menu) {
            if (item.type == "food") {
                food.push_back(item.name);
            }
        }
        return food;
    }
};

int main() {
    std::vector<MenuItem> menu = {
        {"Latte", "drink", 3.5},
        {"Cappuccino", "drink", 4.0},
        {"Sandwich", "food", 5.0}
    };

    CoffeeShop shop("Cool Coffee", menu);

    std::cout << shop.addOrder("Latte") << std::endl;
    std::cout << shop.addOrder("Sandwich") << std::endl;
    std::cout << shop.fulfillOrder() << std::endl;
    std::cout << "Due Amount: " << shop.dueAmount() << std::endl;
    std::cout << "Cheapest Item: " << shop.cheapestItem() << std::endl;

    std::cout << "Drinks: ";
    for (const auto& drink : shop.drinksOnly()) {
        std::cout << drink << " ";
    }
    std::cout << std::endl;

    std::cout << "Food: ";
    for (const auto& food : shop.foodOnly()) {
        std::cout << food << " ";
    }
    std::cout << std::endl;

    return 0;
}
