#pragma once
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
    LightGray,  //0111
    Gray,       //1000
    LightBlue,  //1001
    LightGreen, //1010
    LightCyan,  //1011
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
        const ConsoleColor foreGroundColor = ConsoleColor::LightGray, const ConsoleColor backGroundColor = ConsoleColor::Black,
        const bool topEdge = false, const bool bottomEdge = false, const bool rightEdge = false, const bool leftEdge = false,
        const bool invertColors = false
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
    static void InitializeStdHandle();

    void SetForeGroundColor(const ConsoleColor color);
    ConsoleColor GetForeGroundColor() const;
    void SetBackGroundColor(const ConsoleColor color);
    ConsoleColor GetBackGroundColor() const;

    void SetTopEdge(const bool enabled);
    bool GetTopEdge() const;
    void SetBottomEdge(const bool enabled);
    bool GetBottomEdge() const;
    void SetRightEdge(const bool enabled);
    bool GetRightEdge() const;
    void SetLeftEdge(const bool enabled);
    bool GetLeftEdge() const;

    void SetInvertColors(const bool enabled);
    bool GetInvertColors() const;

    void Reset();

    uint32_t GetAsUint32() const;

    void Apply() const;
private:
    uint32_t _textAttribute;
};

bool operator ==(ConsoleTextAttribute left, ConsoleTextAttribute right);