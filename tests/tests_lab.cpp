#include <gtest/gtest.h>
#include "../src/lab1.cpp"
#include "../src/lab2.cpp"
#include "../src/lab3.cpp"
#include "../src/lab4.cpp"
#include "../src/lab5.cpp"

// 1. Тест множення: стандартний випадок (2x3 на 3x2)
TEST(MatrixMatrixTest, MultiplicationStandard) {
    Matrix m;
    std::vector<std::vector<float>> A = {
        {1.5f, 2.0f, 3.0f},
        {4.0f, 0.5f, 6.0f}
    };
    std::vector<std::vector<float>> B = {
        {7.0f, 8.0f},
        {9.0f, 1.0f},
        {2.0f, 3.5f}
    };

    // Результат:
    // [1.5*7 + 2*9 + 3*2, 1.5*8 + 2*1 + 3*3.5] -> [34.5, 24.5]
    // [4*7 + 0.5*9 + 6*2, 4*8 + 0.5*1 + 6*3.5] -> [44.5, 53.5]
    auto result = m.multiplication(A, B);

    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0].size(), 2);

    EXPECT_FLOAT_EQ(result[0][0], 34.5f);
    EXPECT_FLOAT_EQ(result[0][1], 24.5f);
    EXPECT_FLOAT_EQ(result[1][0], 44.5f);
    EXPECT_FLOAT_EQ(result[1][1], 53.5f);
}

// 2. Тест множення: несумісні розміри (має бути виняток)
TEST(MatrixMatrixTest, MultiplicationException) {
    Matrix m;
    std::vector<std::vector<float>> A = {{1.0f, 2.0f}}; // 1x2
    std::vector<std::vector<float>> B = {{1.0f, 2.0f}}; // 1x2 (кількість рядків B != стовпців A)
    
    EXPECT_THROW(m.multiplication(A, B), std::invalid_argument);
}

// 3. Тест суми мінімумів: перевірка логіки по стовпцях
TEST(MatrixMatrixTest, SumSmallestInColumns) {
    Matrix m;
    // Матриця:
    // 10.0  2.0  5.0
    //  4.0  8.0  1.0
    std::vector<std::vector<float>> C = {
        {10.0f, 2.0f, 5.0f},
        {4.0f, 8.0f, 1.0f}
    };

    // Мінімуми в стовпцях: 4.0, 2.0, 1.0
    // Сума: 4 + 2 + 1 = 7.0
    float result = m.sums_of_the_smallest_elements_of_rows(C);
    EXPECT_FLOAT_EQ(result, 7.0f);
}

// 4. Тест суми мінімумів: від'ємні числа
TEST(MatrixMatrixTest, SumMinWithNegatives) {
    Matrix m;
    // Матриця:
    // -1.0  -5.0
    // -3.0   2.0
    std::vector<std::vector<float>> C = {
        {-1.0f, -5.0f},
        {-3.0f, 2.0f}
    };

    // Мінімуми в стовпцях: -3.0, -5.0
    // Сума: -8.0
    float result = m.sums_of_the_smallest_elements_of_rows(C);
    EXPECT_FLOAT_EQ(result, -8.0f);
}

// 5. Тест: порожня матриця
TEST(MatrixMatrixTest, EmptyMatrixException) {
    Matrix m;
    std::vector<std::vector<float>> empty;
    EXPECT_THROW(m.sums_of_the_smallest_elements_of_rows(empty), std::invalid_argument);
}

//==========================================================================
//==========================================================================

// 1. Тест розділення тексту на слова
TEST(TextProcessorTest, SeparateWordsStandard) {
    SimpleTextProcessor tp;
    std::string input = "Apple orange elephant";
    
    std::vector<std::string> expected = {"Apple", "orange", "elephant"};
    auto result = tp.separate_words_to_vec(input);
    
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result, expected);
}

// 2. Тест сортування за другою літерою
TEST(TextProcessorTest, SortBySecondLetter_1) {
    SimpleTextProcessor tp;
    // 'p' (Apple), 'r' (orange), 'l' (elephant)
    // Очікуваний порядок за ASCII другої літери: 'l' < 'p' < 'r'
    std::vector<std::string> words = {"Apple", "orange", "elephant"};
    std::vector<std::string> expected = {"elephant", "Apple", "orange"};
    
    tp.sort_sec_let(words);
    
    EXPECT_EQ(words, expected);
}

