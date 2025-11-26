#include "Gui.h"
#include <iostream>
#include "FileManager.h"
#include <sstream>

Gui::Gui(TransactionManager& mgr)
    : manager(mgr), window(sf::VideoMode({ 1280, 720 }), "Finance Tracker"), currentMode(Mode::None),
    typeIncome(false), typeExpense(false), category(-1), amount(0.0), inputID(0), activeInputField(ActiveField::None)

{
    if (!font.openFromFile("assets/arial.ttf"))
        std::cerr << "Failed to load font\n";

    setupUI();
}

void Gui::setupUI() {
    buttons.clear();
    buttons.emplace_back(font, "Add", sf::Vector2f(100.f, 40.f), sf::Vector2f(50.f, 80.f),
        [this] { currentMode = Mode::Add; resetInputs(); drawInputs(window); });
    buttons.emplace_back(font, "Edit", sf::Vector2f(100.f, 40.f), sf::Vector2f(170.f, 80.f),
        [this] { currentMode = Mode::Edit; resetInputs(); drawInputs(window); });
    buttons.emplace_back(font, "Delete", sf::Vector2f(100.f, 40.f), sf::Vector2f(290.f, 80.f),
        [this] { currentMode = Mode::Delete; resetInputs(); drawInputs(window); });
    buttons.emplace_back(font, "Save", sf::Vector2f(100.f, 40.f), sf::Vector2f(410.f, 80.f),
        [this] { FileManager::save(manager.getAll(), "data/transactions.txt"); });
    buttons.emplace_back(font, "Load", sf::Vector2f(100.f, 40.f), sf::Vector2f(530.f, 80.f),
        [this] { FileManager::load(manager.getAll(), "data/transactions.txt"); });
    buttons.emplace_back(font, "Monthly Summary", sf::Vector2f(190.f, 40.f), sf::Vector2f(650.f, 80.f),
        [this] { currentMode = Mode::Summary; resetInputs(); drawInputs(window); });
    buttons.emplace_back(font, "Confirm", sf::Vector2f(100.f, 40.f), sf::Vector2f(860.f, 80.f),
        [this] { onConfirm(); });
    buttons.emplace_back(font, "Cancel", sf::Vector2f(100.f, 40.f), sf::Vector2f(980.f, 80.f),
        [this] { currentMode = Mode::None; resetInputs(); });
    


}

void Gui::resetInputs() {
    typeIncome = typeExpense = false;
    category = -1;
    amount = 0.0;
    amountStr.clear();
    date.clear();
    inputID = 0;
}

