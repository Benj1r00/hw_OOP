#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class EducationalInstitution
{
public:
    std::string name;           //назва закладу
    int year_of_foundation;     //рік заснування
    int number_of_students;     //кількість студентів
    int number_of_patents;      //кількість патентів
    double rating;              //реййтинг університети по п'ятибальній шкалі

    //конструктор класу
    EducationalInstitution(std::string s, int n, int t, int b, double d)
    {
        name = s;
        year_of_foundation = n;
        number_of_students = t;
        number_of_patents = b;
        rating = (d > 5.0) ? 5.0f : d;
    }

    //вивід характеристик
    void show_obj()
    {
        std::cout << "1. " << name << " 2. ";
        std::cout << year_of_foundation << " 3. ";
        std::cout << number_of_students << " 4. ";
        std::cout << number_of_patents << " 5. ";
        std::cout << rating << "\n";
    }

    //перевантажуємо оператор == для порівнання об'єктів через стандартний метод find()
    bool operator==(const EducationalInstitution& a) const
    {
        return name == a.name &&
               year_of_foundation == a.year_of_foundation &&
               number_of_students == a.number_of_students &&
               number_of_patents == a.number_of_patents &&
               rating == a.rating; 
    }
};

//функція для виведення методу show_obj() для вектору об'єктів EducationalInstitution
void show_vec_obj(std::vector<EducationalInstitution>& vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i].show_obj();
    }
    std::cout << "\n";
}

int main()
{
    //створюємо вектор об'єктів
    std::vector<EducationalInstitution> vec_obj = {
        EducationalInstitution("KPI", 1898, 25000, 10, 5.0f),
        EducationalInstitution("Lviv Poly", 1816, 15000, 1, 4.7f),
        EducationalInstitution("KNU", 1834, 24000, 8, 4.8f),
        EducationalInstitution("Kyiv-Mohyla", 1615, 5000, 0,  4.95f),
        EducationalInstitution("NAU", 1995, 800, 5, 3.9f)
    };
    //вивід стартових данних
    show_vec_obj(vec_obj);

    //сортування в порядку зпадання за кількісю студентів
    std::cout << "sorting by number of students: \n";
    std::sort(vec_obj.begin(), vec_obj.end(), [](const EducationalInstitution& a, const EducationalInstitution& b){
        return a.number_of_students > b.number_of_students;
    });

    show_vec_obj(vec_obj);

    //сортування в порядку зростання за рейтинговим балом
    std::sort(vec_obj.begin(), vec_obj.end(), [](const EducationalInstitution& a, const EducationalInstitution& b){
        return a.rating < b.rating;
    });

    std::cout << "ranking by rating score: \n";
    show_vec_obj(vec_obj);

    //створюємо об'єкт по який будемо гукати в весторі об'єктів
    EducationalInstitution target("NAU", 1995, 800, 5, 3.9f);

    //шукаємо об'єкт target в векторі
    std::vector<EducationalInstitution>::iterator it = std::find(vec_obj.begin(), vec_obj.end(), target);

    //вискновок, знайшовся такий же об'єкт чи ні
    if (it != vec_obj.end()){
        it->show_obj();
    }
    else
    {
        std::cout << "no such object was found";
    }
    return 0;
}