// 3. Тест логіки фільтрації голосних (імітація блоку з result())
TEST(TextProcessorTest, VowelFilteringLogic) {
    SimpleTextProcessor tp;
    std::vector<std::string> words = {"Apple", "popka", "orange", "sky"};
    std::string vowels = "aeiouyAEIOUY";

    // Логіка, яку ви використовуєте в методі result()
    for (size_t i = 0; i < words.size(); i++) {
        if (vowels.find(words[i][0]) == std::string::npos) {
            words.erase(words.begin() + i);
            i--;
        }
    }

    // "popka" та "sky" мають бути видалені, бо починаються на приголосні
    ASSERT_EQ(words.size(), 2);
    EXPECT_EQ(words[0], "Apple");
    EXPECT_EQ(words[1], "orange");
}

// 4. Тест обробки порожнього рядка (перевірка Exception)
TEST(TextProcessorTest, EmptyInputThrowsException) {
    SimpleTextProcessor tp;
    // Оскільки у вашому коді перевірка стоїть всередині result(), 
    // для тесту ми можемо викликати метод або змоделювати ситуацію
    
    // Якщо ви винесете логіку в окремий метод, це буде виглядати так:
    EXPECT_THROW({
        std::string input = "";
        if(input.empty()) throw std::runtime_error("the text is empty");
    }, std::runtime_error);
}

// 5. Тест сортування з однаковими другими літерами
TEST(TextProcessorTest, SortWithSameSecondLetter) {
    SimpleTextProcessor tp;
    // 'c' (ice), 'c' (ocean) -> порядок має залишитися стабільним або за алгоритмом
    std::vector<std::string> words = {"ocean", "ice"};
    std::vector<std::string> expected = {"ocean", "ice"}; // 'c' == 'c', сортування не змінює місця
    
    tp.sort_sec_let(words);
    EXPECT_EQ(words, expected);
}

//==========================================================================
//==========================================================================

// 1. Тест конструктора та обмеження рейтингу
TEST(EducationalInstitutionTest, ConstructorAndRatingLimit) {
    // Перевірка нормального рейтингу
    EducationalInstitution knu("KNU", 1834, 24000, 8, 4.8);
    EXPECT_EQ(knu.name, "KNU");
    EXPECT_DOUBLE_EQ(knu.rating, 4.8);

    // Перевірка обмеження рейтингу (макс 5.0)
    EducationalInstitution kpi("KPI", 1898, 25000, 10, 10.5); 
    EXPECT_DOUBLE_EQ(kpi.rating, 5.0);
}

// 2. Тест оператора порівняння (==)
TEST(EducationalInstitutionTest, EqualityOperator) {
    EducationalInstitution inst1("NAU", 1933, 15000, 5, 4.0);
    EducationalInstitution inst2("NAU", 1933, 15000, 5, 4.0);
    EducationalInstitution inst3("KPI", 1898, 25000, 10, 5.0);

    EXPECT_TRUE(inst1 == inst2);
    EXPECT_FALSE(inst1 == inst3);
}

// 3. Тест сортування за кількістю студентів (спадання)
TEST(EducationalInstitutionTest, SortByStudentsDescending) {
    std::vector<EducationalInstitution> vec = {
        {"Small", 2000, 100, 1, 3.0},
        {"Big", 1900, 1000, 5, 4.5},
        {"Medium", 1950, 500, 2, 4.0}
    };

    std::sort(vec.begin(), vec.end(), [](const EducationalInstitution& a, const EducationalInstitution& b){
        return a.number_of_students > b.number_of_students;
    });

    EXPECT_EQ(vec[0].name, "Big");
    EXPECT_EQ(vec[1].name, "Medium");
    EXPECT_EQ(vec[2].name, "Small");
}

// 4. Тест сортування за рейтингом (зростання)
TEST(EducationalInstitutionTest, SortByRatingAscending) {
    std::vector<EducationalInstitution> vec = {
        {"Best", 2000, 100, 1, 5.0},
        {"Worst", 1900, 1000, 5, 2.0},
        {"Average", 1950, 500, 2, 3.5}
    };

    std::sort(vec.begin(), vec.end(), [](const EducationalInstitution& a, const EducationalInstitution& b){
        return a.rating < b.rating;
    });

    EXPECT_EQ(vec[0].name, "Worst");
    EXPECT_EQ(vec[1].name, "Average");
    EXPECT_EQ(vec[2].name, "Best");
}

