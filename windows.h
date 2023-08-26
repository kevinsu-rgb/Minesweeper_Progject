#ifndef PROJECT3_WINDOWS_H
#define PROJECT3_WINDOWS_H
#endif //PROJECT3_WINDOWS_H
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#include "fstream"
#include <string>
#include <sstream>
#include "queue"
#include <stack>

bool compare_values(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second < b.second; // compare the second element of each pair (i.e., the time)
}

string transform(int value){
    stringstream String_Test;
    string Real_string;
    int test_minutes = value / 60;
    int test_seconds = value % 60;
    if (test_minutes < 10 && test_seconds >= 10) {
        String_Test << "0" << to_string(test_minutes) << ":" << to_string(test_seconds);
        string Real_string = String_Test.str();
        return Real_string;
    }
    else if (test_minutes < 10 && test_seconds < 10){
        String_Test << "0" << to_string(test_minutes) << ":" << "0" << to_string(test_seconds);
        string Real_string = String_Test.str();
        return Real_string;
    }
    else if (test_minutes >= 10 && test_seconds < 10){
        String_Test << to_string(test_minutes) << ":" << "0" << to_string(test_seconds);
        string Real_string = String_Test.str();
        return Real_string;
    }
    else if (test_minutes >= 10){
        String_Test << to_string(test_minutes) << ":" << to_string(test_seconds);
        string Real_string = String_Test.str();
        return Real_string;
    }
}

void leaderboard_window(int columns, int rows, string Name, int player_time){
    if (Name.find("*") != string::npos){
        Name.substr(0, Name.size() - 1);
    }
    Name += "*";

    string data;
    string name;
    string time;
    int place;
    string minutes;
    string seconds;
    int total_seconds;

    sf::RenderWindow Leaderboard_screen(sf::VideoMode(16 * columns, (rows * 16) + 50), "Minesweeper");
    Leaderboard_screen.setFramerateLimit(60);
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    sf::Text Title;
    Title.setString("LEADERBOARD");
    Title.setFont(font);
    Title.setCharacterSize(20);
    Title.setFillColor(sf::Color::White);
    Title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect Title_Rect = Title.getLocalBounds();
    Title.setOrigin(Title_Rect.left + Title_Rect.width / 2.0f,Title_Rect.top  + Title_Rect.height / 2.0f);
    Title.setPosition(Leaderboard_screen.getSize().x/2.0f,Leaderboard_screen.getSize().y/2.0f - 120);

    vector<pair<string, int>> given_data;
    fstream leaderboard_data("files/leaderboard.txt", ios_base::in);

    for (unsigned int i = 0; i < 6; i++) {
        getline(leaderboard_data, data);
        stringstream str(data);
        getline(str, time, ',');
        stringstream stra(time);
        getline(stra, minutes, ':');
        getline(stra, seconds, ':');
        total_seconds = (stoi(minutes) * 60) + stoi(seconds);
        getline(str, name, ',');

        given_data.push_back({name,total_seconds});
    }
    given_data.push_back({Name, player_time});

    sort(given_data.begin(), given_data.end(), compare_values);

    stringstream String_data;
    String_data << "1." << "\t" << transform(given_data.at(0).second) << "\t" << given_data.at(0).first << "\n" << "\n" << "2." << "\t" << transform(given_data.at(1).second) << "\t" << given_data.at(1).first << "\n" << "\n" << "3." << "\t" << transform(given_data.at(2).second) << "\t" << given_data.at(2).first << "\n" << "\n" << "4." << "\t" << transform(given_data.at(3).second) << "\t" << given_data.at(3).first << "\n" << "\n" << "5." << "\t" << transform(given_data.at(4).second) << "\t" << given_data.at(4).first << "\n" << "\n" ;
    string Real_string = String_data.str();
    sf::Text First;
    First.setString(Real_string);
    First.setFont(font);
    First.setCharacterSize(18);
    First.setFillColor(sf::Color::White);
    First.setStyle(sf::Text::Bold);
    sf::FloatRect Firstrect = First.getLocalBounds();
    First.setOrigin(Firstrect.left + Firstrect.width / 2.0f,Firstrect.top  + Firstrect.height / 2.0f);
    First.setPosition(Leaderboard_screen.getSize().x/2.0f,Leaderboard_screen.getSize().y/2.0f + 20);
    leaderboard_data.close();

    ofstream file;
    file.open("files/leaderboard.txt", ios::trunc);
    file.close();

    ofstream output;
    output.open("files/leaderboard.txt");
    output << transform(given_data[0].second) << "," << given_data[0].first << endl << transform(given_data[1].second) << "," << given_data[1].first << endl << transform(given_data[2].second) << "," << given_data[2].first << endl << transform(given_data[3].second) << "," << given_data[3].first << endl << transform(given_data[4].second) << "," << given_data[4].first;
    output.close();


    while (Leaderboard_screen.isOpen()) {
        sf::Event event;
        while (Leaderboard_screen.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Leaderboard_screen.close();
            }
        }
        Leaderboard_screen.clear(Color::Blue);
        Leaderboard_screen.draw(First);
        Leaderboard_screen.draw(Title);
        Leaderboard_screen.display();

    }
}

