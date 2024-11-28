#pragma once
#include <Windows.h>
#include <inttypes.h>

enum class ConsoleColor : char
{
    Black,      //0000
    Blue,       //0001
    Green,      //0010
    Cyan,       //0011
    Red,        //0100
    Purple,     //0101
    Yellow,     //0110
    Gray,       //1000
    LightGray,  //0111
    LightBlue,  //1001
    LightGreen, //1010
    LightCyan,  //1011
    LightAqua,  //1011
    LightRed,   //1100
    LightPurple,//1101
    LightYellow,//1110
    White,      //1111
};

struct ConsoleTextAttribute
{
public:
    ConsoleTextAttribute
    (
        ConsoleColor foreGroundColor = ConsoleColor::LightGray, ConsoleColor backGroundColor = ConsoleColor::Black,
        bool topEdge = false, bool bottomEdge = false, bool rightEdge = false, bool leftEdge = false,
        bool invertColors = false
    )
    {
        SetForeGroundColor(foreGroundColor);
        SetBackGroundColor(backGroundColor);

        SetTopEdge(topEdge);
        SetBottomEdge(bottomEdge);
        SetRightEdge(rightEdge);
        SetLeftEdge(leftEdge);

        SetInvertColors(invertColors);
    }

    // this function NEEDS to be called at least once before applying ConsoleTextAttribute
    static void InitializeSTDHandle();

    void SetForeGroundColor(ConsoleColor color);
    ConsoleColor GetForeGroundColor();
    void SetBackGroundColor(ConsoleColor color);
    ConsoleColor GetBackGroundColor();

    void SetTopEdge(bool enabled);
    bool GetTopEdge();
    void SetBottomEdge(bool enabled);
    bool GetBottomEdge();
    void SetRightEdge(bool enabled);
    bool GetRightEdge();
    void SetLeftEdge(bool enabled);
    bool GetLeftEdge();

    void SetInvertColors(bool enabled);
    bool GetInvertColors();

    void Reset();

    void Apply();
private:
    uint32_t _textAttribute;
};