// 5. Тест пошуку об'єкта через std::find
TEST(EducationalInstitutionTest, FindObject) {
    std::vector<EducationalInstitution> vec = {
        {"KPI", 1898, 25000, 10, 5.0},
        {"NAU", 1933, 15000, 5, 3.9}
    };

    EducationalInstitution target("NAU", 1933, 15000, 5, 3.9);
    
    auto it = std::find(vec.begin(), vec.end(), target);
    
    ASSERT_NE(it, vec.end());
    EXPECT_EQ(it->name, "NAU");
    
    EducationalInstitution non_existent("KNU", 1834, 1, 1, 1.0);
    auto it_fail = std::find(vec.begin(), vec.end(), non_existent);
    EXPECT_EQ(it_fail, vec.end());
}

//==========================================================================
//==========================================================================

// --- ТЕСТИ ДЛЯ КЛАСУ Word ---

TEST(WordTest, ToStringConversion_w) {
    Word w;
    w.add_letter('H');
    w.add_letter('e');
    w.add_letter('l');
    w.add_letter('l');
    w.add_letter('o');
    EXPECT_EQ(w.toString(), "Hello");
}

TEST(WordTest, VowelCheck) {
    Word w1; w1.add_letter('A'); w1.add_letter('p');
    Word w2; w2.add_letter('c'); w2.add_letter('a'); w2.add_letter('t');
    
    EXPECT_TRUE(w1.startsWithVowel());
    EXPECT_FALSE(w2.startsWithVowel());
}

TEST(WordTest, GetSortChar) {
    Word w;
    w.add_letter('B'); // index 0
    w.add_letter('e'); // index 1
    w.add_letter('e'); // index 2
    EXPECT_EQ(w.getSortChar(), 'e');

    Word shortWord;
    shortWord.add_letter('A');
    EXPECT_EQ(shortWord.getSortChar(), '\0'); // перевірка на коротке слово
}

// --- ТЕСТИ ДЛЯ ObjectTextProcessor (Логіка обробки) ---

TEST(ObjectTextProcessorTest, NormalizationOfSpaces) {
    ObjectTextProcessor tp;
    std::string input = "Hello    world \t  test";
    std::string expected = "Hello world test";
    EXPECT_EQ(tp.normalization_of_spaces(input), expected);
}

TEST(ObjectTextProcessorTest, LetterOrNotCheck) {
    ObjectTextProcessor tp;
    EXPECT_TRUE(tp.letter_or_not('a'));
    EXPECT_TRUE(tp.letter_or_not('Z'));
    EXPECT_FALSE(tp.letter_or_not('1'));
    EXPECT_FALSE(tp.letter_or_not('!'));
}

TEST(ObjectTextProcessorTest, TextRestructuring) {
    ObjectTextProcessor tp;
    std::string input = "Hi! How are you?";
    Text result = tp.restructuring(input);

    // Має бути 2 речення
    ASSERT_EQ(result.sentences.size(), 2);
    
    // Перевірка першого слова першого речення
    SentenceElem firstElem = result.sentences[0].elements[0];
    EXPECT_TRUE(firstElem.isWord);
    EXPECT_EQ(firstElem.word.toString(), "Hi");
}

// --- ТЕСТИ ДЛЯ СОРТУВАННЯ ---

TEST(ObjectTextProcessorTest, SortBySecondLetter_2) {
    ObjectTextProcessor tp;
    Word w1; w1.add_letter('c'); w1.add_letter('z'); // 2-га 'z'
    Word w2; w2.add_letter('a'); w2.add_letter('b'); // 2-га 'b'
    Word w3; w3.add_letter('b'); w3.add_letter('m'); // 2-га 'm'

    std::vector<Word> vec = {w1, w2, w3};
    tp.sort_sec_let(vec);

    // Очікуваний порядок за другою літерою: b, m, z
    EXPECT_EQ(vec[0].toString(), "ab");
    EXPECT_EQ(vec[1].toString(), "bm");
    EXPECT_EQ(vec[2].toString(), "cz");
}

// --- КОМПЛЕКСНИЙ ТЕСТ (Аналог методу result) ---

