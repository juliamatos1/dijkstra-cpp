#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<pair<int, double>>> LP;

void leituraGrafo(LP &, int);
void escritaGrafo(LP &);
void dijkstra(LP &, int);

int main()
{
    int n, m;
    cin >> n >> m;

    LP Grafo;
    Grafo.assign(n, vector<pair<int, double>>());

    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);

    cout << "Total Vertices: " << n << endl;
    cout << "Total Arestas: " << m << endl;

    int origem = 0;
    dijkstra(Grafo, origem);

    return 0;
}

void leituraGrafo(LP &G, int m)
{
    int a, b;
    double c;

    while (m--)
    {
        cin >> a >> b >> c;
        G[a].push_back(make_pair(b, c));
        // Grafo direcionado
    }
}

void escritaGrafo(LP &G)
{
    int n = G.size();

    cout << "Lista de Adjacencia:" << endl;

    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";

        for (const auto &v : G[u])
        {
            cout << "[(" << u << "," << v.first
                 << ") w: " << v.second << "] ";
        }

        cout << endl;
    }
}

void dijkstra(LP &G, int origem)
{
    int n = G.size();

    vector<double> dist(n,
        numeric_limits<double>::infinity());

    vector<int> predecessor(n, -1);

    priority_queue<
        pair<double, int>,
        vector<pair<double, int>>,
        greater<pair<double, int>>
    > fila;

    dist[origem] = 0;
    fila.push({0, origem});

    while (!fila.empty())
    {
        double d = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if (d > dist[u])
            continue;

        for (const auto &v : G[u])
        {
            int vizinho = v.first;
            double peso = v.second;

            if (dist[u] + peso < dist[vizinho])
            {
                dist[vizinho] = dist[u] + peso;
                predecessor[vizinho] = u;

                fila.push({dist[vizinho], vizinho});
            }
        }
    }

    cout << "\nResultado do Dijkstra:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Vertice " << i << ": ";

        if (isinf(dist[i]))
        {
            cout << "Inacessivel";
        }
        else
        {
            cout << "Distancia = " << dist[i];

            cout << " | Predecessor = "
                 << predecessor[i];

            // Reconstrucao do caminho minimo
            vector<int> caminho;

            for (int atual = i; atual != -1;
                 atual = predecessor[atual])
            {
                caminho.push_back(atual);
            }

            reverse(caminho.begin(), caminho.end());

            cout << " | Caminho = ";

            for (int j = 0; j < (int)caminho.size(); j++)
            {
                cout << caminho[j];

                if (j + 1 < (int)caminho.size())
                    cout << " -> ";
            }
        }

        cout << endl;
    }
}
