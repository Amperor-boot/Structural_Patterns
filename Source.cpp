#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <Windows.h>

// Базовый класс  
class Text {
public:
    virtual std::string render(const std::string& content) {
        return content;
    }
};

// Декоратор для абзаца  
class Paragraph : public Text {
public:
    std::string render(const std::string& content) override {
        return "<p>" + content + "</p>";
    }
};

// Декоратор для реверсирования текста  
class Reversed : public Text {
public:
    std::string render(const std::string& content) override {
        std::string reversed_content = content;
        std::reverse(reversed_content.begin(), reversed_content.end());
        return reversed_content;
    }
};

// Класс для создания ссылки  
class Link {
public:
    std::string render(const std::string& url, const std::string& content) {
        return "<a href=\"" + url + "\">" + content + "</a>";
    }
};

class VeryHeavyDatabase {
public:
    virtual std::string GetData(const std::string& key) {
        return "value";  // Имитация тяжелой операции  
    }
};

class OneShotDB : public VeryHeavyDatabase {
private:
    VeryHeavyDatabase* real_object;
    size_t shots;
    size_t current_shot;

public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : real_object(real_object), shots(shots), current_shot(0) {
    }

    std::string GetData(const std::string& key) override {
        if (current_shot < shots) {
            current_shot++;
            return real_object->GetData(key);
        }
        else {
            return "error";
        }
    }
};

int main(int argc, char** argv)
{
    setlocale(LC_CTYPE, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Используем декоратор для параграфа  
    Text* text_block = new Paragraph();
    std::cout << text_block->render("Hello world") << std::endl;  // <p>Hello world</p>

    // Используем декоратор для реверсирования  
    text_block = new Reversed();
    std::cout << text_block->render("Hello world") << std::endl;  // dlrow olleH

    // Используем класс Link  
    Link link;
    std::cout << link.render("netology.ru", "Hello world") << std::endl;  // <a href="netology.ru">Hello world</a>

    // Освобождаем память  
    delete text_block;  // Освобождаем память для Paragraph и Reversed  

    VeryHeavyDatabase real_db;
    OneShotDB limit_db(&real_db, 2);

    std::cout << limit_db.GetData("key") << std::endl;  // value  
    std::cout << limit_db.GetData("key") << std::endl;  // value  
    std::cout << limit_db.GetData("key") << std::endl;  // error

    return 0;
}