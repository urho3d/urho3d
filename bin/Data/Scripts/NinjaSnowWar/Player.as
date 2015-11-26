class Player
{
    int score;
    String name;
    uint nodeID;
    Connection@ connection;
    Controls lastControls;

    Player()
    {
        score = 0;
        nodeID = 0;
    }
}

class HiscoreEntry
{
    int score;
    String name;
}