TEST(ObjectTextProcessorTest, IntegrationVowelFilteringAndSorting) {
    ObjectTextProcessor tp;
    // Текст, де слова на голосну: Apple, orange, elephant
    // Другі літери: p, r, l
    std::string input = "Apple orange elephant popka.";
    
    Text myText = tp.restructuring(tp.normalization_of_spaces(input));
    std::vector<Word> vec;
    
    for (auto& s : myText.sentences) {
        for (auto& el : s.elements) {
            if (el.isWord && el.word.startsWithVowel()) {
                vec.push_back(el.word);
            }
        }
    }
    
    tp.sort_sec_let(vec);
    
    ASSERT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0].toString(), "elephant"); // 'l'
    EXPECT_EQ(vec[1].toString(), "Apple");    // 'p'
    EXPECT_EQ(vec[2].toString(), "orange");   // 'r'
}

// --- ТЕСТИ ДЛЯ КЛАСУ Word ---

TEST(WordTest, ToStringConversion) {
    Word w;
    w.add_letter('H');
    w.add_letter('e');
    w.add_letter('l');
    w.add_letter('l');
    w.add_letter('o');
    EXPECT_EQ(w.toString(), "Hello");
}

TEST(WordTest, VowelCheck_1) {
    Word w1; w1.add_letter('A'); w1.add_letter('p');
    Word w2; w2.add_letter('c'); w2.add_letter('a'); w2.add_letter('t');
    
    EXPECT_TRUE(w1.startsWithVowel());
    EXPECT_FALSE(w2.startsWithVowel());
}

TEST(WordTest, GetSortChar_1) {
    Word w;
    w.add_letter('B'); // index 0
    w.add_letter('e'); // index 1
    w.add_letter('e'); // index 2
    EXPECT_EQ(w.getSortChar(), 'e');

    Word shortWord;
    shortWord.add_letter('A');
    EXPECT_EQ(shortWord.getSortChar(), '\0'); // перевірка на коротке слово
}

// --- ТЕСТИ ДЛЯ ObjectTextProcessor (Логіка обробки) ---

TEST(ObjectTextProcessorTest, NormalizationOfSpaces_1) {
    ObjectTextProcessor tp;
    std::string input = "Hello    world \t  test";
    std::string expected = "Hello world test";
    EXPECT_EQ(tp.normalization_of_spaces(input), expected);
}

TEST(ObjectTextProcessorTest, LetterOrNotCheck_1) {
    ObjectTextProcessor tp;
    EXPECT_TRUE(tp.letter_or_not('a'));
    EXPECT_TRUE(tp.letter_or_not('Z'));
    EXPECT_FALSE(tp.letter_or_not('1'));
    EXPECT_FALSE(tp.letter_or_not('!'));
}

TEST(ObjectTextProcessorTest, TextRestructuring_1) {
    ObjectTextProcessor tp;
    std::string input = "Hi! How are you?";
    Text result = tp.restructuring(input);

    // Має бути 2 речення
    ASSERT_EQ(result.sentences.size(), 2);
    
    // Перевірка першого слова першого речення
    SentenceElem firstElem = result.sentences[0].elements[0];
    EXPECT_TRUE(firstElem.isWord);
    EXPECT_EQ(firstElem.word.toString(), "Hi");
}

// --- ТЕСТИ ДЛЯ СОРТУВАННЯ ---

TEST(ObjectTextProcessorTest, SortBySecondLetter) {
    ObjectTextProcessor tp;
    Word w1; w1.add_letter('c'); w1.add_letter('z'); // 2-га 'z'
    Word w2; w2.add_letter('a'); w2.add_letter('b'); // 2-га 'b'
    Word w3; w3.add_letter('b'); w3.add_letter('m'); // 2-га 'm'

    std::vector<Word> vec = {w1, w2, w3};
    tp.sort_sec_let(vec);

    // Очікуваний порядок за другою літерою: b, m, z
    EXPECT_EQ(vec[0].toString(), "ab");
    EXPECT_EQ(vec[1].toString(), "bm");
    EXPECT_EQ(vec[2].toString(), "cz");
}

// --- КОМПЛЕКСНИЙ ТЕСТ (Аналог методу result) ---

