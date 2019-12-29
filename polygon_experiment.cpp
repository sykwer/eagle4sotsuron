#include <tuple>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using P = pair<float, float>;
using T = tuple<float, float, string>;
using R = tuple<P, P, P, P, int>;

const int NUM = 10;

int main() {
  const float delta = -0.12;
  const float width = 0.8;
  const float half = width / 2;
  float x1 = 1.2;
  float y1 = 99;
  float x2 = 1.4;
  float y2 = 98.8;
  float x3 = 1.2;
  float y3 = 98.6;
  float x4 = 1;
  float y4 = 98.8;

  const float SHIFT = 0.025;

  vector<R> rects;

  for (int j = 0; j < NUM; j++) {
    vector<P> ypos;

    const float BOTTOM_SHIFT = 1.0 + width * (j % 4);
    for (int i = 0; i < NUM; i++) {
      float xx1 = (x1 + j * width);
      float yy1 = (y1 - i * width) - delta;
      float xx2 = (x2 + j * width) - delta;
      float yy2 = (y2 - i * width);
      float xx3 = (x3 + j * width);
      float yy3 = (y3 - i * width) + delta;
      float xx4 = (x4 + j * width) + delta;
      float yy4 = (y4 - i * width);

      if (i == 0) ypos.push_back(make_pair(xx1, yy1));
      else ypos.push_back(make_pair(xx1 - SHIFT, yy1 - SHIFT));

      ypos.push_back(make_pair(xx4, yy4));
      ypos.push_back(make_pair(xx3 - SHIFT, yy3 + SHIFT));

      if (i == NUM - 1) {
        ypos.push_back(P(xx1 - SHIFT, yy1 - SHIFT - BOTTOM_SHIFT));
        ypos.push_back(P(xx4, yy4 - BOTTOM_SHIFT));
        ypos.push_back(P(xx3, yy3 - BOTTOM_SHIFT));

        // Rects below
        rects.push_back(make_tuple(P(xx1, yy1-BOTTOM_SHIFT-width), P(xx2, yy2-BOTTOM_SHIFT-width), P(xx3, yy3-BOTTOM_SHIFT-width), P(xx4, yy4-BOTTOM_SHIFT-width), j));
      }
    }

    for (int i = NUM - 1; i >= 0; i--) {
      float xx1 = (x1 + j * width);
      float yy1 = (y1 - i * width) - delta;
      float xx2 = (x2 + j * width) - delta;
      float yy2 = (y2 - i * width);
      float xx3 = (x3 + j * width);
      float yy3 = (y3 - i * width) + delta;
      float xx4 = (x4 + j * width) + delta;
      float yy4 = (y4 - i * width);

      if (i == NUM - 1) {
        ypos.push_back(P(xx2, yy2 - BOTTOM_SHIFT));
        ypos.push_back(P(xx1 + SHIFT, yy1 - SHIFT - BOTTOM_SHIFT));
      }

      ypos.push_back(make_pair(xx3 + SHIFT, yy3 + SHIFT));
      ypos.push_back(make_pair(xx2, yy2));

      if (i != 0) {
        ypos.push_back(make_pair(xx1 + SHIFT, yy1 - SHIFT));
      } else {
        ypos.push_back(make_pair(xx1, yy1));
      }
    }

    cout << "poly yaxis" << j << " 0.01 ";
    for (P yp : ypos) {
      cout << "( " << yp.first << " " << yp.second << ") ";
    }
    cout << "; ";
  }

  vector<T> vias;

  for (int j = 0; j < NUM; j++) {
    for (int i = 0; i < NUM; i++) {
      float xx1 = (x1 + j * width + half);
      float yy1 = (y1 - i * width - half) - delta;
      float xx2 = (x2 + j * width + half) - delta;
      float yy2 = (y2 - i * width - half);
      float xx3 = (x3 + j * width + half);
      float yy3 = (y3 - i * width - half) + delta;
      float xx4 = (x4 + j * width + half) + delta;
      float yy4 = (y4 - i * width - half);

      // via
      vias.push_back(make_tuple(xx1, yy2, "xaxis" + to_string(i)));

      const float SHIFT = 0.055;
      vector<P> xpos;
      xpos.push_back(P(xx1, yy1));
      xpos.push_back(P(xx2 - SHIFT, yy2 + SHIFT));
      xpos.push_back(P(xx2 - SHIFT, yy2 - SHIFT));
      xpos.push_back(P(xx3, yy3));
      xpos.push_back(P(xx4 + SHIFT, yy4 - SHIFT));
      xpos.push_back(P(xx4 + SHIFT, yy4 + SHIFT));
      xpos.push_back(P(xx1, yy1));

      cout << "poly xaxis" << i << " 0.01 ";
      for (P xp : xpos) {
        cout << "(" << xp.first << " " << xp.second << ") ";
      }
      cout << "; ";
    }
  }

  for (R rect : rects) {
    P p1 = get<0>(rect);
    P p2 = get<1>(rect);
    P p3 = get<2>(rect);
    P p4 = get<3>(rect);
    string name = "yaxis" + to_string(get<4>(rect));
    cout << "poly " << name << " 0.01 (" << p1.first << " " << p1.second << ") (" << p2.first << " " << p2.second << ") (" << p3.first << " " << p3.second << ") (" << p4.first << " " << p4.second << ") (" << p1.first << " " << p1.second << "); ";
  }

  cout << "change drill 0.15; ";
  cout << "via 0.35; ";
  for (T via : vias) {
    cout << "via '" << get<2>(via) << "' (" << get<0>(via) << " " << get<1>(via) << "); ";
  }

  cout << endl;
  return 0;
}
