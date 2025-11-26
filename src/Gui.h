#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include "TransactionManager.h"

struct Button {
    sf::RectangleShape rect;
    sf::Text text;
    std::function<void()> onClick;

    Button(sf::Font& font, const std::string& label, sf::Vector2f size, sf::Vector2f pos, std::function<void()> cb)
        : rect(size), text(font, label,  20), onClick(cb)
    {
        rect.setPosition(pos);
        rect.setFillColor(sf::Color(100, 100, 100));
        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f(pos.x + 10.f, pos.y + 5.f));
    }

    void draw(sf::RenderTarget& target) { target.draw(rect); target.draw(text); }
    bool contains(sf::Vector2f point) const { return rect.getGlobalBounds().contains(point); }
};

enum class ActiveField
{
    None,
    ID,
    Amount,
    Date,
    Month,
    TypeIncome,
    TypeExpense,
    Cat0,
    Cat1,
    Cat2,
    Cat3
};



enum class Mode { None, Add, Edit, Delete, Summary };

class Gui {
private:
    TransactionManager& manager;
    sf::RenderWindow window;
    sf::Font font;

    
    ActiveField activeInputField;
    std::vector<Button> buttons;
    Mode currentMode;

    struct InputBox {
        sf::FloatRect bounds;
        std::string label;
        bool isActive = false;
    };
    std::vector<InputBox> inputHitboxes;

    struct ClickBox {
        sf::FloatRect bounds;
        std::string label;
    };
    std::vector<ClickBox> buttonHitboxes;

    std::string amountStr;
    std::string idStr;
    std::string monthInput = "";
    std::string summaryText;


    bool typeIncome, typeExpense;
    int category; 
    double amount;
    std::string date;
    int inputID;

public:
    Gui(TransactionManager& mgr);
    void run();

private:
    void setupUI();
    void resetInputs();
    void drawInputs(sf::RenderTarget& target);
    void onConfirm();
    void drawTextBox(sf::RenderTarget& target, const sf::FloatRect& r, bool active);
    void updateMonthlySummary(const std::string& yearMonth);
};