void Gui::drawInputs(sf::RenderTarget& target) {
    inputHitboxes.clear();
    if (currentMode == Mode::None) return;

    float y = 150.f;

    sf::Text title(font, "", 22);
    title.setFillColor(sf::Color::White);

    if (currentMode == Mode::Add) title.setString("Add Transaction");
    else if (currentMode == Mode::Edit) title.setString("Edit Transaction");
    else if (currentMode == Mode::Delete) title.setString("Delete Transaction");

    title.setPosition(sf::Vector2f(50.f, y)); y += 40.f;
    target.draw(title);

    if (currentMode == Mode::Edit || currentMode == Mode::Delete)
    {
        sf::Text idLabel(font, "ID: " + std::to_string(inputID), 20);
        idLabel.setPosition(sf::Vector2f(50.f, y));
        y += 30.f;
        sf::FloatRect r = idLabel.getGlobalBounds();

        InputBox box;
        box.bounds = r;
        box.label = "id";
        box.isActive = (activeInputField == ActiveField::ID);
        inputHitboxes.push_back(box);

        drawTextBox(target, r, box.isActive);
        target.draw(idLabel);
    }

    if (currentMode == Mode::Add || currentMode == Mode::Edit) {
        sf::Text typeLabel(font, "Type:",  20); typeLabel.setFillColor(sf::Color::White); typeLabel.setPosition(sf::Vector2f(50.f, y)); y += 30.f;
        target.draw(typeLabel);

        sf::Text income(font, "Income", 20);
        income.setFillColor(typeIncome ? sf::Color::Green : sf::Color::White);
        income.setPosition(sf::Vector2f(70.f, y));
        target.draw(income);
        inputHitboxes.push_back({ income.getGlobalBounds(), "income" });

        sf::Text expense(font, "Expense", 20);
        expense.setFillColor(typeExpense ? sf::Color::Red : sf::Color::White);
        expense.setPosition(sf::Vector2f(200.f, y));
        target.draw(expense);
        inputHitboxes.push_back({ expense.getGlobalBounds(), "expense" });
        y += 30.f;

        sf::Text catLabel(font, "Category:",  20); catLabel.setFillColor(sf::Color::White); catLabel.setPosition(sf::Vector2f(50.f, y)); y += 30.f;
        target.draw(catLabel);
        const char* cats[4] = { "Food","Transportation","Rent","Other" };
        for (int i = 0; i < 4; i++) {
            sf::Text c(font, cats[i], 20);
            c.setFillColor(category == i ? sf::Color::Green : sf::Color::White);
            c.setPosition(sf::Vector2f(70.f + i * 150.f, y));
            target.draw(c);

            inputHitboxes.push_back({
                c.getGlobalBounds(),
                "cat" + std::to_string(i)
                });
        }
        y += 50.f;

        sf::Text amt(font, "Amount: " + amountStr, 20);
        amt.setPosition(sf::Vector2f(50.f, y));
        y += 40.f;
        sf::FloatRect r2 = amt.getGlobalBounds();

        InputBox box2;
        box2.bounds = r2;
        box2.label = "amount";
        box2.isActive = (activeInputField == ActiveField::Amount);
        inputHitboxes.push_back(box2);

        drawTextBox(target, r2, box2.isActive);
        target.draw(amt);


        sf::Text dt(font, "Date: " + date, 20);
        dt.setPosition(sf::Vector2f(50.f, y));
        y += 40.f;
		sf::FloatRect r3 = dt.getGlobalBounds();

        InputBox box3;
		box3.bounds = r3;
		box3.label = "date";
		box3.isActive = (activeInputField == ActiveField::Date);
		inputHitboxes.push_back(box3);

		drawTextBox(target, r3, box3.isActive);
        target.draw(dt);

    }
    if (Mode::Summary == currentMode)
    {
        sf::Text mt(font, "Month: " + monthInput, 20);
        mt.setPosition(sf::Vector2f(50.f, y));
        sf::FloatRect r4(sf::Vector2f{ 50.f, y }, sf::Vector2f{ 250.f, 35.f });
        y += 40.f;
        

        InputBox box4;
        box4.bounds = r4;
        box4.label = "month";
        box4.isActive = (activeInputField == ActiveField::Month);
        inputHitboxes.push_back(box4);

        drawTextBox(target, r4, box4.isActive);
        target.draw(mt);

        sf::RectangleShape genBtn;
        genBtn.setSize({ 140.f, 40.f });
        genBtn.setPosition({ 1160.f, 200.f });
        genBtn.setFillColor(sf::Color(60, 60, 60));
        genBtn.setOutlineThickness(2);
        genBtn.setOutlineColor(sf::Color::White);

        target.draw(genBtn);

        sf::Text bt(font, "Generate" , 20);
        bt.setPosition(sf::Vector2f(1180.f, 205.f));
        bt.setFillColor(sf::Color::White);
        target.draw(bt);

        // Add hitbox
        buttonHitboxes.push_back({
            genBtn.getGlobalBounds(),
            "generateSummary"
            });
        if (!summaryText.empty()) {
            float summaryY = 300.f;
            float summaryX = 50.f;

            std::istringstream iss(summaryText);
            std::string line;
            while (std::getline(iss, line)) {
                sf::Text txt(font, line, 18);
                txt.setFillColor(sf::Color::White);
                txt.setPosition(sf::Vector2f(summaryX, summaryY));
                target.draw(txt);
                summaryY += 22.f;
            }
        }
    }

}

void Gui::onConfirm()
{
    if (currentMode == Mode::Add)
    {
        if (!typeIncome && !typeExpense) return;
        if (category < 0) return;

        std::string tType = typeIncome ? "income" : "expense";
        std::string tCat;

        switch (category)
        {
        case 0: tCat = "Food"; break;
        case 1: tCat = "Transportation"; break;
        case 2: tCat = "Rent"; break;
        case 3: tCat = "Other"; break;
        }

        manager.addTransaction(tType, tCat, amount, date);
    }

    else if (currentMode == Mode::Edit)
    {
        std::string tType = typeIncome ? "income" : "expense";
        std::string tCat;

        switch (category)
        {
        case 0: tCat = "Food"; break;
        case 1: tCat = "Transportation"; break;
        case 2: tCat = "Rent"; break;
        case 3: tCat = "Other"; break;
        }

        manager.editTransaction(inputID, tType, tCat, amount, date);
    }

    else if (currentMode == Mode::Delete)
    {
        manager.deleteTransaction(inputID);
    }

    currentMode = Mode::None;
    resetInputs();
}

void Gui::drawTextBox(sf::RenderTarget& target, const sf::FloatRect& r, bool active)
{
    sf::RectangleShape box;
    box.setSize({ r.size.x + 10.f, r.size.y + 10.f });
    box.setPosition({ r.position.x - 5.f, r.position.y - 5.f });
    box.setFillColor(active ? sf::Color(60, 120, 255) : sf::Color(70, 70, 70));
    box.setOutlineThickness(2.f);
    box.setOutlineColor(active ? sf::Color::White : sf::Color(120, 120, 120));
    target.draw(box);
}

