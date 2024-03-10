#include "GameConsole.h"
#include "../Input/Input.h"
#include "../Log/Log.h"
#include "../Resources/TestImages.h"

GameConsole::GameConsole(Frame ip_oLevel)
{
    voLevel1.Initialize(ip_oLevel.vnFrameWidth, ip_oLevel.vnFrameHeight, ip_oLevel.vaCanvas);
}

GameConsole::~GameConsole()
{
}

void GameConsole::Start()
{
    // Add debug log to check the time to print each separated image vs one combined
    // Also add debug log for moving cursor vs flusing data	
    //Create list of images and parse them into Initialize function of Frame to generate one frame
    //https://coding-champ.com/tutorials/c-plus-plus/lists-and-vectors
    //std::list<GameObject> dataSet;

    /* Create */
    GameObject voBorder(border, 0, 0, 0);
    dataSet.push_back(voBorder);

    GameObject voPlayer(Player, 10, 5, 1);
    dataSet.push_back(voPlayer);
    //voLevel1.Draw(voPlayer.vaImage, voPlayer.vaImage[0], voPlayer.vaImage[1], voPlayer.vnXPosition, voPlayer.vnYPosition);

    // Looping through all of the elements:
    for (GameObject voObject : dataSet)
    {
        voLevel1.AddImageToCanvas(voObject.vaImage, voObject.vnXPosition, voObject.vnYPosition);
    }

    voLevel1.Draw();

    /*
    // Using iterator, reach element at index 1:
    auto objectIterator = dataSet.begin();
    std::advance(objectIterator, 1);

    GameObject voTest = *objectIterator;
    std::cout << voTest.vaImage[0] << std::endl;
    */
}

void GameConsole::Update()
{

    vnInput = ReadInput();

    /* 
        If your container contains instances instead of pointers *, you will need to take a reference & of the object instead, and use for ( auto& enemy : enemies ). 
        This will ensure your object is modified in place, and not copied, otherwise, your changes won't get reflected in the container. 
        https://stackoverflow.com/questions/55114428/how-to-loop-through-class-objects-in-c
    */
    for (GameObject& voObject : dataSet)
    {
        switch (vnInput)
        {
            case KEY_VALUE::UP:
                voObject.MoveUp();
                break;
            case KEY_VALUE::DOWN:
                voObject.MoveDown();
                break;
            case KEY_VALUE::LEFT:
                voObject.MoveLeft();
                break;
            case KEY_VALUE::RIGHT:
                voObject.MoveRight();
                break;
            default:

                break;
        }
        if (voObject.vnXPosition < 0)
        {
            voObject.MoveRight();
        }
        if (voObject.vnXPosition + voObject.vnWidth > voLevel1.vnFrameWidth)
        {
            voObject.MoveLeft();
        }
        if (voObject.vnYPosition < 0)
        {
            voObject.MoveDown();
        }
        if (voObject.vnYPosition + voObject.vnHeight  > voLevel1.vnFrameHeight)
        {
            voObject.MoveUp();
        }

        voLevel1.AddImageToCanvas(voObject.vaImage, voObject.vnXPosition, voObject.vnYPosition);
        
    }

    voLevel1.Draw();

    //vnInput = 0;
}
