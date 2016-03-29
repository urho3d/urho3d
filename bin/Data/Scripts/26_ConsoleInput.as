// Console input example.
// This sample demonstrates:
//     - Implementing a crude text adventure game, which accepts input both through the engine console,
//       and standard input.
//     - Disabling default execution of console commands as immediate mode AngelScript.

#include "Scripts/Utilities/Sample.as"

bool gameOn;
bool foodAvailable;
bool eatenLastTurn;
int numTurns;
int hunger;
int urhoThreat;

// Hunger level descriptions
String[] hungerLevels = {
    "bursting",
    "well-fed",
    "fed",
    "hungry",
    "very hungry",
    "starving"
};

// Urho threat level descriptions
String[] urhoThreatLevels = {
    "Suddenly Urho appears from a dark corner of the fish tank",
    "Urho seems to have his eyes set on you",
    "Urho is homing in on you mercilessly"
};

void Start()
{
    // Execute the common startup for samples
    SampleStart();

    // Disable default execution of AngelScript from the console
    script.executeConsoleCommands = false;

    // Subscribe to console commands and the frame update
    SubscribeToEvent("ConsoleCommand", "HandleConsoleCommand");
    SubscribeToEvent("Update", "HandleUpdate");

    // Subscribe key down event
    SubscribeToEvent("KeyDown", "HandleEscKeyDown");

    // Hide logo to make room for the console
    SetLogoVisible(false);

    // Show the console by default, make it large
    console.numRows = graphics.height / 16;
    console.numBufferedRows = 2 * console.numRows;
    console.commandInterpreter = "ScriptEventInvoker";
    console.visible = true;
    console.closeButton.visible = false;

    // Show OS mouse cursor
    input.mouseVisible = true;

    // Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE);

    // Open the operating system console window (for stdin / stdout) if not open yet
    // Do not open in fullscreen, as this would cause constant device loss
    if (!graphics.fullscreen)
        OpenConsoleWindow();

    // Initialize game and print the welcome message
    StartGame();

    // Randomize from system clock
    SetRandomSeed(time.systemTime);
}

void HandleConsoleCommand(StringHash eventType, VariantMap& eventData)
{
    if (eventData["Id"].GetString() == "ScriptEventInvoker")
        HandleInput(eventData["Command"].GetString());
}

void HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Check if there is input from stdin
    String input = GetConsoleInput();
    if (input.length > 0)
        HandleInput(input);
}

void HandleEscKeyDown(StringHash eventType, VariantMap& eventData)
{
    // Unlike the other samples, exiting the engine when ESC is pressed instead of just closing the console
    if (eventData["Key"].GetInt() == KEY_ESC)
        engine.Exit();
}

void StartGame()
{
    Print("Welcome to the Urho adventure game! You are the newest fish in the tank; your\n"
          "objective is to survive as long as possible. Beware of hunger and the merciless\n"
          "predator cichlid Urho, who appears from time to time. Evading Urho is easier\n"
          "with an empty stomach. Type 'help' for available commands.");

    gameOn = true;
    foodAvailable = false;
    eatenLastTurn = false;
    numTurns = 0;
    hunger = 2;
    urhoThreat = 0;
}

void EndGame(const String&in message)
{
    Print(message);
    Print("Game over! You survived " + String(numTurns) + " turns.\n"
          "Do you want to play again (Y/N)?");

    gameOn = false;
}

void Advance()
{
    if (urhoThreat > 0)
    {
        ++urhoThreat;
        if (urhoThreat > 3)
        {
            EndGame("Urho has eaten you!");
            return;
        }
    }
    else if (urhoThreat < 0)
        ++urhoThreat;
    if (urhoThreat == 0 && Random() < 0.2f)
        ++urhoThreat;

    if (urhoThreat > 0)
        Print(urhoThreatLevels[urhoThreat - 1] + ".");

    if ((numTurns & 3) == 0 && !eatenLastTurn)
    {
        ++hunger;
        if (hunger > 5)
        {
            EndGame("You have died from starvation!");
            return;
        }
        else
            Print("You are " + hungerLevels[hunger] + ".");
    }

    eatenLastTurn = false;

    if (foodAvailable)
    {
        Print("The floating pieces of fish food are quickly eaten by other fish in the tank.");
        foodAvailable = false;
    }
    else if (Random() < 0.15f)
    {
        Print("The overhead dispenser drops pieces of delicious fish food to the water!");
        foodAvailable = true;
    }

    ++numTurns;
}

void HandleInput(const String&in input)
{
    String inputLower = input.ToLower().Trimmed();
    if (inputLower.empty)
    {
        Print("Empty input given!");
        return;
    }

    if (inputLower == "quit" || inputLower == "exit")
        engine.Exit();
    else if (gameOn)
    {
        // Game is on
        if (inputLower == "help")
            Print("The following commands are available: 'eat', 'hide', 'wait', 'score', 'quit'.");
        else if (inputLower == "score")
            Print("You have survived " + String(numTurns) + " turns.");
        else if (inputLower == "eat")
        {
            if (foodAvailable)
            {
                Print("You eat several pieces of fish food.");
                foodAvailable = false;
                eatenLastTurn = true;
                hunger -= (hunger > 3) ? 2 : 1;
                if (hunger < 0)
                {
                    EndGame("You have killed yourself by over-eating!");
                    return;
                }
                else
                    Print("You are now " + hungerLevels[hunger] + ".");
            }
            else
                Print("There is no food available.");

            Advance();
        }
        else if (inputLower == "wait")
        {
            Print("Time passes...");
            Advance();
        }
        else if (inputLower == "hide")
        {
            if (urhoThreat > 0)
            {
                bool evadeSuccess = hunger > 2 || Random() < 0.5f;
                if (evadeSuccess)
                {
                    Print("You hide behind the thick bottom vegetation, until Urho grows bored.");
                    urhoThreat = -2;
                }
                else
                    Print("Your movements are too slow; you are unable to hide from Urho.");
            }
            else
                Print("There is nothing to hide from.");

            Advance();
        }
        else
            Print("Cannot understand the input '" + input + "'.");
    }
    else
    {
        // Game is over, wait for (y)es or (n)o reply
        if (inputLower[0] == 'y')
            StartGame();
        else if (inputLower[0] == 'n')
            engine.Exit();
        else
            Print("Please answer 'y' or 'n'.");
    }
}

// Create XML patch instructions for screen joystick layout specific to this sample app
String patchInstructions =
        "<patch>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button2']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" +
        "        <attribute name=\"Is Visible\" value=\"false\" />" +
        "    </add>" +
        "</patch>";
