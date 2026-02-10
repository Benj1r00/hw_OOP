#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Letter
{
public:
    char value;
    Letter(char c) {value = c;}
};

class Word
{
public: 
    std::vector<Letter> letters;
    void add_letter(char c) 
    {
        Letter newLetter(c);      // 1. Створюємо об'єкт явно
        letters.push_back(newLetter); // 2. Кладемо його у вектор
    }

    std::string toString() const //повернення слова як звичайного string
    {
        std::string s = "";
        for (const auto& l : letters) s += l.value;
        return s;
    }

    bool startsWithVowel() const // перевірка чи слово починається з голосної
    {
        if (letters.empty()) return false;
        char c = letters[0].value;
        std::string vowels = "aeiouyAEIOUY";
        return vowels.find(c) != std::string::npos;
    }

    char getSortChar() const
    {
        if (letters.size() < 2) return '\0';
        return letters[1].value;
    }
};


struct SentenceElem
{
    bool isWord;
    Word word;
    char punctuation;

    SentenceElem(Word w) {isWord = true, word = w, punctuation = '\0';}
    SentenceElem(char p) {isWord = false, word = {}, punctuation = p;} 
};

class Sentence
{
public:
    std::vector<SentenceElem> elements;
    void add(SentenceElem e) {elements.push_back(e);}
};

class Text
{
public:
    std::vector<Sentence> sentences;
    void add(const Sentence s) {sentences.push_back(s);}
};

class TextProcessor
{
private:
   std::string normalization_of_spaces(const std::string& str)
   {
        std::string result;
        bool flagSpace = false;
        for (size_t i = 0; i < str.size(); i++)
        {
            if (std::isspace(str[i])) 
            {
                if (!flagSpace)
                {
                    result += ' ';
                    flagSpace = true;
                }
            }
            else
            {
                result += str[i];
                flagSpace = false;
            }
        }
        return result;
    }

    bool letter_or_not(char c)
    {
        std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        bool result = false;
        for (size_t i = 0; i < letters.size(); i++)
        {
            if (c == letters[i]) {result = true;}
        }
        return result;
    }

    Text restructuring(std::string str)
    {
        Text result;
        Sentence currentSent;
        Word currentWord;
        std::string endSymbols = "!?.";
        for (size_t i = 0; i < str.size(); i++)
        {
            if (letter_or_not(str[i]))
            {
                currentWord.add_letter(str[i]);
            }
            else 
            {
                if (!currentWord.letters.empty())
                {
                    currentSent.add(SentenceElem(currentWord));
                    currentWord = Word();
                }
                if (str[i] == ' ')
                {
                    continue;
                }
                if (endSymbols.find(str[i]) != std::string::npos)
                {
                    currentSent.add(SentenceElem(str[i]));
                    result.add(currentSent);
                    currentSent = Sentence();
                }
                else 
                {
                    currentSent.add(SentenceElem(str[i]));
                }
            }
        }
        return result;
    }

    void sort_sec_let(std::vector<Word>& vec_word)
    {
        for (size_t i = 0; i < vec_word.size(); i++)
        {
            for (size_t j = 0; j < vec_word.size()-i-1; j++)
            {
                if (vec_word[j].getSortChar() > vec_word[j+1].getSortChar())
                {
                    Word w = vec_word[j+1];
                    vec_word[j+1] = vec_word[j];
                    vec_word[j] = w;
                }
            }  
        }  
    }
public:
    void result()
    {
        try
        {
            std::string Imput_text = "Apple orange elephant umbrella popka ice avocado eye.";
            if(Imput_text.empty())
            {
                throw std::runtime_error("the text is empty");
            }
            
            Text myText = restructuring(normalization_of_spaces(Imput_text));
            
            std::vector<Word> vec;
            for (size_t i = 0; i < myText.sentences.size(); i++) 
            {
                Sentence& s = myText.sentences[i];
                for (size_t j = 0; j < s.elements.size(); j++)
                {
                    SentenceElem& el = s.elements[j];
                    if (el.isWord && el.word.startsWithVowel())
                    {
                        vec.push_back(el.word);
                    } 
                }
            }

            sort_sec_let(vec);

            for (size_t i = 0; i < vec.size(); i++)
            {
                std::cout << vec[i].toString() << '\n';
            }
        }
        catch (const std::exception& e) 
        {
            std::cerr << "Помилка: " << e.what() << std::endl;
        }
    }
};

int main()
{
    TextProcessor text;
    text.result();
    return 0;
}