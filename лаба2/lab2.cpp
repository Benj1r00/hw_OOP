#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class TextProcessor
{
private:
    std::vector<std::string> separate_words(const std::string& text)
    {
        std::vector<std::string> words;
        std::stringstream ss(text);
        std::string word;

        while (ss >> word) 
        {
            words.push_back(word);
        }
        return words;
    }

    void sort_sec_let(std::vector<std::string>& vec_word)
    {
        for(size_t i = 1; i < vec_word.size()-1; i++)
        {
            for(size_t j = 0; j < vec_word.size()-i; j++)
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
public:
    void result()
    {
        try
        {
            std::string Imput_text = "Apple orange elephant umbrella popka ice avocado eye";
            if(Imput_text.empty())
            {
                throw std::runtime_error("the text is empty");
            }
            std::cout << "Original text: " << Imput_text << "\n";

            std::vector<std::string> Imput_words_vec = separate_words(Imput_text);
            std::string vowels = "aeiouyAEIOUY"; 

            for (size_t i = 0; i < Imput_words_vec.size(); i++)
            {
                if (vowels.find(Imput_words_vec[i][0]) == std::string::npos)
                {
                    Imput_words_vec.erase(Imput_words_vec.begin() + i);
                    i--;
                }
            }
            
            sort_sec_let(Imput_words_vec);

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

int main()
{
    TextProcessor text;
    text.result();
    return 0;
}