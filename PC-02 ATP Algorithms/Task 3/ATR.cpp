#include <iostream>
#include <vector>
#include <algorithm>

enum Period {
  N = 14
};
using namespace std;

struct Asset {
  vector < double > high;
  vector < double > low;
  vector < double > close;
  vector < double > TR;
  double ATR = 0;
};

void trueRange(Asset & asset, int days) {
  for (int index = days; index > 0; index--) {
    int pos = asset.high.size() - index;

    // maximum of high-yesterdays's close and low-yesterday's close
    double max_close = max(abs(asset.high[pos] - asset.close[pos]), abs(asset.low[pos] - asset.close[pos]));

    // maximum of high-low and max_close
    asset.TR.push_back(max(asset.high[pos] - asset.low[pos], max_close));
  }
}

void initialize(Asset & asset, int days) {
  for (int index = 0; index < days; index++) {
    double random1 = rand() % 10 + 95 + (rand() % 100) * (0.01f); //between 95 and 105
    double random2 = rand() % 10 + 95 + (rand() % 100) * (0.01f);

    asset.high.push_back(max(random1, random2));
    asset.low.push_back(min(random1, random2));
    asset.close.push_back(rand() % 10 + 95 + (rand() % 100) * (0.01f)); //yesterday's close does not have to be between today high and low
  }

  trueRange(asset, days);
  cout << "High, Low, Close, True Range respectively" << endl;

  for (int index = 0; index < asset.TR.size(); index++) {
    asset.ATR += asset.TR[index];
    cout << asset.high[index] << ", " << asset.low[index] << ", " << asset.close[index] << ", " << asset.TR[index] << endl;
  }
  asset.ATR = asset.ATR / asset.TR.size();
  cout << asset.ATR << endl;
}

void nextATR(Asset & asset, double & ATR) {
  int n = asset.TR.size();
  int days;
  cout << "Input Number of days" << endl;
  cin >> days;
  if (days < 0) {
    cout << "Invalid input" << endl;
    return;
  }
  cout << "Do you wish to give data?" << endl << "Type 1 for YES and 0 for NO" << endl;
  bool b;
  cin >> b;
  if (b & 1) {
    int high_, low_, close_; // today's high,low,close
    for (int i = 0; i < days; i++) {
      cin >> high_ >> low_ >> close_;
      if (high_ > 0 && low_ > 0 && close_ > 0) {
        asset.high.push_back(high_);
        asset.low.push_back(low_);
        asset.close.push_back(close_);
      } else {
        cout << "Invalid input" << endl;
        return;
      }
    }
  } else {
    initialize(asset, days);
  }

  for (int i = 0; i < days; i++) {
    ATR = ((n - 1) * ATR + asset.TR[n]) / n;
    cout << "Average True range for " << n + 1 << "th day: " << ATR << endl;
    n++;
  }

  cout << "Do you wish to continue?" << endl << "Type 1 for YES and 0 for NO" << endl;
  int temp;
  cin >> temp;
  if (temp & 1)
    nextATR(asset, asset.ATR);
  else return;
}
int main() {
  // object initialisation
  Asset asset;

  //First 14 days initialisation
  initialize(asset, N);

  //Next days
  nextATR(asset, asset.ATR);
}