void startwindow(string &Name, bool &game_closed){
    string Data;
    int width;
    int height;
    fstream Board_config("files/board_config.cfg", ios_base::in);
    getline(Board_config,Data);
    width = stoi(Data) * 32;
    getline(Board_config,Data);
    height = (stoi(Data) * 32) + 100;
    getline(Board_config,Data);

    sf::RenderWindow Welcomewindow(sf::VideoMode(width, height), "Minesweeper");
    Welcomewindow.setFramerateLimit(60);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(width,height));
    rect.setPosition(0,0);
    rect.setOrigin(0,0);
    rect.setFillColor(sf::Color(0,0,255));

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    sf::Text starttext;
    starttext.setString("WELCOME TO MINESWEEPER!");
    starttext.setFont(font);
    starttext.setCharacterSize(24);
    starttext.setFillColor(sf::Color::White);
    starttext.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::FloatRect starttextRect = starttext.getLocalBounds();
    starttext.setOrigin(starttextRect.left + starttextRect.width / 2.0f,starttextRect.top  + starttextRect.height / 2.0f);
    starttext.setPosition(Welcomewindow.getSize().x/2.0f,Welcomewindow.getSize().y/2.0f - 150);

    sf::Text Prompttext;
    Prompttext.setString("Enter your name:");
    Prompttext.setFont(font);
    Prompttext.setCharacterSize(20);
    Prompttext.setFillColor(sf::Color::White);
    Prompttext.setStyle(sf::Text::Bold);
    sf::FloatRect PrompttextRect = Prompttext.getLocalBounds();
    Prompttext.setOrigin(PrompttextRect.left + PrompttextRect.width / 2.0f,PrompttextRect.top  + PrompttextRect.height / 2.0f);
    Prompttext.setPosition(Welcomewindow.getSize().x/2.0f,Welcomewindow.getSize().y/2.0f - 75);

    sf::Text enterText;
    enterText.setString("|");
    enterText.setFont(font);
    enterText.setCharacterSize(18);
    enterText.setFillColor(sf::Color::Yellow);
    enterText.setStyle(sf::Text::Bold);
    sf::FloatRect entertextRect = enterText.getLocalBounds();
    enterText.setOrigin(entertextRect.left + entertextRect.width / 2.0f,entertextRect.top  + entertextRect.height / 2.0f);
    enterText.setPosition(Welcomewindow.getSize().x/2.0f,Welcomewindow.getSize().y/2.0f - 45);

    while (Welcomewindow.isOpen())
    {
        sf::Event event;
        while (Welcomewindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                game_closed = true;
                Welcomewindow.close();
            }
            if (event.type == sf::Event::TextEntered){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                    if (Name == ""){
                        continue;
                    }
                    else{
                        Name.pop_back();
                        enterText.setString(Name + "|");
                        sf::FloatRect entertextRect = enterText.getLocalBounds();
                        enterText.setOrigin(entertextRect.left + entertextRect.width / 2.0f,entertextRect.top  + entertextRect.height / 2.0f);
                        enterText.setPosition(Welcomewindow.getSize().x/2.0f,Welcomewindow.getSize().y/2.0f - 45);
                    }
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (Name == ""){
                        continue;
                    }
                    else{
                        Name[0] = toupper(Name[0]);
                        for (unsigned int i = 1; i < Name.size(); i++){
                            Name[i] = tolower(Name[i]);
                        }
                        Welcomewindow.close();
                    }
                }
                else if (((97 <= event.text.unicode and event.text.unicode <= 122) or (65 <= event.text.unicode and event.text.unicode <= 90)) && Name.size() < 10) {
                    if (Name == ""){
                        Name += toupper(event.text.unicode);
                    }
                    else{
                        Name += tolower(event.text.unicode);
                    }
                    enterText.setString(Name + "|");
                    sf::FloatRect entertextRect = enterText.getLocalBounds();
                    enterText.setOrigin(entertextRect.left + entertextRect.width / 2.0f,entertextRect.top  + entertextRect.height / 2.0f);
                    enterText.setPosition(Welcomewindow.getSize().x/2.0f,Welcomewindow.getSize().y/2.0f - 45);
                }
                else{
                    continue;
                }
            }
            Welcomewindow.clear();
            Welcomewindow.draw(rect);
            Welcomewindow.draw(starttext);
            Welcomewindow.draw(Prompttext);
            Welcomewindow.draw(enterText);
            Welcomewindow.display();
        }
    }
}
void gamewindow(string &Name){
    int times_end = 0;
    int waste = 59999;
    int minutes;
    int seconds_left;
    int offset;
    sf::Clock clock;
    bool leaderboard_check = false;
    bool game_pause = false;
    bool game_win = false;
    bool game_loss = false;
    string Data;
    int width;
    int height;
    int num_mines;
    fstream Board_config("files/board_config.cfg", ios_base::in);
    getline(Board_config,Data);
    int columns = stoi(Data);
    width = columns * 32;
    getline(Board_config,Data);
    int rows = stoi(Data);
    height = (rows * 32) + 100;
    getline(Board_config,Data);
    num_mines = stoi(Data);

    sf::RenderWindow Gamewindow(sf::VideoMode(width, height), "Minesweeper");
    Gamewindow.setFramerateLimit(60);

    sf::Texture debug;
    debug.loadFromFile("files/images/debug.png");
    sf::Sprite debug_image(debug);

    sf::Texture face_happy;
    face_happy.loadFromFile("files/images/face_happy.png");
    sf::Sprite face_happy_image(face_happy);

    sf::Texture face_lose;
    face_lose.loadFromFile("files/images/face_lose.png");
    sf::Sprite face_lose_image(face_lose);

    sf::Texture face_win;
    face_win.loadFromFile("files/images/face_win.png");
    sf::Sprite face_win_image(face_win);

    sf::Texture flag;
    flag.loadFromFile("files/images/flag.png");
    sf::Sprite flag_image(flag);

    sf::Texture leaderboard;
    leaderboard.loadFromFile("files/images/leaderboard.png");
    sf::Sprite leaderboard_image(leaderboard);

    sf::Texture pause;
    pause.loadFromFile("files/images/pause.png");
    sf::Sprite pause_image(pause);

    sf::Texture play;
    play.loadFromFile("files/images/play.png");
    sf::Sprite play_image(play);

    sf::Texture hidden;
    hidden.loadFromFile("files/images/tile_hidden.png");
    sf::Sprite hidden_tile(hidden);

    sf::Texture revealed;
    revealed.loadFromFile("files/images/tile_revealed.png");
    sf::Sprite revealed_tile(revealed);

    sf::Texture mine;
    mine.loadFromFile("files/images/mine.png");
    sf::Sprite Mine_Image(mine);

    sf::Texture num_1;
    num_1.loadFromFile("files/images/number_1.png");
    sf::Sprite Num_1_Image(num_1);

    sf::Texture num_2;
    num_2.loadFromFile("files/images/number_2.png");
    sf::Sprite Num_2_Image(num_2);

    sf::Texture num_3;
    num_3.loadFromFile("files/images/number_3.png");
    sf::Sprite Num_3_Image(num_3);

    sf::Texture num_4;
    num_4.loadFromFile("files/images/number_4.png");
    sf::Sprite Num_4_Image(num_4);

    sf::Texture num_5;
    num_5.loadFromFile("files/images/number_5.png");
    sf::Sprite Num_5_Image(num_5);

    sf::Texture num_6;
    num_6.loadFromFile("files/images/number_6.png");
    sf::Sprite Num_6_Image(num_6);

    sf::Texture num_7;
    num_7.loadFromFile("files/images/number_7.png");
    sf::Sprite Num_7_Image(num_7);

    sf::Texture num_8;
    num_8.loadFromFile("files/images/number_8.png");
    sf::Sprite Num_8_Image(num_8);

    sf::Texture digits;
    digits.loadFromFile("files/images/digits.png");
    sf::Sprite Digits_image(digits);


    int Minesweeper_board[rows][columns];
    int actual_Minesweeper_board[rows][columns];
    int temp_board[rows][columns];
    int mine_counter = 0;

    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            actual_Minesweeper_board[i][j] = 10;
            Minesweeper_board[i][j] = 0;

        }
    }
    while (mine_counter < num_mines) {
        int i = rand() % rows;
        int j = rand() % columns;
        if (Minesweeper_board[i][j] != 9) {
            Minesweeper_board[i][j] = 9;
            mine_counter += 1;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (Minesweeper_board[i][j] != 9) {
                int Mines_near = 0;
                if (i > 0 && j > 0 && Minesweeper_board[i - 1][j - 1] == 9) {
                    Mines_near += 1;
                }
                if (i > 0 && Minesweeper_board[i - 1][j] == 9) {
                    Mines_near += 1;
                }
                if (i > 0 && j < columns - 1 && Minesweeper_board[i - 1][j + 1] == 9) {
                    Mines_near += 1;
                }
                if (j > 0 && Minesweeper_board[i][j - 1] == 9) {
                    Mines_near += 1;
                }
                if (j < columns - 1 && Minesweeper_board[i][j + 1] == 9) {
                    Mines_near += 1;
                }
                if (i < rows - 1 && j > 0 && Minesweeper_board[i + 1][j - 1] == 9) {
                    Mines_near += 1;
                }
                if (i < rows - 1 && Minesweeper_board[i + 1][j] == 9) {
                    Mines_near += 1;
                }
                if (i < rows - 1 && j < columns - 1 && Minesweeper_board[i + 1][j + 1] == 9) {
                    Mines_near += 1;
                }
                Minesweeper_board[i][j] = Mines_near;
            }
        }
    }

    int final_ultra_seconds;
    int debug_Num_clicks = 1;
    int flags_placed = 0;
    int play_clicks = 1;
    int Leaderboard_clicks = 1;

    int final_minute = 0;
    int final_second = 0;

    while (Gamewindow.isOpen()) {
        sf::Time elapsed = clock.getElapsedTime();

        Vector2i pos = Mouse::getPosition(Gamewindow);
        int x_coordinates = pos.x / 32;
        int y_coordinates = pos.y / 32;

        int seconds = elapsed.asSeconds();
        seconds += offset;

        Gamewindow.clear(Color::White);

        debug_image.setPosition((columns * 32) - 304, 32 * (rows + 0.5f));
        FloatRect Debug_button_bounds = debug_image.getGlobalBounds();
        Gamewindow.draw(debug_image);

        leaderboard_image.setPosition((columns * 32) - 176, 32 * (rows + 0.5f));
        FloatRect Leaderboard_bounds = leaderboard_image.getGlobalBounds();
        Gamewindow.draw(leaderboard_image);

        if (game_loss == false && game_win == false) {
            face_happy_image.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));
            Gamewindow.draw(face_happy_image);
        }
        else if (game_loss == true){
            face_lose_image.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));
            Gamewindow.draw(face_lose_image);
        }
        else if (game_win == true){
            face_win_image.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));
            Gamewindow.draw(face_win_image);
        }

        if (game_pause == false){
            pause_image.setPosition((columns * 32) - 240, 32 * (rows + 0.5f));
            Gamewindow.draw(pause_image);
        }
        else if (game_pause == true){
            play_image.setPosition((columns * 32) - 240, 32 * (rows + 0.5f));
            Gamewindow.draw(play_image);
        }

        FloatRect pause_play_button = pause_image.getGlobalBounds();

        FloatRect Reset_button_happy = face_happy_image.getGlobalBounds();

        sf::Event event;

        while (Gamewindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Gamewindow.close();
            }
            if (event.type == Event::MouseButtonPressed){
                if (event.key.code == Mouse::Left) {
                    if (Leaderboard_bounds.contains(pos.x,pos.y) && leaderboard_check == false && game_win == true){
                        leaderboard_check = true;
                        offset = seconds;
                    }
                    else if (Leaderboard_bounds.contains(pos.x,pos.y) && leaderboard_check == false && game_pause == true){
                        leaderboard_check = true;
                    }
                    else if (Leaderboard_bounds.contains(pos.x,pos.y) && leaderboard_check == false){
                        leaderboard_check = true;
                             for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < columns; j++) {
                                    temp_board[i][j] = actual_Minesweeper_board[i][j];
                                }
                            }
                            for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < columns; j++) {
                                    actual_Minesweeper_board[i][j] = 0;
                                }
                            }
                            offset = seconds;
                    }
                    if (pause_play_button.contains(pos.x, pos.y) && game_loss == false && game_win == false && play_clicks % 2 != 0){
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < columns; j++) {
                                temp_board[i][j] = actual_Minesweeper_board[i][j];
                            }
                        }
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < columns; j++) {
                                actual_Minesweeper_board[i][j] = 0;
                            }
                        }
                        offset = seconds;
                        play_clicks += 1;
                        game_pause = true;
                    }
                    else if (pause_play_button.contains(pos.x, pos.y) && game_loss == false && game_win == false && play_clicks % 2 == 0) {
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < columns; j++) {
                                actual_Minesweeper_board[i][j] = temp_board[i][j];
                            }
                        }
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < columns; j++) {
                                temp_board[i][j] = 0;
                            }
                        }
                        game_pause = false;
                        play_clicks += 1;
                        clock.restart();
                    }
                    if ((game_loss == false && game_win == false && game_pause == false)){
                        if (Debug_button_bounds.contains(pos.x, pos.y) && debug_Num_clicks % 2 != 0) {
                            debug_Num_clicks += 1;
                            for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < columns; j++) {
                                    if (Minesweeper_board[i][j] == 9 && actual_Minesweeper_board[i][j] != 11) {
                                        actual_Minesweeper_board[i][j] = 12;
                                    }
                                    else if (Minesweeper_board[i][j] == 9 && actual_Minesweeper_board[i][j] == 11) {
                                        actual_Minesweeper_board[i][j] = 13;
                                    }
                                }
                            }
                        }
                        else if (Debug_button_bounds.contains(pos.x, pos.y) && debug_Num_clicks % 2 == 0 && game_pause == false) {
                            debug_Num_clicks += 1;
                            for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < columns; j++) {
                                    if (Minesweeper_board[i][j] == 9 && actual_Minesweeper_board[i][j] == 12) {
                                        actual_Minesweeper_board[i][j] = 10;
                                    }
                                    else if (Minesweeper_board[i][j] == 9 && actual_Minesweeper_board[i][j] == 13) {
                                        actual_Minesweeper_board[i][j] = 11;
                                    }
                                }
                            }
                        }
                    }
                    if (Reset_button_happy.contains(pos.x, pos.y)){
                        debug_Num_clicks = 1;
                        flags_placed = 0;
                        play_clicks = 1;
                        offset = 0;
                        Leaderboard_clicks = 1;
                        times_end = 0;
                        waste = 5999;
                        final_ultra_seconds = 0;

                        clock.restart();

                        game_win = false;
                        game_loss = false;
                        game_pause = false;
                        leaderboard_check = false;

                        int mine_counter = 0;

                        for (unsigned int i = 0; i < rows; i++) {
                            for (unsigned int j = 0; j < columns; j++) {
                                actual_Minesweeper_board[i][j] = 10;
                                Minesweeper_board[i][j] = 0;

                            }
                        }
                        while (mine_counter < num_mines) {
                            int i = rand() % rows;
                            int j = rand() % columns;
                            if (Minesweeper_board[i][j] != 9) {
                                Minesweeper_board[i][j] = 9;
                                mine_counter += 1;
                            }
                        }

                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < columns; j++) {
                                if (Minesweeper_board[i][j] != 9) {
                                    int Mines_near = 0;
                                    if (i > 0 && j > 0 && Minesweeper_board[i - 1][j - 1] == 9) {
                                        Mines_near += 1;
                                    }
                                    if (i > 0 && Minesweeper_board[i - 1][j] == 9) {
                                        Mines_near += 1;
                                    }
                                    if (i > 0 && j < columns - 1 && Minesweeper_board[i - 1][j + 1] == 9) {
                                        Mines_near += 1;
                                    }
                                    if (j > 0 && Minesweeper_board[i][j - 1] == 9) {
                                        Mines_near += 1;
                                    }
                                    if (j < columns - 1 && Minesweeper_board[i][j + 1] == 9) {
                                        Mines_near += 1;
                                    }
                                    if (i < rows - 1 && j > 0 && Minesweeper_board[i + 1][j - 1] == 9) {
                                        Mines_near += 1;
                                    }
                                    if (i < rows - 1 && Minesweeper_board[i + 1][j] == 9) {
                                        Mines_near += 1;
                                    }
                                    if (i < rows - 1 && j < columns - 1 && Minesweeper_board[i + 1][j + 1] == 9) {
                                        Mines_near += 1;
                                    }
                                    Minesweeper_board[i][j] = Mines_near;
                                }
                            }
                        }
                    }
                    if (Minesweeper_board[y_coordinates][x_coordinates] == 9 && game_loss != true && game_win != true && (actual_Minesweeper_board[y_coordinates][x_coordinates] != 11 && actual_Minesweeper_board[y_coordinates][x_coordinates] != 13)) {
                        for (int i = 0; i < rows; i++) {
                            for (int j = 0; j < columns; j++) {
                                if (Minesweeper_board[i][j] == 9 && actual_Minesweeper_board[i][j] == 11) {
                                    actual_Minesweeper_board[i][j] = 13;
                                }
                                else if (Minesweeper_board[i][j] == 9 && game_pause != true) {
                                    actual_Minesweeper_board[i][j] = 9;
                                    game_loss = true;
                                }
                            }
                        }
                    }
                    if (actual_Minesweeper_board[y_coordinates][x_coordinates] == 10 && game_loss != true && game_win != true) {
                        if (Minesweeper_board[y_coordinates][x_coordinates] == 0) {
                            stack<pair<int, int>> tiles_to_reveal;
                            int row = y_coordinates;
                            int col = x_coordinates;
                            tiles_to_reveal.push(make_pair(row, col));
                            actual_Minesweeper_board[row][col] = Minesweeper_board[row][col];
                            while (!tiles_to_reveal.empty()) {
                                pair<int, int> tile = tiles_to_reveal.top();
                                tiles_to_reveal.pop();
                                row = tile.first;
                                col = tile.second;
                                if (Minesweeper_board[row][col] == 0) {
                                    for (int i = row-1; i <= row+1; i++) {
                                        for (int j = col-1; j <= col+1; j++) {
                                            if (i >= 0 && i < rows && j >= 0 && j < columns && actual_Minesweeper_board[i][j] == 10) {
                                                actual_Minesweeper_board[i][j] = Minesweeper_board[i][j];
                                                tiles_to_reveal.push(make_pair(i, j));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else{
                            actual_Minesweeper_board[y_coordinates][x_coordinates] = Minesweeper_board[y_coordinates][x_coordinates];
                        }
                    }
                    else if (game_loss != true && game_win != true && (actual_Minesweeper_board[y_coordinates][x_coordinates] == 11)) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && (actual_Minesweeper_board[y_coordinates][x_coordinates] == 13)) {
                        continue;
                    }
                }
                else if (event.key.code == Mouse::Right){
                    if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 11) {
                        flags_placed -= 1;
                        actual_Minesweeper_board[y_coordinates][x_coordinates] = 10;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 13) {
                        flags_placed -= 1;
                        actual_Minesweeper_board[y_coordinates][x_coordinates] = 12;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 0) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 1) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 2) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 3) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 4) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 5) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 6) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 7) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 8) {
                        continue;
                    }
                    else if (game_loss != true && game_win != true && (actual_Minesweeper_board[y_coordinates][x_coordinates] == 12)){
                        flags_placed += 1;
                        actual_Minesweeper_board[y_coordinates][x_coordinates] = 13;
                    }
                    else if (game_loss != true && game_win != true && actual_Minesweeper_board[y_coordinates][x_coordinates] == 10){
                        flags_placed += 1;
                        actual_Minesweeper_board[y_coordinates][x_coordinates] = 11;
                    }
                }
            }
        }
        int found = 0;
        if (game_win == false && game_loss == false && game_pause == false && leaderboard_check == false){
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    if (actual_Minesweeper_board[i][j] == 1) {
                        found += 1;
                    }
                    else if (actual_Minesweeper_board[i][j] == 2) {
                        found += 1;

                    }
                    else if (actual_Minesweeper_board[i][j] == 3) {
                        found += 1;

                    }
                    else if (actual_Minesweeper_board[i][j] == 4) {
                        found += 1;

                    }
                    else if (actual_Minesweeper_board[i][j] == 5) {
                        found += 1;

                    }
                    else if (actual_Minesweeper_board[i][j] == 6) {
                        found += 1;

                    }
                    else if (actual_Minesweeper_board[i][j] == 7) {
                        found += 1;
                    }
                    else if (actual_Minesweeper_board[i][j] == 8) {
                        found += 1;
                    }
                    else if (actual_Minesweeper_board[i][j] == 0) {
                        found += 1;
                    }
                    else if (actual_Minesweeper_board[i][j] == 11 && Minesweeper_board[i][j] == 9) {
                        found += 1;
                    }
                    else if (actual_Minesweeper_board[i][j] == 10 && Minesweeper_board[i][j] == 9) {
                        found += 1;
                    }
                    else if (actual_Minesweeper_board[i][j] == 13) {
                        found += 1;
                    }
                    else if (actual_Minesweeper_board[i][j] == 12) {
                        found += 1;
                    }
                }

            }
            if (found == ((columns * rows))) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        if (actual_Minesweeper_board[i][j] == 13){
                            actual_Minesweeper_board[i][j] = 11;
                        }
                        if (Minesweeper_board[i][j] == 9 && (actual_Minesweeper_board[i][j] == 10)){
                            flags_placed += 1;
                            actual_Minesweeper_board[i][j] = 11;
                        }
                        else if (actual_Minesweeper_board[i][j] == 12) {
                            flags_placed += 1;
                            actual_Minesweeper_board[i][j] = 11;                        }
                    }
                }
                game_win = true;
                leaderboard_check = true;
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (actual_Minesweeper_board[i][j] == 9) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Mine_Image.setPosition(j * 32, i * 32);
                    Mine_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Mine_Image);
                }
                else if (actual_Minesweeper_board[i][j] == 12) {
                    hidden_tile.setPosition(j * 32, i * 32);
                    hidden_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(hidden_tile);
                    Mine_Image.setPosition(j * 32, i * 32);
                    Mine_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Mine_Image);
                }
                else if (actual_Minesweeper_board[i][j] == 1) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Num_1_Image.setPosition(j * 32, i * 32);
                    Num_1_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Num_1_Image);
                } else if (actual_Minesweeper_board[i][j] == 2) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Num_2_Image.setPosition(j * 32, i * 32);
                    Num_2_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Num_2_Image);
                } else if (actual_Minesweeper_board[i][j] == 3) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Num_3_Image.setPosition(j * 32, i * 32);
                    Num_3_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Num_3_Image);
                } else if (actual_Minesweeper_board[i][j] == 4) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Num_4_Image.setPosition(j * 32, i * 32);
                    Num_4_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Num_4_Image);
                } else if (actual_Minesweeper_board[i][j] == 5) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Num_5_Image.setPosition(j * 32, i * 32);
                    Num_5_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Num_5_Image);
                } else if (actual_Minesweeper_board[i][j] == 6) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Num_6_Image.setPosition(j * 32, i * 32);
                    Num_6_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Num_6_Image);
                } else if (actual_Minesweeper_board[i][j] == 7) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Num_7_Image.setPosition(j * 32, i * 32);
                    Num_7_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Num_7_Image);
                }
                else if (actual_Minesweeper_board[i][j] == 8) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                    Num_8_Image.setPosition(j * 32, i * 32);
                    Num_8_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Num_8_Image);
                }
                else if (actual_Minesweeper_board[i][j] == 0) {
                    revealed_tile.setPosition(j * 32, i * 32);
                    revealed_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(revealed_tile);
                }
                else if (actual_Minesweeper_board[i][j] == 10) {
                    hidden_tile.setPosition(j * 32, i * 32);
                    Gamewindow.draw(hidden_tile);
                }
                else if (actual_Minesweeper_board[i][j] == 11) {
                    hidden_tile.setPosition(j * 32, i * 32);
                    hidden_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(hidden_tile);
                    flag_image.setPosition(j * 32, i * 32);
                    flag_image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(flag_image);
                }
                else if (actual_Minesweeper_board[i][j] == 13) {
                    hidden_tile.setPosition(j * 32, i * 32);
                    hidden_tile.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(hidden_tile);
                    flag_image.setPosition(j * 32, i * 32);
                    flag_image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(flag_image);
                    Mine_Image.setPosition(j * 32, i * 32);
                    Mine_Image.setTextureRect(IntRect(0, 0, 32, 32));
                    Gamewindow.draw(Mine_Image);
                }
            }
        }

        int test = num_mines - flags_placed;
        if (to_string(test).find("-") != string::npos){
            int counter = 1;
            Digits_image.setPosition(12, 32 * ((rows)+0.5f) + 16);
            Digits_image.setTextureRect(IntRect(10 * 21, 0, 21, 32));
            Gamewindow.draw(Digits_image);
            if (to_string(test).size() - 1 == 1){
                Digits_image.setPosition(33, 32 * ((rows)+0.5f) + 16);
                Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                Digits_image.setPosition(54, 32 * ((rows)+0.5f) + 16);
                Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                int digit = (test / static_cast<int>(std::pow(10, 0))) % 10;
                int change = abs(digit) * 21;
                Digits_image.setPosition(75, 32 * ((rows)+0.5f) + 16);
                Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                Gamewindow.draw(Digits_image);
            }
            else if (to_string(test).size() - 1 == 2){
                Digits_image.setPosition(33, 32 * ((rows)+0.5f) + 16);
                Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                string test_string = to_string(test);
                int counter = 0;
                for (int i = 1; i >= 0; i--) {
                    counter += 1;
                    int digit = (test / static_cast<int>(std::pow(10, i))) % 10;
                    int change = abs(digit) * 21;
                    Digits_image.setPosition(33 + (21 * counter), 32 * ((rows)+0.5f) + 16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                }
            }
            else if (to_string(test).size() - 1 == 3){
                int counter = 0;
                for (int i = to_string(test).size() - 2; i >= 0; i--) {
                    int digit = (test / static_cast<int>(std::pow(10, i))) % 10;
                    int change = abs(digit) * 21;
                    Digits_image.setPosition(33 + (21 * counter), 32 * ((rows)+0.5f) + 16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    counter += 1;
                }
            }
        }
        else if (to_string(test).size() == 1){
            Digits_image.setPosition(33, 32 * ((rows)+0.5f) + 16);
            Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
            Gamewindow.draw(Digits_image);
            Digits_image.setPosition(54, 32 * ((rows)+0.5f) + 16);
            Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
            Gamewindow.draw(Digits_image);
            int change = test * 21;
            Digits_image.setPosition(75, 32 * ((rows)+0.5f) + 16);
            Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
            Gamewindow.draw(Digits_image);
        }
        else if (to_string(test).size() == 2){
            Digits_image.setPosition(33, 32 * ((rows)+0.5f) + 16);
            Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
            Gamewindow.draw(Digits_image);
            string test_string = to_string(test);
            int counter = 0;
            for (int i = 2 - 1; i >= 0; i--) {
                counter += 1;
                int digit = (test / static_cast<int>(std::pow(10, i))) % 10;
                int change = digit * 21;
                Digits_image.setPosition(33 + (21 * counter), 32 * ((rows)+0.5f) + 16);
                Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                Gamewindow.draw(Digits_image);
            }
        }
        else if (to_string(test).size() == 3){
            int counter = 0;
            for (int i = 3 - 1; i >= 0; i--) {
                counter += 1;
                int digit = (test / static_cast<int>(std::pow(10, i))) % 10;
                int change = digit * 21;
                Digits_image.setPosition(33 + (21 * counter), 32 * ((rows)+0.5f) + 16);
                Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                Gamewindow.draw(Digits_image);
            }
        }
        if (game_pause == true){
            if (final_minute == 0 && final_second >= 0){
                Digits_image.setPosition(((columns)*32)-97, 32*((rows)+0.5f)+16);
                Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                Digits_image.setPosition(((columns)*32)-76, 32*((rows)+0.5f)+16);
                Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                int counter = 0;
                for (int i = 1; i >= 0; i--) {
                    int digit = (final_second / static_cast<int>(std::pow(10, i))) % 10;
                    int change = digit * 21;
                    Digits_image.setPosition(((columns)*32)-54 + (counter * 21), 32*((rows)+0.5f)+16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    counter += 1;
                }
            }
            else if (final_minute > 0 && seconds_left >= 0) {
                if (final_minute < 10) {
                    Digits_image.setPosition(((columns) * 32) - 97, 32 * ((rows) + 0.5f) + 16);
                    Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    int digit = (final_minute / static_cast<int>(std::pow(10, 0))) % 10;
                    int change = digit * 21;
                    Digits_image.setPosition(((columns) * 32) - 76, 32 * ((rows) + 0.5f) + 16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    int counter = 0;
                    for (int i = 1; i >= 0; i--) {
                        int digit = (final_second / static_cast<int>(std::pow(10, i))) % 10;
                        int change = digit * 21;
                        Digits_image.setPosition(((columns) * 32) - 54 + (counter * 21), 32 * ((rows) + 0.5f) + 16);
                        Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                        Gamewindow.draw(Digits_image);
                        counter += 1;
                    }
                }
            }
                else if (final_minute >= 10){
                    int counter = 0;
                    for (int i = 1; i >= 0; i--) {
                        int digit = (final_minute / static_cast<int>(std::pow(10, i))) % 10;
                        int change = digit * 21;
                        Digits_image.setPosition(((columns)*32)-97 + (counter * 21), 32*((rows)+0.5f)+16);
                        Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                        Gamewindow.draw(Digits_image);
                        counter += 1;
                    }
                    counter = 0;
                    for (int i = 1; i >= 0; i--) {
                        int digit = (final_second / static_cast<int>(std::pow(10, i))) % 10;
                        int change = digit * 21;
                        Digits_image.setPosition(((columns)*32)-54 + (counter * 21), 32*((rows)+0.5f)+16);
                        Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                        Gamewindow.draw(Digits_image);
                        counter += 1;
                    }
                }
        }
        else if (minutes == 0 && seconds_left >= 0  && game_win == false && game_loss == false){
            minutes = seconds / 60;
            seconds_left = seconds % 60;
            final_minute = minutes;
            final_second = seconds_left;
            Digits_image.setPosition(((columns)*32)-97, 32*((rows)+0.5f)+16);
            Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
            Gamewindow.draw(Digits_image);
            Digits_image.setPosition(((columns)*32)-76, 32*((rows)+0.5f)+16);
            Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
            Gamewindow.draw(Digits_image);
            int counter = 0;
            for (int i = 1; i >= 0; i--) {
                int digit = (seconds_left / static_cast<int>(std::pow(10, i))) % 10;
                int change = digit * 21;
                Digits_image.setPosition(((columns)*32)-54 + (counter * 21), 32*((rows)+0.5f)+16);
                Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                counter += 1;
            }
        }
        else if (minutes > 0 && seconds_left >= 0 && game_win == false && game_loss == false){
            minutes = seconds / 60;
            seconds_left = seconds % 60;
            final_minute = minutes;
            final_second = seconds_left;
            if (minutes < 10){
                Digits_image.setPosition(((columns)*32)-97, 32*((rows)+0.5f)+16);
                Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                int digit = (minutes / static_cast<int>(std::pow(10, 0))) % 10;
                int change = digit * 21;
                Digits_image.setPosition(((columns)*32)-76, 32*((rows)+0.5f)+16);
                Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                int counter = 0;
                for (int i = 1; i >= 0; i--) {
                    int digit = (seconds_left / static_cast<int>(std::pow(10, i))) % 10;
                    int change = digit * 21;
                    Digits_image.setPosition(((columns)*32)-54 + (counter * 21), 32*((rows)+0.5f)+16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    counter += 1;
                }
            }
            else if (minutes >= 10  && game_win == false && game_loss == false){
                final_minute = minutes;
                final_second = seconds_left;
                int counter = 0;
                for (int i = 1; i >= 0; i--) {
                    int digit = (minutes / static_cast<int>(std::pow(10, i))) % 10;
                    int change = digit * 21;
                    Digits_image.setPosition(((columns)*32)-97 + (counter * 21), 32*((rows)+0.5f)+16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    counter += 1;
                }
                counter = 0;
                for (int i = 1; i >= 0; i--) {
                    int digit = (seconds_left / static_cast<int>(std::pow(10, i))) % 10;
                    int change = digit * 21;
                    Digits_image.setPosition(((columns)*32)-54 + (counter * 21), 32*((rows)+0.5f)+16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    counter += 1;
                }
            }
        }
        else if (final_minute == 0 && final_second >= 0  && (game_win == true || game_loss == true)){
            Digits_image.setPosition(((columns)*32)-97, 32*((rows)+0.5f)+16);
            Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
            Gamewindow.draw(Digits_image);
            Digits_image.setPosition(((columns)*32)-76, 32*((rows)+0.5f)+16);
            Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
            Gamewindow.draw(Digits_image);
            int counter = 0;
            for (int i = 1; i >= 0; i--) {
                int digit = (final_second / static_cast<int>(std::pow(10, i))) % 10;
                int change = digit * 21;
                Digits_image.setPosition(((columns)*32)-54 + (counter * 21), 32*((rows)+0.5f)+16);
                Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                counter += 1;
            }
        }
        else if (final_minute > 0 && seconds_left >= 0 && (game_win == true || game_loss == true)){
            if (final_minute < 10){
                Digits_image.setPosition(((columns)*32)-97, 32*((rows)+0.5f)+16);
                Digits_image.setTextureRect(IntRect(0, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                int digit = (final_minute / static_cast<int>(std::pow(10, 0))) % 10;
                int change = digit * 21;
                Digits_image.setPosition(((columns)*32)-76, 32*((rows)+0.5f)+16);
                Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                Gamewindow.draw(Digits_image);
                int counter = 0;
                for (int i = 1; i >= 0; i--) {
                    int digit = (final_second / static_cast<int>(std::pow(10, i))) % 10;
                    int change = digit * 21;
                    Digits_image.setPosition(((columns)*32)-54 + (counter * 21), 32*((rows)+0.5f)+16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    counter += 1;
                }
            }
            else if (final_minute >= 10  && (game_win == true || game_loss == true)){
                int counter = 0;
                for (int i = 1; i >= 0; i--) {
                    int digit = (final_minute / static_cast<int>(std::pow(10, i))) % 10;
                    int change = digit * 21;
                    Digits_image.setPosition(((columns)*32)-97 + (counter * 21), 32*((rows)+0.5f)+16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    counter += 1;
                }
                counter = 0;
                for (int i = 1; i >= 0; i--) {
                    int digit = (final_second / static_cast<int>(std::pow(10, i))) % 10;
                    int change = digit * 21;
                    Digits_image.setPosition(((columns)*32)-54 + (counter * 21), 32*((rows)+0.5f)+16);
                    Digits_image.setTextureRect(IntRect(change, 0, 21, 32));
                    Gamewindow.draw(Digits_image);
                    counter += 1;
                }
                }
            }
        if (game_pause == false){
            pause_image.setPosition((columns * 32) - 240, 32 * (rows + 0.5f));
            Gamewindow.draw(pause_image);
        }
        if (game_pause == true){
            play_image.setPosition((columns * 32) - 240, 32 * (rows + 0.5f));
            Gamewindow.draw(play_image);
        }
        if (game_win == true && leaderboard_check == true && times_end == 0){
            times_end += 1;
            face_win_image.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));
            Gamewindow.draw(face_win_image);
            final_ultra_seconds = seconds;
            Gamewindow.display();
            leaderboard_window(columns, rows, Name, final_ultra_seconds);
            leaderboard_check = false;
            game_pause = false;
        }
        else if (game_win == true && leaderboard_check == true){
            face_win_image.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));
            Gamewindow.draw(face_win_image);
            final_ultra_seconds = seconds;
            Gamewindow.display();
            leaderboard_window(columns, rows, Name, waste);
            leaderboard_check = false;
            game_pause = false;
        }
        Gamewindow.display();

        if (leaderboard_check == true && game_pause == true){
            leaderboard_window(columns, rows, Name, waste);
            leaderboard_check = false;
        }
        else if (leaderboard_check == true && game_win == false){
            leaderboard_window(columns, rows, Name, waste);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    actual_Minesweeper_board[i][j] = temp_board[i][j];
                }
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    temp_board[i][j] = 0;
                }
            }
            game_pause = false;
            leaderboard_check = false;
            clock.restart();
        }
    }
}



