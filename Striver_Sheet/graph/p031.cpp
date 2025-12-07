#include <bits/stdc++.h>
using namespace std;

int cheapest_flights_stops_optimal(int total_cities, vector<vector<int>>& flights_list, int src, int dst, int max_stops) {
    vector<vector<pair<int, int>>> adj_flights(total_cities);
    for (auto& flight : flights_list) {
        adj_flights[flight[0]].push_back({flight[1], flight[2]});
    }

    vector<int> min_price(total_cities, INT_MAX);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq_flight;

    min_price[src] = 0;
    pq_flight.push({0, src, 0});

    while (!pq_flight.empty()) {
        auto [curr_price, curr_city, stops_taken] = pq_flight.top();
        pq_flight.pop();

        if (curr_city == dst) return curr_price;
        if (stops_taken > max_stops) continue;
        if (curr_price > min_price[curr_city]) continue;

        for (auto& [next_city, ticket_price] : adj_flights[curr_city]) {
            int new_price = curr_price + ticket_price;
            if (new_price < min_price[next_city]) {
                min_price[next_city] = new_price;
                pq_flight.push({new_price, next_city, stops_taken + 1});
            }
        }
    }

    return min_price[dst] == INT_MAX ? -1 : min_price[dst];
}

int main() {
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
    cout << cheapest_flights_stops_optimal(4, flights, 0, 3, 1) << endl;
    return 0;
}