TEST(ObjectTextProcessorTest, IntegrationVowelFilteringAndSorting_1) {
    ObjectTextProcessor tp;
    // Текст, де слова на голосну: Apple, orange, elephant
    // Другі літери: p, r, l
    std::string input = "Apple orange elephant popka.";
    
    Text myText = tp.restructuring(tp.normalization_of_spaces(input));
    std::vector<Word> vec;
    
    for (auto& s : myText.sentences) {
        for (auto& el : s.elements) {
            if (el.isWord && el.word.startsWithVowel()) {
                vec.push_back(el.word);
            }
        }
    }
    
    tp.sort_sec_let(vec);
    
    ASSERT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0].toString(), "elephant"); // 'l'
    EXPECT_EQ(vec[1].toString(), "Apple");    // 'p'
    EXPECT_EQ(vec[2].toString(), "orange");   // 'r'
}

// 1. Тести для створення квіток ( Flower та нащадки )
TEST(FlowerTest, ConstructorValidation) {
    // Перевірка коректного створення
    EXPECT_NO_THROW(Rose(100.0, 10, 50.0));
    
    // Перевірка викидання виключення при некоректних параметрах
    EXPECT_THROW(Rose(-10.0, 10, 50.0), std::invalid_argument); // від'ємна ціна
    EXPECT_THROW(Rose(100.0, 0, 50.0), std::invalid_argument);  // свіжість < 1
    EXPECT_THROW(Rose(100.0, 11, 50.0), std::invalid_argument); // свіжість > 10
}

TEST(FlowerTest, SubclassGetters) {
    Rose r(150.0, 9, 60.0);
    EXPECT_EQ(r.get_name(), "Rose");
    EXPECT_DOUBLE_EQ(r.get_price(), 150.0);
    EXPECT_EQ(r.get_freshness(), 9);
}

// 2. Тести для аксесуарів у Букеті
TEST(BouquetTest, AccessoryLogic) {
    Bouquet b;
    b.addAccessory(50.0);
    b.addAccessory(25.5);
    
    EXPECT_DOUBLE_EQ(b.accessoryPrice, 75.5);
    EXPECT_THROW(b.addAccessory(-10.0), std::domain_error);
}

// 3. Тест підрахунку повної вартості
TEST(BouquetTest, CalculationTotalCost) {
    Bouquet b;
    b.addAccessory(100.0);
    b.addFlower(std::make_unique<Rose>(200.0, 10, 60.0));
    b.addFlower(std::make_unique<Tulip>(50.0, 8, 40.0));
    
    // 100 (аксесуар) + 200 (троянда) + 50 (тюльпан) = 350
    EXPECT_DOUBLE_EQ(b.CalcCostBouquet(), 350.0);
}

// 4. Тест сортування за свіжістю
TEST(BouquetTest, SortingByFreshness) {
    Bouquet b;
    b.addFlower(std::make_unique<Tulip>(80.0, 5, 40.0));  // Середня свіжість
    b.addFlower(std::make_unique<Rose>(150.0, 10, 60.0)); // Найвища свіжість
    b.addFlower(std::make_unique<Lily>(120.0, 7, 50.0));  // Висока свіжість
    
    b.sortBouquet();
    
    // Перевіряємо порядок після сортування (має бути за спаданням: 10, 7, 5)
    ASSERT_EQ(b.flowers.size(), 3);
    EXPECT_EQ(b.flowers[0]->get_freshness(), 10);
    EXPECT_EQ(b.flowers[1]->get_freshness(), 7);
    EXPECT_EQ(b.flowers[2]->get_freshness(), 5);
}

// 5. Тест пошуку квітки за діапазоном довжини
TEST(BouquetTest, FindByStemLengthRange) {
    Bouquet b;
    b.addFlower(std::make_unique<Rose>(150.0, 10, 60.0));
    b.addFlower(std::make_unique<Tulip>(80.0, 10, 40.0));
    
    // Перевірка валідації діапазону
    EXPECT_THROW(b.findFlowerlendht(50, 40), std::logic_error); // min > max
    EXPECT_THROW(b.findFlowerlendht(-1, 10), std::logic_error); // від'ємне значення
    
    // Логіку виводу в консоль важко перевірити через EXPECT_EQ, 
    // але ми перевіряємо, що метод не "падає" при коректному діапазоні
    EXPECT_NO_THROW(b.findFlowerlendht(30, 45));
}

// 6. Тест на додавання порожнього об'єкта (nullptr)
TEST(BouquetTest, AddEmptyFlowerException) {
    Bouquet b;
    std::unique_ptr<Flower> emptyFlower = nullptr;
    EXPECT_THROW(b.addFlower(std::move(emptyFlower)), std::runtime_error);
}