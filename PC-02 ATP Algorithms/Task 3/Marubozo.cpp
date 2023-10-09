#include <iostream>
#include <vector>

using namespace std;

struct Candle 
{
    double open;
    double high;
    double low;
    double close;
};

enum MarubozuTrend 
{
    BULLISH,
    BEARISH,
    NONE
};

MarubozuTrend detectMarubozu(Candle candle) 
{
    if (candle.close > candle.open)
    {
        double upper = candle.high - candle.close;
        double lower = candle.low -candle.open;
        if (upper == 0 && lower == 0) 
        { 
            return BULLISH;
        }
    } 
if (candle.close < candle.open)
    {
        double upper = candle.low - candle.close;
        double lower = candle.high -candle.open;
        if (upper == 0 && lower == 0) 
        { 
            return BEARISH;
        }
    }
    return NONE;     
}

int main() {

    vector<Candle> candles = 
    {
        {100.0, 110.0, 100.0, 110.0}, // bullish marubozu
        {105.0, 105.0, 98.0, 98.0}, // bearish marubozu
        {100.0, 105.0, 98.0, 103.0}, // not a marubozu
    };

    for (auto candle : candles) 
    {
        MarubozuTrend marubozu = detectMarubozu(candle);
        if (marubozu == BULLISH) 
        {
            cout << "Bullish marubozu detected" << endl;
        } 
        else if (marubozu == BEARISH) 
        {
            cout << "Bearish marubozu detected" << endl;
        } 
        else 
        {
            cout << "Not a marubozu" << endl;
        }
    }
    return 0;
}
