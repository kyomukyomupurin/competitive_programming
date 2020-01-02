// Shortest Path Faster Algorithm(SPFA)
// verified by
//     https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B

#include <limits>
#include <queue>
#include <vector>

template <class T>
class SPFA {
 public:
  SPFA(int node_size) : node_size_(node_size) { Initialize(); }

  void AddEdge(int from, int to, T cost) { graph_[from].push_back({to, cost}); }

  // use after Solve()
  bool ExistNegativeCycle() { return distance_.empty(); }

  void Solve(int source) {
    std::queue<int> q;
    q.push(source);
    pending_[source] = true;
    ++times_[source];
    distance_[source] = 0;
    while (!q.empty()) {
      int top = q.front();
      q.pop();
      pending_[top] = false;
      for (const auto& next : graph_[top]) {
        T next_cost = distance_[top] + next.cost;
        if (next_cost >= distance_[next.to]) continue;
        distance_[next.to] = next_cost;
        if (!pending_[next.to]) {
          if (++times_[next.to] >= node_size_) {
            distance_.clear();
            return;
          }
          pending_[next.to] = true;
          q.push(next.to);
        }
      }
    }
    return;
  }

  T operator[](int to) const { return distance_[to]; }

 private:
  struct edge {
    int to;
    T cost;
  };
  int node_size_;
  std::vector<std::vector<edge>> graph_;
  std::vector<T> distance_;
  std::vector<int> pending_;
  std::vector<int> times_;

  void Initialize() {
    graph_.resize(node_size_);
    distance_.assign(node_size_, std::numeric_limits<T>::max() / 2);
    pending_.assign(node_size_, 0);
    times_.assign(node_size_, 0);
  }
};

// verification code
/*
void GRL_1_B() {
  int n, m, r; cin >> n >> m >> r;
  SPFA<int> spfa(n);
  for (int i = 0; i < m; ++i) {
    int s, t, d; cin >> s >> t >> d;
    spfa.AddEdge(s, t, d);
  }

  spfa.Solve(r);

  if (spfa.ExistNegativeCycle()) {
    cout << "NEGATIVE CYCLE" << '\n';
  } else {
    for (int i = 0; i < n; ++i) {
      if (spfa[i] == std::numeric_limits<int>::max() / 2) {
        cout << "INF" << '\n';
      } else {
        cout << spfa[i] << '\n';
      }
    }
  }
}
*/