#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class SimpleTextProcessor
{
public:
    // розділення текста на слова та збереження їх у векторі
    std::vector<std::string> separate_words_to_vec(const std::string& text)
    {
        std::vector<std::string> words;
        std::stringstream ss(text); // створення потока для розділення текста на слова
        std::string word;

        while (ss >> word) // розділення текста на слова
        {
            words.push_back(word);
        }
        return words;
    }

    // сортування вектора слів за другою літерою (бульбашковим сортуванням)
    void sort_sec_let(std::vector<std::string>& vec_word)
    {
        for(size_t i = 0; i < vec_word.size(); i++)
        {
            for(size_t j = 0; j < vec_word.size()-i-1; j++)
            {
                if((int)vec_word[j][1] > (int)vec_word[j+1][1])
                {
                    std::string s = vec_word[j+1];
                    vec_word[j+1] = vec_word[j];
                    vec_word[j] = s;
                }
            }
        }
    }
    
    void result() // головна функція для виконання завдання
    {
        try
        {
            std::string Imput_text = "Apple orange elephant umbrella popka ice avocado eye";
            if(Imput_text.empty()) // перевірка на порожній текст
            {
                throw std::runtime_error("the text is empty");
            }
            std::cout << "Original text: " << Imput_text << "\n";

            std::vector<std::string> Imput_words_vec = separate_words_to_vec(Imput_text);
            std::string vowels = "aeiouyAEIOUY"; 

            for (size_t i = 0; i < Imput_words_vec.size(); i++) // видалення слів, які не починаються з голосної літери
            {
                if (vowels.find(Imput_words_vec[i][0]) == std::string::npos)
                {
                    Imput_words_vec.erase(Imput_words_vec.begin() + i);
                    i--;
                }
            }
            
            sort_sec_let(Imput_words_vec); // сортування

            for (size_t i = 0; i < Imput_words_vec.size(); i++)
            {
                std::cout << Imput_words_vec[i] << "\n";
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << "\n";
        }
    }
};

#ifndef TESTING
int main()
{
    SimpleTextProcessor text;
    text.result();
    return 0;
}
#endif