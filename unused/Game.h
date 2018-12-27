class Game {
 private:
    bool checkPossibilityOfMoveAndPrepareForIt(Coord, bool *, bool *, int *, const int *, Map *);

    void startMenuLoop(bool *, int *, size_t *, Map *, bool *, NCurses *, Coord *);

    int getNumberOfMovesGivenForEachCoin(NCurses *mainWindow);

    bool startGameplayLoop(Map *map, int *, int *, Character *, size_t *, const int *, NCurses *, NCurses *);

    void render(Map *, Character *, int, const size_t *, NCurses *, NCurses *);

    void updateAndShowLeaderboard(size_t, const int *, NCurses *);

    void showMessage(NCurses *, const std::string &, int, bool waitAfterMessage = true);

 public:
    Game();

    void startMainLoop();

    ~Game();
};