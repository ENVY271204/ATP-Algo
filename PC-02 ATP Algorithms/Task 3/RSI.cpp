#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
enum Period {
  N = 14
};

struct Asset {
  vector < double > close;
  vector < double > change;
  vector < double > gain;
  vector < double > loss;
  double avgGain = 0;
  double avgLoss = 0;
};

void initialize(Asset & asset, int days) {
  for (int index = 0; index < days; index++) {
    double random = rand() % 10 + 95 + (rand() % 100) * (0.01f);
    asset.close.push_back(random);
    asset.change.push_back(0);
    asset.gain.push_back(0);
    asset.loss.push_back(0);
  }

  for (int index = days - 1; index >= days - N; index--) {
    if (index == 0) {
      // first day avgGain and avg Loss initializer
      double random = rand() % 10 + 95 + (rand() % 100) * (0.01f);
      asset.change[0] = asset.close[0] - random;
      asset.gain[index] = max(asset.change[index], 0.0);
      asset.loss[index] = max(-asset.change[index], 0.0);
      asset.avgGain += max((asset.close[0] - random), 0.0);
      asset.avgLoss += max(-(asset.close[0] - random), 0.0);
      break;
    }
    asset.change[index] = asset.close[index] - asset.close[index - 1];
    asset.gain[index] = max(asset.change[index], 0.0);
    asset.loss[index] = max(-asset.change[index], 0.0);
    asset.avgGain += asset.gain[index];
    asset.avgLoss += asset.loss[index];
  }

  asset.avgGain /= days;
  asset.avgLoss /= days;

  cout << "Close, Change, Gain, Loss respectively" << endl;

  for (int index = 0; index < days; index++) {
    cout << asset.close[index] << ", " << asset.change[index] << ", " << asset.gain[index] << ", " << asset.loss[index] << endl;
  }

  cout << "Initial Average Gain: " << asset.avgGain << endl;
  cout << "Initial Average Loss: " << asset.avgLoss << endl;
}

void nextInitialize(Asset & asset) {
  double random = rand() % 10 + 95 + (rand() % 100) * (0.01f);
  asset.change.push_back(random - asset.close.back());
  asset.close.push_back(random);
  asset.gain.push_back(max(asset.change.back(), 0.0));
  asset.loss.push_back(max(-asset.change.back(), 0.0));
  asset.avgGain = ((N - 1) * asset.avgGain + asset.gain.back()) / N;
  asset.avgLoss = ((N - 1) * asset.avgLoss + asset.loss.back()) / N;
}
void nextRSI(Asset & asset) {
  int n = asset.close.size();
  double gain = 0;
  double loss = 0;

  double RS;
  double RSI;

  nextInitialize(asset);

  RS = asset.avgGain / asset.avgLoss;
  RSI = 100 - 100 / (1 + RS);

  cout << "RSI for " << n + 1 << "th day: " << RSI << endl;

  cout << "Do you wish to continue?" << endl <<
    "Type 1 for YES and 0 for NO" << endl;
  int temp;
  cin >> temp;
  if (temp & 1)
    nextRSI(asset);
  else
    return;
}

int main() {
  // object initialisation
  Asset asset;

  // First 20 days initialisation
  initialize(asset, N);

  // Next days
  nextRSI(asset);
}