void Gui::updateMonthlySummary(const std::string& yearMonth)
{
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    manager.showMonthlySummary(yearMonth);

    std::cout.rdbuf(oldCout);

    summaryText = oss.str();
}

void Gui::run()
{
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                continue;
            }

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                const auto* e = event->getIf<sf::Event::MouseButtonPressed>();

                sf::Vector2f mp(
                    static_cast<float>(e->position.x),
                    static_cast<float>(e->position.y)
                );

                for (auto& btn : buttons)
                {
                    if (btn.contains(mp))
                    {
                        btn.onClick();
                        goto nextEvent; 
                    }
                }

                for (auto& b : buttonHitboxes)
                {
                    if (b.bounds.contains(mp))
                    {
                        if (b.label == "generateSummary")
                        {
                            updateMonthlySummary(monthInput);
                        }
                    }
                }


                for (auto& box : inputHitboxes)
                {
                    if (box.bounds.contains(mp))
                    {
                        for (auto& b : inputHitboxes)
                            b.isActive = false;
                        box.isActive = true;

                        if (box.label == "income") {
                            typeIncome = true;
                            typeExpense = false;
                        }
                        else if (box.label == "expense") {
                            typeIncome = false;
                            typeExpense = true;
                        }
                        else if (box.label.rfind("cat", 0) == 0) {
                            category = std::stoi(box.label.substr(3));
                        }
                        else if (box.label == "id") {
                            activeInputField = ActiveField::ID;
                        }
                        else if (box.label == "amount") {
                            activeInputField = ActiveField::Amount;
                        }
                        else if (box.label == "date") {
                            activeInputField = ActiveField::Date;
                        }
                        else if (box.label == "month") {
                            activeInputField = ActiveField::Month;
                        }

                        break;
                    }
                }

            nextEvent:;

                continue;
            }

            if (event->is<sf::Event::TextEntered>())
            {
                const auto* e = event->getIf<sf::Event::TextEntered>();
                char32_t unicode = e->unicode;

                switch (activeInputField)
                {
                case ActiveField::ID:
                    if (unicode >= '0' && unicode <= '9') {
                        inputID = inputID * 10 + (unicode - '0');
                    }
                    else if (unicode == 8) { 
                        inputID /= 10; 
                    }
                    break;

                case ActiveField::Amount:
                    if ((unicode >= '0' && unicode <= '9') || unicode == '.')
                    {
                        if (unicode == '.' && amountStr.find('.') != std::string::npos)
                            break;

                        amountStr += static_cast<char>(unicode);

                        try {
                            amount = std::stod(amountStr);
                        }
                        catch (...) {
                            amount = 0;
                        }
                    }
                    else if (unicode == 8)
                    {
                        if (!amountStr.empty())
                        {
                            amountStr.pop_back();
                            try {
                                amount = amountStr.empty() ? 0 : std::stod(amountStr);
                            }
                            catch (...) {
                                amount = 0;
                            }
                        }
                    }
                    break;

                case ActiveField::Date:
                    if ((unicode >= '0' && unicode <= '9') || unicode == '-' || unicode == '/') {
                        date += static_cast<char>(unicode);
                    }
                    else if (unicode == 8) {
                        if (!date.empty()) {
                            date.pop_back();
                        }
                    }
                    break;

                case ActiveField::Month:
                    if (unicode == 8) { 
                        if (!monthInput.empty())
                            monthInput.pop_back();
                    }
                    else if (unicode < 128) {
                        char c = static_cast<char>(unicode);
                        if (std::isdigit(c) || c == '-') {
                            if (monthInput.size() < 8)
                                monthInput.push_back(c);
                        }
                    }
                    break;


                case ActiveField::TypeIncome:
                    typeIncome = true;
                    typeExpense = false;
                    break;

                case ActiveField::TypeExpense:
                    typeIncome = false;
                    typeExpense = true;
                    break;

                case ActiveField::Cat0:
                case ActiveField::Cat1:
                case ActiveField::Cat2:
                case ActiveField::Cat3:
                    category = static_cast<int>(activeInputField) - static_cast<int>(ActiveField::Cat0);
                    break;

                default:
                    break;
                }

                continue;
            }

            if (auto* resized = event->getIf<sf::Event::Resized>())
            {
                continue;
            }
        }

        window.clear(sf::Color(50, 50, 50));

        sf::Text net(font, "hello");
        net.setFont(font);
        net.setString("Net Total: " + std::to_string(manager.getTotalBalance()));
        net.setCharacterSize(24);
        net.setFillColor(sf::Color::White);
        net.setPosition(sf::Vector2f(50.f, 30.f));
        window.draw(net);

        for (auto& btn : buttons)
            btn.draw(window);

        drawInputs(window);

        window.display();
    }
}


