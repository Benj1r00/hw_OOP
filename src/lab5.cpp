#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

class Flower
{
protected:
    std::string name;   // назва квітки
    double price;       // прайс
    int freshness;      // 1-зів'яла, 10-тільки зірвали
    double stemLength;  // довжина стебла
public:
    // конструктор класу з перевіркою параметрів
    Flower(std::string n, double p, int f, double s)
    : name(n), price(p), freshness(f), stemLength(s){
        if (f < 1 || f > 10 || p < 0 || s < 0) // перевірка на логічність параметрів
        {
            throw std::invalid_argument("Incorrect flower parameters");
        }
    }

    // деструктор
    virtual ~Flower() {}

    // гетери для надання інформації класа
    std::string get_name() const {return name;}
    double get_price() const {return price;}
    int get_freshness() const {return freshness;}
    double get_stemLength() const {return stemLength;}

    // вивід інформація про вміст класу
    virtual void show_inf() const
    {
        std::cout << "name: " << name 
        << " price: " << price 
        << " freshness: " << freshness 
        << " stemLength: " << stemLength << "\n";
    }
};

// нащадок: троянда
class Rose : public Flower {
public:
    Rose(double p, int f, double l) : Flower("Rose", p, f, l) {}
};

// нащадок: тюльпан
class Tulip : public Flower {
public:
    Tulip(double p, int f, double l) : Flower("Tulip", p, f, l) {}
};

// нащадок: лілія
class Lily : public Flower {
public:
    Lily(double p, int f, double l) : Flower("Lily", p, f, l) {}
};

class Bouquet
{
public:
    std::vector<std::unique_ptr<Flower>> flowers;
    double accessoryPrice = 0;

    // додвання аксесуарів
    void addAccessory(double price)
    {
        if (price < 0) {throw std::domain_error("The price of accessories cannot be negative");}
        accessoryPrice += price; // збільшення ціни
    }

    // додавання квітки до вектора букета
    void addFlower (std::unique_ptr<Flower> flower)
    {
        if (!flower) {throw std::runtime_error("trying to add an empty object");}
        // переміщення вказівника в останній елемент вектора, після цієї операції flower стає nullptr
        flowers.push_back(std::move(flower));
    }

    // сортування букету за свіжістю
    void sortBouquet()
    {
        std::sort(flowers.begin(), flowers.end(), [](const auto& a, const auto& b){
            return a->get_freshness() > b->get_freshness();
        });   
    }

    // знаходження повтої вартості букету
    double CalcCostBouquet() const
    {
        double total = accessoryPrice; // додаваня вартості аксусуарів
        for (size_t i = 0; i < flowers.size(); i++) // цикл додавання вартості квітів
        {
            total += flowers[i]->get_price();
        }
        return total;
    }

    // пошук квітки за діапазоном довжини (наприклад від 10 до 20 одиниць)
    void findFlowerlendht(double min, double max)
    {
        bool found_or_not = false; // флажок, знайшлась квітка чи ні
        if (min < 0 || max < 0 || max < min) // перевірка логічності діапазону
        {
            throw std::logic_error("error in the specified range");
        }
        for (size_t i = 0; i < flowers.size(); i++)
        {
            if (flowers[i]->get_stemLength() >= min && flowers[i]->get_stemLength() <= max)
            {
                std::cout << "flower found: " << "\n";
                flowers[i]->show_inf();
                found_or_not = true; // підняття флажку, квітка знайдена
            }
        }
        if (found_or_not == false) {std::cout << "a flower with such a stem range has not been found";}
    }

    // вивід створеного букету, ціни аксесуара та повної ціни
    void ShowBouquet() const
    {
        for (size_t i = 0; i < flowers.size(); i++)
        {
            flowers[i]->show_inf();
        }

        std::cout << "accessoryPrice: " << accessoryPrice << " | ";
        std::cout << "full price of the bouquet: " << CalcCostBouquet() << "\n"; 
    }
};

#ifndef TESTING 
int main()
{
    try
    {
        Bouquet bouquet;
    
        // додавання квітів до букета
        bouquet.addFlower(std::make_unique<Rose>(150.0, 10, 60.5)); 
        bouquet.addFlower(std::make_unique<Tulip>(80.0, 7, 40.0));
        bouquet.addFlower(std::make_unique<Lily>(120.0, 9, 50.0));

        bouquet.addAccessory(50.1);
        
        std::cout << "-----------------------------------" << "\n";
        bouquet.sortBouquet(); // сортування за свіжістю
        bouquet.ShowBouquet(); // вивід букету
        std::cout << "-----------------------------------" << "\n";

        bouquet.findFlowerlendht(45.5, 55); // пошук квітки 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
#endif